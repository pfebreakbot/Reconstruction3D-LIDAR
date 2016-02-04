#include "ros/ros.h"
#include "std_msgs/Float32.h"


void LIDAR_MEASURESCallback(const std_msgs::Float32::ConstPtr& msg)
{
  ROS_INFO("LIDAR_MEASURES: [%f]", msg->data);
}

void MPP_MEASURESCallback(const std_msgs::Float32::ConstPtr& msg)
{
  ROS_INFO("MPP_MEASURES: [%f]", msg->data);
}

void SERVO_MEASURESCallback(const std_msgs::Float32::ConstPtr& msg)
{
  ROS_INFO("SERVO_MEASURES: [%f]", msg->data);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Test_OUT_ROS");
  ros::NodeHandle n;

  ros::Subscriber subLIDAR = n.subscribe("LIDAR_MEASURES", 1000, LIDAR_MEASURESCallback);
  ros::Subscriber subMPP = n.subscribe("MPP_MEASURES", 1000, MPP_MEASURESCallback);
  ros::Subscriber subSERVO = n.subscribe("SERVO_MEASURES", 1000, SERVO_MEASURESCallback);

  ros::spin();

  return 0;
}