#include "hikvision_camera_node.h"
#include <sstream>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <cstring>

// 构造函数实现
HikvisionCameraNode::HikvisionCameraNode() : Node("hikvision_camera_node"),
                                             connection_state_(ConnectionState::DISCONNECTED),
                                             is_capturing_(false),
                                             thread_running_(true) {
    // 声明并获取参数
    this->declare_parameter<std::string>("camera_ip", "192.168.1.64");
    this->declare_parameter<int>("camera_port", 80);
    this->declare_parameter<std::string>("username", "admin");
    this->declare_parameter<std::string>("password", "12345");
    
    this->get_parameter("camera_ip", camera_ip_);
    this->get_parameter("camera_port", camera_port_);
    this->get_parameter("username", username_);
    this->get_parameter("password", password_);
    
    // 初始化发布者和服务
    image_pub_ = this->create_publisher<sensor_msgs::msg::Image>("/camera/flame_image", 10);
    
    ptz_control_srv_ = this->create_service<hikvision_interfaces::srv::PtzControl>(
        "/camera/ptz_control",
        std::bind(&HikvisionCameraNode::handle_ptz_control, this, std::placeholders::_1, std::placeholders::_2)
    );
    
    set_resolution_srv_ = this->create_service<hikvision_interfaces::srv::SetResolution>(
        "/camera/set_resolution",
        std::bind(&HikvisionCameraNode::handle_set_resolution, this, std::placeholders::_1, std::placeholders::_2)
    );
    
    // 初始化摄像头连接
    if (init_camera_connection()) {
        RCLCPP_INFO(this->get_logger(), "摄像头初始化成功");
        
        // 启动图像采集定时器(10Hz)
        image_capture_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&HikvisionCameraNode::capture_and_publish_image, this)
        );
        
        // 启动心跳检测定时器(2秒一次)
        heartbeat_timer_ = this->create_wall_timer(
            std::chrono::seconds(2),
            std::bind(&HikvisionCameraNode::heartbeat_check, this)
        );
    } else {
        RCLCPP_ERROR(this->get_logger(), "摄像头初始化失败，启动重连机制");
        // 启动重连线程
        reconnect_thread_ = std::thread(&HikvisionCameraNode::reconnect_task, this);
    }
}

// 析构函数实现
HikvisionCameraNode::~HikvisionCameraNode() {
    // 停止线程
    thread_running_ = false;
    if (reconnect_thread_.joinable()) {
        reconnect_thread_.join();
    }
    
    // 停止图像采集
    is_capturing_ = false;
    if (cap_.isOpened()) {
        cap_.release();
    }
    
    // 关闭连接
    close_socket_connection();
}

// 初始化摄像头连接
bool HikvisionCameraNode::init_camera_connection() {
    // 建立Socket连接
    if (!create_socket_connection()) {
        RCLCPP_ERROR(this->get_logger(), "无法建立Socket连接");
        return false;
    }
    
    // 发送首次请求获取nonce
    std::string response = send_isapi_request("GET", "/ISAPI/System/status");
    if (response.find("401 Unauthorized") == std::string::npos) {
        RCLCPP_ERROR(this->get_logger(), "未收到预期的401响应，无法获取认证信息");
        close_socket_connection();
        return false;
    }
    
    // 提取nonce
    nonce_ = extract_nonce(response);
    if (nonce_.empty()) {
        RCLCPP_ERROR(this->get_logger(), "无法从响应中提取nonce");
        close_socket_connection();
        return false;
    }
    
    // 获取RTSP流地址
    response = send_isapi_request("GET", "/ISAPI/Streaming/channels/1");
    if (!parse_rtsp_url(response)) {
        RCLCPP_ERROR(this->get_logger(), "无法获取RTSP流地址");
        close_socket_connection();
        return false;
    }
    
    // 尝试打开RTSP流
    if (!cap_.open(rtsp_url_)) {
        RCLCPP_ERROR(this->get_logger(), "无法打开RTSP流: %s", rtsp_url_.c_str());
        close_socket_connection();
        return false;
    }
    
    // 更新连接状态
    connection_state_ = ConnectionState::CONNECTED;
    return true;
}

// 建立Socket连接
bool HikvisionCameraNode::create_socket_connection() {
    // 创建Socket
    socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd_ < 0) {
        RCLCPP_ERROR(this->get_logger(), "创建Socket失败: %s", strerror(errno));
        return false;
    }
    
    // 设置服务器地址
    memset(&server_addr_, 0, sizeof(server_addr_));
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(camera_port_);
    
    // 转换IP地址
    if (inet_pton(AF_INET, camera_ip_.c_str(), &server_addr_.sin_addr) <= 0) {
        RCLCPP_ERROR(this->get_logger(), "无效的IP地址: %s", camera_ip_.c_str());
        close(socket_fd_);
        return false;
    }
    
    // 连接服务器
    if (connect(socket_fd_, (struct sockaddr*)&server_addr_, sizeof(server_addr_)) < 0) {
        RCLCPP_ERROR(this->get_logger(), "连接失败: %s", strerror(errno));
        close(socket_fd_);
        return false;
    }
    
    return true;
}

