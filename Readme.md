<!--
 * @Description: 
 * @Author: lq qiang.li@seres.cn
 * @Date: 2024-05-11 10:13:51
 * @LastEditTime: 2024-05-11 10:13:58
 * @LastEditors: lq qiang.li@seres.cn
-->
cd chapt3/chapt3_ws/
colcon build --packages-select example_topic_rclcpp
source install/setup.bash
ros2 run example_topic_rclcpp topic_publisher_01


