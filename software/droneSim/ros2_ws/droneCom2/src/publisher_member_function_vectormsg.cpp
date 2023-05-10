#include <chrono>
#include <memory>
#include <iostream>
#include <fstream>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"

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
		string xyz;
		auto message = geometry_msgs::msg::Vector3();

		while(!archivo.eof()){//loop to read coordinates from file and send them as a message
			getline(archivo, xyz);
			message.x = std::stof(xyz[0]);
    		message.y = std::stof(xyz[1]);
    		message.z = std::stof(xyz[2]);
			RCLCPP_INFO(this->get_logger(), "Publishing: '%f' '%f' '%f'", message.x, message.y, message.z);
    		publisher_->publish(message);
		}    	
    	
	}
  	rclcpp::TimerBase::SharedPtr timer_;
  	rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr publisher_;

};

ifstream archivo;

int main(int argc, char* argv[])
{
	archivo.open("coordinates.txt", ios::in); //Abrimos el archivo de coordenadas en modo lectura

		if(archivo.fail()){
			cout<<"No se pudo abrir el archivo";
			exit(1);
		}
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MinimalPublisher>());
	rclcpp::shutdown();
	archivo.close();
	return 0;
}
