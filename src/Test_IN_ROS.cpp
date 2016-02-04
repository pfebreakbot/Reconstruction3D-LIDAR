#include "ros/ros.h"
#include "pfebreakbot/LIDAR.h"
#include "pfebreakbot/MPP.h"
#include "pfebreakbot/SERVO.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Test_IN_ROS");

    ros::NodeHandle n;

    ros::ServiceClient clientLIDAR = n.serviceClient<pfebreakbot::LIDAR>("LIDAR_COMMAND");

    ros::ServiceClient clientMPP = n.serviceClient<pfebreakbot::MPP>("MPP_COMMAND");

    ros::ServiceClient clientSERVO = n.serviceClient<pfebreakbot::SERVO>("SERVO_COMMAND");

    pfebreakbot::LIDAR srvLIDAR;

    pfebreakbot::MPP srvMPP;

    pfebreakbot::SERVO srvSERVO;

    float angle=0.0;

    for (int i = 0; i< 400; i++)
    {

        if (clientLIDAR.call(srvLIDAR))
            ROS_INFO("Successed to call LIDAR service");
        else
            ROS_ERROR("Failed to call LIDAR service");

        if (clientMPP.call(srvMPP))
            ROS_INFO("Successed to call MPP service");
        else
            ROS_ERROR("Failed to call MPP service");

        angle+=0.017;
        srvSERVO.request.angle_rad=angle;
        if (clientSERVO.call(srvSERVO))
            ROS_INFO("Successed to call SERVO service");
        else
            ROS_ERROR("Failed to call SERVO service");
       //usleep(10000);
    }
    return 0;
}


























