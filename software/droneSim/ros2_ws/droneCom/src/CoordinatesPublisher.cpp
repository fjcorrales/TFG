#include <chrono>
#include <memory>


#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"

using namespace std::chrono_literals;

class CoordinatesPublisher : public rclcpp::Node
{

public:
	
	CoordinatesPublisher()
	: Node("coordinates_publisher")
	{
		publisher_ = this->create_publisher<geometry_msgs::msg::Vector3>("topic", 10);
		timer_ = this->create_wall_timer(
			500ms, std::bind(&CoordinatesPublisher::timer_callback, this));
	}

private:
	
	void timer_callback()
	{
		auto message = geometry_msgs::msg::Vector3();

		while(3 == scanf("%lf %lf %lf", &(message.x), &(message.y), &(message.z))){//loop to read coordinates from file and send them as a message
			RCLCPP_INFO(this->get_logger(), "Publishing: '%f' '%f' '%f'", message.x, message.y, message.z);
    		publisher_->publish(message);
		}    	
    	
	}
  	rclcpp::TimerBase::SharedPtr timer_;
  	rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr publisher_;

};



int main(int argc, char* argv[])
{

	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<CoordinatesPublisher>());
	rclcpp::shutdown();
	return 0;
}
