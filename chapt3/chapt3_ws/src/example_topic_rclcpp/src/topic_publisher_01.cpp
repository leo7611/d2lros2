#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
class TopicPublisher01 : public rclcpp::Node {
public:
  // 构造函数,有一个参数为节点名称
  TopicPublisher01(std::string name) : Node(name) {
    // RCLCPP_INFO(this->get_logger(), "%s节点已经启动.", name.c_str());
    RCLCPP_INFO(this->get_logger(), "大家好，我是%s.", name.c_str());
    // 创建发布者
    command_publisher_ =
        this->create_publisher<std_msgs::msg::String>("command", 10);
    // 创建定时器，500ms为周期，定时发布
    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(500),
        std::bind(&TopicPublisher01::timer_callback, this));
  }

private:
  // 声名定时器指针
  rclcpp::TimerBase::SharedPtr timer_;
  void timer_callback() {
    // 创建消息
    std_msgs::msg::String message;
    message.data = "Hello, ROS2!";
    // 日志打印
    // 使用RCLCPP_INFO宏打印消息，消息内容为"Publishing: '%s'"。
    // 在C++中，c_str()函数用于获取一个C风格的字符串（以null结尾的字符数组）的指针。
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    // 发布消息
    command_publisher_->publish(message);
  }
  // 声明话题发布者指针
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  /*创建对应节点的共享指针对象*/
  auto node = std::make_shared<TopicPublisher01>("topic_publisher_01");
  /* 运行节点，并检测退出信号*/
  rclcpp::spin(
      node); //它的作用是让节点开始执行自己的事件循环，接收和处理来自ROS
             // 2系统的消息和事件。rclcpp::spin(node)函数会在节点对象node上调用一个无限循环，该循环会不断地检查节点是否有新的消息到达或其他事件发生。当有消息到达时，节点会调用相应的回调函数来处理消息。这样，节点可以实时地与其他节点进行通信，并执行相应的操作。
  rclcpp::shutdown(); // rclcpp::shutdown()函数是ROS 2中用于关闭节点的函数。
  return 0;
}