// 关闭Socket连接
void HikvisionCameraNode::close_socket_connection() {
    if (socket_fd_ > 0) {
        close(socket_fd_);
        socket_fd_ = -1;
    }
    connection_state_ = ConnectionState::DISCONNECTED;
}

// MD5哈希计算
std::string HikvisionCameraNode::md5_hash(const std::string& input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((const unsigned char*)input.c_str(), input.size(), digest);
    
    // 转换为16进制字符串
    std::stringstream ss;
    for(int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }
    return ss.str();
}

// 生成Digest认证头
std::string HikvisionCameraNode::generate_digest_auth(const std::string& method, const std::string& uri) {
    // 计算HA1 = MD5(用户名:realm:密码)
    std::string ha1 = md5_hash(username_ + ":" + realm_ + ":" + password_);
    
    // 计算HA2 = MD5(请求方法:URI)
    std::string ha2 = md5_hash(method + ":" + uri);
    
    // 计算response = MD5(HA1:nonce:HA2)
    std::string response = md5_hash(ha1 + ":" + nonce_ + ":" + ha2);
    
    // 构造认证头
    std::string auth_header = "Digest username=\"" + username_ + "\", "
                            "realm=\"" + realm_ + "\", "
                            "nonce=\"" + nonce_ + "\", "
                            "uri=\"" + uri + "\", "
                            "response=\"" + response + "\"";
    
    return auth_header;
}

