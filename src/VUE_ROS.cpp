/**
 * \file VUE_ROS.cpp
 * \brief ROS node to convert and synchronize motors' angles and lidar distance to create point cloud
 * \author pfebreakbot
 * \version 0.1
 * \date 4 January 2016
 */
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include <sensor_msgs/PointCloud.h>
#include <cmath>



void polardToCartesian(float *x,float *y, float *z, float MPP, float SERVO, float LIDAR )
{
    *x=LIDAR*cos(SERVO)*cos(MPP);
    *y=LIDAR*cos(SERVO)*sin(MPP);
    *z=LIDAR*sin(SERVO);
}

class Lidar
{
    ros::Publisher *m_p_cloud_pub;
    sensor_msgs::PointCloud *m_p_cloud;
    float *m_p_LIDAR;
    float *m_p_MPP;
    float *m_p_SERVO;
    unsigned int *m_p_i;

    public:
        Lidar(ros::Publisher *p_cloud_pub, sensor_msgs::PointCloud *p_cloud, float *p_LIDAR,float *p_MPP,float *p_SERVO,unsigned int *p_i)
        {
            m_p_cloud_pub=p_cloud_pub;
            m_p_cloud=p_cloud;
            m_p_LIDAR=p_LIDAR;

            m_p_MPP=p_MPP;
            m_p_SERVO=p_SERVO;
            m_p_i=p_i;

        }
        void operator()(const std_msgs::Float32::ConstPtr& msg)
        {
            *m_p_LIDAR=msg->data;

            float x,y,z;
            polardToCartesian(&x,&y,&z,*m_p_MPP,*m_p_SERVO,*m_p_LIDAR);

            (*m_p_cloud).header.frame_id = "my_sensor_frame";
            (*m_p_cloud).header.stamp = ros::Time::now();
            (*m_p_cloud).points.resize(*m_p_i+1);

            (*m_p_cloud).points[*m_p_i].x = x;
            (*m_p_cloud).points[*m_p_i].y = y;
            (*m_p_cloud).points[*m_p_i].z = z;

            (*m_p_cloud_pub).publish(*m_p_cloud);
            *m_p_i=*m_p_i+1;
        }
};

class Mpp
{
    float *m_p_MPP;
    public:
        Mpp(float *p_MPP)
        {
            m_p_MPP=p_MPP;
        }
        void operator()(const std_msgs::Float32::ConstPtr& msg)
        {
            *m_p_MPP=msg->data;
        }
};

class Servo
{
    float *m_p_SERVO;
    public:
        Servo(float *p_SERVO)
        {
            m_p_SERVO=p_SERVO;
        }
        void operator()(const std_msgs::Float32::ConstPtr& msg)
        {
            *m_p_SERVO=msg->data;
        }
};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "VUE_ROS");
    ros::NodeHandle n;

    ros::Publisher cloud_pub = n.advertise<sensor_msgs::PointCloud>("my_cloud", 10);

    sensor_msgs::PointCloud cloud;

    float LIDAR=10,MPP=0,SERVO=-1.0471;
    unsigned int i=0;

    ros::Subscriber subMPP = n.subscribe<std_msgs::Float32>("MPP_MEASURES", 10, Mpp(&MPP));
    ros::Subscriber subSERVO = n.subscribe<std_msgs::Float32>("SERVO_MEASURES", 10, Servo(&SERVO));
    ros::Subscriber subLIDAR = n.subscribe<std_msgs::Float32>("LIDAR_MEASURES", 10, Lidar(&cloud_pub,&cloud,&LIDAR,&MPP,&SERVO,&i));

    ros::spin();


    return 0;
}


















































