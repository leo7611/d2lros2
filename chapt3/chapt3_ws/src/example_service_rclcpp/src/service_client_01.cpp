#include "rclcpp/rclcpp.hpp"

class ServiceClient01 : public rclcpp::Node {
public:
  // 构造函数,有一个参数为节点名称
  ServiceClient01(std::string name) : Node(name) {
    RCLCPP_INFO(this->get_logger(), "client节点已启动：%s.", name.c_str());
    // 创建客户端
    client_ = this->create_client<example_interfaces::srv::AddTwoInts>(
        "add_two_ints");
  }
  void send_request(int a, int b) {
    RCLCPP_INFO(this->get_logger(), "计算%d+%d", a, b);
    // 1.等待服务端上线
    while (!cli)

      // 创建请求
      auto request =
          std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = a;
    request->b = b;
    // 等待服务端响应
    auto result_callback = std::bind(&ServiceClient01::result_callback_, this,
                                     std::placeholders::_1);
    // 调用客户端的异步服务请求
  }

private:
  // 声明客户端
  rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;
  void result_callback_(
      rclcpp::Client<example_interfaces::srv::AssTwoInts>::SharedFuture
          result_feature) {
    auto response = result_feature.get();
    RCLCPP_INFO(this->get_logger(), "Sum计算结果: %ld", response->sum);
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  /*创建对应节点的共享指针对象*/
  //   使用std::make_shared函数可以创建一个智能指针，它会自动管理内存的释放，避免内存泄漏的风险。
  auto node = std::make_shared<ServiceClient01>("service_client_01");
  //   ServiceClient01 node("service_client_01");
  /* 运行节点，并检测退出信号*/
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}