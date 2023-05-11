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
	: Node("minimal_publisher")
	{
		publisher_ = this->create_publisher<geometry_msgs::msg::Vector3>("topic", 10);
		timer_ = this->create_wall_timer(
			500ms, std::bind(&MinimalPublisher::timer_callback, this));
	}

private:

	void timer_callback()
	{
		
		auto message = geometry_msgs::msg::Vector3();

		while(fgets(archivo, 2048, xyz)){//loop to read coordinates from file and send them as a message
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


FILE * archivo;
char * xyz;

int main(int argc, char* argv[])
{
	
	archivo = fopen("coordinates.txt", "r"); //Abrimos el archivo de coordenadas en modo lectura

	if(archivo == NULL){
		std::cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MinimalPublisher>());
	rclcpp::shutdown();
	fclose(archivo);
	return 0;
}
