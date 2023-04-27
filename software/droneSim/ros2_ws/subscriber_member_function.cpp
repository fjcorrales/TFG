// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>
#include <deque>
#include <unistd.h>

#include "subscriber_member_function.h"

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
      : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<geometry_msgs::msg::Vector3>(
        "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }
  std::deque<geometry_msgs::msg::Vector3::SharedPtr> deque;

private:
  void topic_callback(const geometry_msgs::msg::Vector3::SharedPtr msg) // const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%f' '%f' '%f'", msg->x, msg->y, msg->z);
    deque.push_back(msg);
  }
  rclcpp::Subscription<geometry_msgs::msg::Vector3>::SharedPtr subscription_;
};
typedef rclcpp::executors::SingleThreadedExecutor Executor;
// rclcpp::executors::SingleThreadedExecutor executor;
// rclcpp::executors::StaticSingleThreadedExecutor executor;
std::shared_ptr<Executor> executor;

void *start()
{
  int argc = 1;
  char name[] = "subscriber";
  char *argv[] = {name};

  rclcpp::init(argc, argv);
  executor = std::make_shared<Executor>();
  auto node = std::make_shared<MinimalSubscriber>();
  executor->add_node(node);
  return node.get();
}
// PILA
// OPCION 1: devolver void* en start, recibirlo en el update y hacer cast a MinimalSubscriber
// OPCION 2: cola como atributo general, al principio del fichero

int update(vector3_transfer *ptr, void *subscriber)
{
  MinimalSubscriber *minimalSubscriber = (MinimalSubscriber *)subscriber;
  executor->spin_some();
  if (!minimalSubscriber->deque.empty())
  {
    auto msg = minimalSubscriber->deque.front();
    minimalSubscriber->deque.pop_front();
    ptr->x = msg->x;
    ptr->y = msg->y;
    ptr->z = msg->z;
    return 1;
  }
  return 0;
}

void end()
{
  rclcpp::shutdown();
}

int main_og1(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
int main_og2(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor executor;
  auto node = std::make_shared<MinimalSubscriber>();
  executor.add_node(node);
  executor.spin();
  return 0;
}
int main_og3(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto executor = std::make_shared<Executor>();
  auto node = std::make_shared<MinimalSubscriber>();
  executor->add_node(node);
  executor->spin();
  rclcpp::shutdown();
  return 0;
}
int main_og4(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  executor = std::make_shared<Executor>();
  auto node = std::make_shared<MinimalSubscriber>();
  executor->add_node(node);
  executor->spin();
  rclcpp::shutdown();
  return 0;
}
int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  executor = std::make_shared<Executor>();
  auto node = std::make_shared<MinimalSubscriber>();
  executor->add_node(node);
  for (int i = 0; i < 2; i++)
  {
    executor->spin_some();
    sleep(1);
  }
  rclcpp::shutdown();
  return 0;
}