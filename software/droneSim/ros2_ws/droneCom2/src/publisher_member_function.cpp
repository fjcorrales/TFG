#include <chrono>
#include <memory>
#include <iostream>
#include <fstream>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{

public:
	MinimalPublisher()
	: Node("minimal_publisher"),count_(0)
	{
		publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
		timer_ = this->create_wall_timer(
			500ms, std::bind(&MinimalPublisher::timer_callback, this));
	}

private:
	void timer_callback()
	{
		auto message = geometry_msgs::msg::Vector3();
    	message.x = getDirection("DIRECTION_X");
    	message.y = getDirection("DIRECTION_Y");
    	message.z = getDirection("DIRECTION_Z");
    	RCLCPP_INFO(this->get_logger(), "Publishing: '%f' '%f' '%f'", message.x, message.y, message.z);
    	publisher_->publish(message);
	}
  	rclcpp::TimerBase::SharedPtr timer_;
  	rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr publisher_;

};

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MinimalPublisher>());
	rclcpp::shutdown();
	return 0;
}
