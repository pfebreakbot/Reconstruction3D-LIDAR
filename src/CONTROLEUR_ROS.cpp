/**
 * \file LIDAR_ROS.cpp
 * \brief ROS control node to the pfebreakbot nodes
 * \author pfebreakbot
 * \version 0.1
 * \date 4 January 2016
 */

#include "ros/ros.h"
#include "pfebreakbot/LIDAR.h"
#include "pfebreakbot/MPP.h"
#include "pfebreakbot/SERVO.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "CONTROLEUR_ROS");
    ros::NodeHandle n;

    ros::ServiceClient clientLIDAR = n.serviceClient<pfebreakbot::LIDAR>("LIDAR_COMMAND");
    ros::ServiceClient clientMPP = n.serviceClient<pfebreakbot::MPP>("MPP_COMMAND");
    ros::ServiceClient clientSERVO = n.serviceClient<pfebreakbot::SERVO>("SERVO_COMMAND");

    pfebreakbot::LIDAR srvLIDAR;
    pfebreakbot::MPP srvMPP;
    pfebreakbot::SERVO srvSERVO;

    for(float i =0; i< 400 && ros::ok(); i+=1)//pour 0.9
    {
        if(clientMPP.call(srvMPP))
        {

            for(float j =-1.0472; j<= 1.0472; j+=0.0174533)//pour 0.9
            {
                srvSERVO.request.angle_rad=j;
                if(clientSERVO.call(srvSERVO) == false)
                    ROS_ERROR("Failed to call SERVO service");
                if (clientLIDAR.call(srvLIDAR) == false)
                    ROS_ERROR("Failed to call LIDAR service");
            }
        }
        else
        {
             ROS_ERROR("Failed to call MPP service");
             return 1;
        }
     }

    return 0;
}






































