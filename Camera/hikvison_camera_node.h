#ifndef HIKVISION_CAMERA_NODE_H
#define HIKVISION_CAMERA_NODE_H

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "hikvision_interfaces/srv/ptz_control.hpp"
#include "hikvision_interfaces/srv/set_resolution.hpp"
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include <openssl/md5.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <tinyxml2.h>

// 连接状态枚举
enum class ConnectionState {
    DISCONNECTED,    // 未连接
    CONNECTED,       // 已连接
    RECONNECTING,    // 重连中
    ERROR            // 错误状态
};

class HikvisionCameraNode : public rclcpp::Node {
public:
    // 构造函数，初始化节点和参数
    HikvisionCameraNode();
    
    // 析构函数，释放资源
    ~HikvisionCameraNode();

private:
    // 摄像头参数
    std::string camera_ip_;
    int camera_port_;
    std::string username_;
    std::string password_;
    std::string rtsp_url_;
    
    // 网络相关
    int socket_fd_;                     // Socket文件描述符
    struct sockaddr_in server_addr_;    // 服务器地址结构
    std::atomic<ConnectionState> connection_state_;  // 连接状态
    
    // 认证相关
    std::string nonce_;                 // 用于Digest认证的随机数
    std::string realm_ = "IP Camera";   // 海康设备固定realm
    
    // ROS2相关
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_;  // 图像发布者
    rclcpp::Service<hikvision_interfaces::srv::PtzControl>::SharedPtr ptz_control_srv_;  // 云台控制服务
    rclcpp::Service<hikvision_interfaces::srv::SetResolution>::SharedPtr set_resolution_srv_;  // 分辨率设置服务
    rclcpp::TimerBase::SharedPtr heartbeat_timer_;  // 心跳检测定时器
    rclcpp::TimerBase::SharedPtr image_capture_timer_;  // 图像采集定时器
    
    // 图像采集相关
    cv::VideoCapture cap_;              // 视频捕获对象
    std::atomic<bool> is_capturing_;    // 图像采集状态
    
    // 线程相关
    std::thread reconnect_thread_;      // 重连线程
    std::atomic<bool> thread_running_;  // 线程运行标志
    
    // 初始化摄像头连接
    bool init_camera_connection();
    
    // 建立Socket连接
    bool create_socket_connection();
    
    // 关闭Socket连接
    void close_socket_connection();
    
    // 生成Digest认证头
    std::string generate_digest_auth(const std::string& method, const std::string& uri);
    
    // MD5哈希计算
    std::string md5_hash(const std::string& input);
    
    // 发送ISAPI请求
    std::string send_isapi_request(const std::string& method, const std::string& uri, const std::string& body = "");
    
    // 解析XML响应获取RTSP地址
    bool parse_rtsp_url(const std::string& response);
    
    // 云台控制服务回调
    void handle_ptz_control(const std::shared_ptr<hikvision_interfaces::srv::PtzControl::Request> req,
                            std::shared_ptr<hikvision_interfaces::srv::PtzControl::Response> res);
    
    // 分辨率设置服务回调
    void handle_set_resolution(const std::shared_ptr<hikvision_interfaces::srv::SetResolution::Request> req,
                              std::shared_ptr<hikvision_interfaces::srv::SetResolution::Response> res);
    
    // 心跳检测函数
    void heartbeat_check();
    
    // 图像采集函数
    void capture_and_publish_image();
    
    // 重连函数
    void reconnect_task();
    
    // 从响应中提取nonce
    std::string extract_nonce(const std::string& response);
};

#endif // HIKVISION_CAMERA_NODE_H