// 发送ISAPI请求
std::string HikvisionCameraNode::send_isapi_request(const std::string& method, const std::string& uri, const std::string& body) {
    if (connection_state_ != ConnectionState::CONNECTED && connection_state_ != ConnectionState::RECONNECTING) {
        RCLCPP_WARN(this->get_logger(), "未连接状态，无法发送请求");
        return "";
    }
    
    // 构造HTTP请求
    std::string request = method + " " + uri + " HTTP/1.1\r\n"
                        "Host: " + camera_ip_ + ":" + std::to_string(camera_port_) + "\r\n"
                        "Content-Type: application/xml\r\n";
    
    // 添加认证头(首次请求没有nonce，不添加认证头)
    if (!nonce_.empty()) {
        request += "Authorization: " + generate_digest_auth(method, uri) + "\r\n";
    }
    
    // 添加内容长度和连接保持
    request += "Content-Length: " + std::to_string(body.size()) + "\r\n"
              "Connection: keep-alive\r\n\r\n"
              + body;
    
    // 发送请求
    ssize_t bytes_sent = send(socket_fd_, request.c_str(), request.size(), 0);
    if (bytes_sent < 0) {
        RCLCPP_ERROR(this->get_logger(), "发送请求失败: %s", strerror(errno));
        connection_state_ = ConnectionState::ERROR;
        return "";
    }
    
    // 接收响应
    char buffer[4096];
    std::string response;
    ssize_t bytes_read;
    
    // 设置接收超时(5秒)
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    setsockopt(socket_fd_, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    
    while ((bytes_read = recv(socket_fd_, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        response += buffer;
        
        // 检查是否接收完毕(通过Content-Length判断)
        size_t content_length_pos = response.find("Content-Length: ");
        if (content_length_pos != std::string::npos) {
            size_t end_pos = response.find("\r\n", content_length_pos);
            std::string len_str = response.substr(content_length_pos + 16, end_pos - (content_length_pos + 16));
            int content_length = std::stoi(len_str);
            
            size_t body_pos = response.find("\r\n\r\n");
            if (body_pos != std::string::npos) {
                size_t received_length = response.size() - (body_pos + 4);
                if (received_length >= content_length) {
                    break; // 接收完毕
                }
            }
        }
    }
    
    if (bytes_read < 0) {
        RCLCPP_ERROR(this->get_logger(), "接收响应失败: %s", strerror(errno));
        connection_state_ = ConnectionState::ERROR;
        return "";
    }
    
    return response;
}

// 从响应中提取nonce
std::string HikvisionCameraNode::extract_nonce(const std::string& response) {
    size_t nonce_start = response.find("nonce=\"");
    if (nonce_start == std::string::npos) {
        return "";
    }
    
    nonce_start += 7; // 跳过"nonce=\""
    size_t nonce_end = response.find("\"", nonce_start);
    if (nonce_end == std::string::npos) {
        return "";
    }
    
    return response.substr(nonce_start, nonce_end - nonce_start);
}

// 解析XML响应获取RTSP地址
bool HikvisionCameraNode::parse_rtsp_url(const std::string& response) {
    // 找到XML部分的起始位置
    size_t xml_start = response.find("<?xml");
    if (xml_start == std::string::npos) {
        RCLCPP_ERROR(this->get_logger(), "响应中未找到XML内容");
        return false;
    }
    
    // 提取XML部分
    std::string xml_content = response.substr(xml_start);
    
    // 解析XML
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.Parse(xml_content.c_str());
    if (error != tinyxml2::XML_SUCCESS) {
        RCLCPP_ERROR(this->get_logger(), "XML解析失败: %s", doc.ErrorName());
        return false;
    }
    
    // 查找RTSP URL元素
    tinyxml2::XMLElement* rtsp_elem = doc.FirstChildElement("StreamingChannel")->FirstChildElement("RTSPURL");
    if (rtsp_elem && rtsp_elem->GetText()) {
        rtsp_url_ = rtsp_elem->GetText();
        RCLCPP_INFO(this->get_logger(), "获取RTSP流地址: %s", rtsp_url_.c_str());
        return true;
    }
    
    RCLCPP_ERROR(this->get_logger(), "XML中未找到RTSPURL元素");
    return false;
}

// 云台控制服务回调
void HikvisionCameraNode::handle_ptz_control(const std::shared_ptr<hikvision_interfaces::srv::PtzControl::Request> req,
                                            std::shared_ptr<hikvision_interfaces::srv::PtzControl::Response> res) {
    RCLCPP_INFO(this->get_logger(), "收到云台控制请求: 方向=%s, 速度=%d", req->direction.c_str(), req->speed);
    
    if (connection_state_ != ConnectionState::CONNECTED) {
        res->success = false;
        res->message = "摄像头未连接";
        return;
    }
    
    // 构造PTZ控制的XML请求体
    std::string xml_body = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                          "<PTZData>"
                          "  <pan>" + req->direction + "</pan>"
                          "  <speed>" + std::to_string(req->speed) + "</speed>"
                          "</PTZData>";
    
    // 发送ISAPI请求
    std::string response = send_isapi_request("PUT", "/ISAPI/PTZ/Controls", xml_body);
    
    // 检查响应
    if (response.find("200 OK") != std::string::npos) {
        res->success = true;
        res->message = "云台控制成功";
        RCLCPP_INFO(this->get_logger(), "云台控制成功");
    } else {
        res->success = false;
        res->message = "云台控制失败";
        RCLCPP_ERROR(this->get_logger(), "云台控制失败，响应: %s", response.c_str());
    }
}

// 分辨率设置服务回调
void HikvisionCameraNode::handle_set_resolution(const std::shared_ptr<hikvision_interfaces::srv::SetResolution::Request> req,
                                               std::shared_ptr<hikvision_interfaces::srv::SetResolution::Response> res) {
    RCLCPP_INFO(this->get_logger(), "收到分辨率设置请求: 宽度=%d, 高度=%d", req->width, req->height);
    
    if (connection_state_ != ConnectionState::CONNECTED) {
        res->success = false;
        res->message = "摄像头未连接";
        return;
    }
    
    // 构造分辨率设置的XML请求体
    std::string xml_body = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                          "<VideoResolution>"
                          "  <width>" + std::to_string(req->width) + "</width>"
                          "  <height>" + std::to_string(req->height) + "</height>"
                          "</VideoResolution>";
    
    // 发送ISAPI请求
    std::string response = send_isapi_request("PUT", "/ISAPI/Image/Resolution", xml_body);
    
    // 检查响应
    if (response.find("200 OK") != std::string::npos) {
        // 分辨率更改后需要重新打开RTSP流
        cap_.release();
        if (cap_.open(rtsp_url_)) {
            res->success = true;
            res->message = "分辨率设置成功";
            RCLCPP_INFO(this->get_logger(), "分辨率设置成功");
        } else {
            res->success = false;
            res->message = "分辨率设置成功，但无法重新打开RTSP流";
            RCLCPP_ERROR(this->get_logger(), "无法重新打开RTSP流");
        }
    } else {
        res->success = false;
        res->message = "分辨率设置失败";
        RCLCPP_ERROR(this->get_logger(), "分辨率设置失败，响应: %s", response.c_str());
    }
}

// 心跳检测函数
void HikvisionCameraNode::heartbeat_check() {
    if (connection_state_ != ConnectionState::CONNECTED) {
        return;
    }
    
    // 发送轻量级心跳请求
    std::string response = send_isapi_request("GET", "/ISAPI/System/status");
    
    // 检查响应
    if (response.empty() || response.find("200 OK") == std::string::npos) {
        RCLCPP_WARN(this->get_logger(), "心跳检测失败，连接可能已断开");
        connection_state_ = ConnectionState::ERROR;
        
        // 如果没有重连线程，则启动一个
        if (!reconnect_thread_.joinable() || !thread_running_) {
            thread_running_ = true;
            reconnect_thread_ = std::thread(&HikvisionCameraNode::reconnect_task, this);
        }
    }
}

// 图像采集函数
void HikvisionCameraNode::capture_and_publish_image() {
    if (connection_state_ != ConnectionState::CONNECTED || !cap_.isOpened()) {
        return;
    }
    
    cv::Mat frame;
    if (cap_.read(frame)) {  // 读取一帧图像
        // 压缩图像为JPEG格式
        std::vector<uchar> buffer;
        std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, 80};  // 质量80%
        cv::imencode(".jpg", frame, buffer, params);
        
        // 转换为ROS图像消息
        auto msg = std::make_unique<sensor_msgs::msg::Image>();
        msg->header.stamp = this->now();
        msg->header.frame_id = "camera_frame";
        msg->height = frame.rows;
        msg->width = frame.cols;
        msg->encoding = "bgr8";
        msg->is_bigendian = false;
        msg->step = frame.cols * frame.elemSize();
        msg->data.assign(buffer.begin(), buffer.end());
        
        // 发布图像消息
        image_pub_->publish(std::move(msg));
    } else {
        RCLCPP_WARN(this->get_logger(), "无法获取图像帧，尝试重新打开RTSP流");
        cap_.release();
        cap_.open(rtsp_url_);
    }
}

// 重连任务
void HikvisionCameraNode::reconnect_task() {
    RCLCPP_INFO(this->get_logger(), "启动重连线程");
    connection_state_ = ConnectionState::RECONNECTING;
    
    // 重连尝试次数
    int retry_count = 0;
    
    while (thread_running_ && connection_state_ != ConnectionState::CONNECTED) {
        RCLCPP_INFO(this->get_logger(), "重连尝试 %d...", retry_count + 1);
        
        // 关闭现有连接
        close_socket_connection();
        
        // 尝试重新初始化连接
        if (init_camera_connection()) {
            RCLCPP_INFO(this->get_logger(), "重连成功");
            connection_state_ = ConnectionState::CONNECTED;
            
            // 重启图像采集定时器
            image_capture_timer_ = this->create_wall_timer(
                std::chrono::milliseconds(100),
                std::bind(&HikvisionCameraNode::capture_and_publish_image, this)
            );
            
            break;
        }
        
        // 重连失败，等待一段时间后重试(指数退避)
        retry_count++;
        int delay = std::min(1000 * (1 << std::min(retry_count, 5)), 5000);  // 最大延迟5秒
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    
    RCLCPP_INFO(this->get_logger(), "重连线程结束");
}


void HikvisionCameraNode::publish_image() {
    cv::Mat frame;
    if (rtsp_capture.read(frame)) {
        // 1. 直接调用火焰检测算法（C++接口）
        FlameDetector detector;
        std::vector<cv::Rect> flame_areas = detector.detect(frame);  // 检测火焰区域
        
        // 2. 若检测到火焰，自动触发云台控制
        if (!flame_areas.empty()) {
            this->auto_track_flame(flame_areas[0], frame.cols, frame.rows);  // 跟踪逻辑
        }

        // 3. 后续图像发布逻辑（不变）
        std::vector<uchar> buffer;
        cv::imencode(".jpg", frame, buffer, {cv::IMWRITE_JPEG_QUALITY, 80});
        // ... 发布ROS2消息 ...
    }
}

// 火焰跟踪逻辑：根据火焰位置控制云台转动
void HikvisionCameraNode::auto_track_flame(const cv::Rect& flame, int frame_width, int frame_height) {
    // 计算火焰中心与画面中心的偏移
    int center_x = frame_width / 2;
    int center_y = frame_height / 2;
    int flame_center_x = flame.x + flame.width / 2;
    int flame_center_y = flame.y + flame.height / 2;

    // 若偏移超过阈值（如50像素），发送云台控制指令
    if (std::abs(flame_center_x - center_x) > 50) {
        std::string direction = (flame_center_x > center_x) ? "right" : "left";
        int speed = std::min(10, std::abs(flame_center_x - center_x) / 10);  // 速度与偏移成正比
        this->control_ptz(direction, speed);  // 直接调用内部云台控制方法
    }
}