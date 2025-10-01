#include "rclcpp/rclcpp.hpp"
#include "hikvision_camera_node.h"

int main(int argc, char * argv[]) {
    // 初始化ROS2
    rclcpp::init(argc, argv);
    
    // 创建并运行节点
    auto node = std::make_shared<HikvisionCameraNode>();
    rclcpp::spin(node);
    
    // 关闭ROS2
    rclcpp::shutdown();
    return 0;
}
