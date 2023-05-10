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

std::shared_ptr<Executor> executor;
//The node as a global variable
std::shared_ptr<MinimalSubscriber> node;

void start()
{
  int argc = 1;
  char name[] = "subscriber";
  char *argv[] = {name};

  rclcpp::init(argc, argv);
  executor = std::make_shared<Executor>();
  node = std::make_shared<MinimalSubscriber>();
  executor->add_node(node);
}
// PILA
// OPCION 1: devolver void* en start, recibirlo en el update y hacer cast a MinimalSubscriber
// OPCION 2: cola como atributo general, al principio del fichero

int update(vector3_transfer *ptr)
{
  executor->spin_some();
  if (!node->deque.empty())
  {
    auto msg = node->deque.front();
    node->deque.pop_front();
    ptr->x = msg->x;
    ptr->y = msg->y;
    ptr->z = msg->z;
    return 1;
  }
  return 0;
}

void end()
{
  node.reset();
  rclcpp::shutdown();
}

int dummy(int num)
{
  return num;
}

int main(int argc, char *argv[])
{
  start();
  vector3_transfer data;
  for (int i = 0; i < 5; i++)
  {
    update(&data);
    sleep(1);
  }
  end();
  return 0;
}
