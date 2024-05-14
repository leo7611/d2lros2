/*
 * @Description:
 * @Author: lq qiang.li@seres.cn
 * @Date: 2024-05-11 10:59:16
 * @LastEditTime: 2024-05-13 09:56:55
 * @LastEditors: lq qiang.li@seres.cn
 */
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
class TopicSubscribe01 : public rclcpp::Node {
public:
  // 构造函数,有一个参数为节点名称
  TopicSubscribe01(std::string name) : Node(name) {
    RCLCPP_INFO(this->get_logger(), "大家好，我是%s.", name.c_str());
    /*
    std::shared_ptr< SubscriptionT > rclcpp::Node::create_subscription 	(
    const std::string &  	topic_name, const rclcpp::QoS &  	qos,
                CallbackT &&  	callback,
                const SubscriptionOptionsWithAllocator< AllocatorT > &
    options = SubscriptionOptionsWithAllocator<AllocatorT>(), typename
    MessageMemoryStrategyT::SharedPtr  	msg_mem_strat = (
    MessageMemoryStrategyT::create_default()    )
        )
     */
    /*
    callback参数对应的是使用std::bind绑定的回调函数。在这里，std::bind函数
    用于将TopicSubscribe01类的成员函数topic_callback绑定到当前对象this上，
    并使用std::placeholders::_1占位符表示接收到的消息参数。
     */
    // 创建一个订阅者订阅话题
    command_subscribe_ = this->create_subscription<std_msgs::msg::String>(
        "command", 10,
        std::bind(&TopicSubscribe01::command_callback, this,
                  std::placeholders::_1));
  }

private:
  // 声明一个订阅者
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscribe_;
  // 收到话题数据的回调函数
  void command_callback(const std_msgs::msg::String::SharedPtr msg) {
    double speed = 0.0f;
    if (msg->data == "HelloROS2") {
      speed = 0.2f;
    }
    RCLCPP_INFO(this->get_logger(), "收到话题数据：%s, 速度：%f",
                msg->data.c_str(), speed);
  }
};

int main(int argc, char **argv) {
  /* rclcpp初始化*/
  rclcpp::init(argc, argv);
  /*创建对应节点的共享指针对象*/
  auto node = std::make_shared<TopicSubscribe01>("topic_subscribe_01");
  /* 运行节点，并检测退出信号*/
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}