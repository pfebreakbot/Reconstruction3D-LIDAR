/**
 * \file Test_VUE.cpp
 * \brief ROS node to test VUE_ROS.cpp
 * \author pfebreakbot
 * \version 0.1
 * \date 4 January 2016
 */
#include "ros/ros.h"
#include "std_msgs/Float32.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Test_VUE_ROS");

    ros::NodeHandle n;

    ros::Publisher publisherMPP = n.advertise<std_msgs::Float32>("MPP_MEASURES", 1000);
    ros::Publisher publisherLIDAR = n.advertise<std_msgs::Float32>("LIDAR_MEASURES", 1000);
    ros::Publisher publisherSERVO = n.advertise<std_msgs::Float32>("SERVO_MEASURES", 1000);

    ros::Rate loop_rate(100);

    std_msgs::Float32 msg;

    bool plusmoins= false;

    for (float i = -1.0472; i< 1.0472 && ros::ok(); i+=0.0157)//pour 0.9°
    {
        msg.data = i;
        publisherSERVO.publish(msg);

        for(float j=0; j<6.28;j+=0.0157)
        {
            msg.data = j;
            publisherMPP.publish(msg);

            //msg.data=(plusmoins)?1.0:1.1;
            msg.data=1.0;
            plusmoins=!plusmoins;

            publisherLIDAR.publish(msg);
            loop_rate.sleep();

        }
    }
    return 0;
}
