#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "pfebreakbot/LIDAR.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

class Command
{
    int m_fd;
    ros::Publisher m_publisher;

    public:
    Command(int fd, ros::Publisher publisher)
    {
        m_fd = fd;
        m_publisher = publisher;

    }
    bool operator()(pfebreakbot::LIDAR::Request& req, pfebreakbot::LIDAR::Response& res)
    {

        while((wiringPiI2CReadReg8(m_fd,0x01))&0x01);//status register
        //wiringPiI2CWriteReg8(m_fd,0x00,0x03);//without DC correction
        wiringPiI2CWriteReg8(m_fd,0x00,0x04);//with DC correction
        while((wiringPiI2CReadReg8(m_fd,0x01))&0x01);//status register
        unsigned char distH = wiringPiI2CReadReg8(m_fd,0x0f);
        unsigned char distL = wiringPiI2CReadReg8(m_fd,0x10);
        //*
        float val1=((distH<<8)+distL);

        wiringPiI2CWriteReg8(m_fd,0x00,0x04);//without DC correction
        while((wiringPiI2CReadReg8(m_fd,0x01))&0x01);//status register
        distH = wiringPiI2CReadReg8(m_fd,0x0f);
        distL = wiringPiI2CReadReg8(m_fd,0x10);
        float val2=((distH<<8)+distL);//*/

        std_msgs::Float32 msg;
        //msg.data = ((distH<<8)+distL);

        msg.data= (val1+val2)/200;

        ROS_INFO("%f", msg.data);
        m_publisher.publish(msg);

        return true;
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "LIDAR");
    ros::NodeHandle n;

    system("gpio load i2c 400");
    int fd=wiringPiI2CSetup(0x62);
    wiringPiI2CWriteReg8(fd,0x00,0x00);//reset
    delay(20);
    wiringPiI2CWriteReg8(fd,0x1c,0x20);//low noise, low sensitivity

    ros::Publisher publisher = n.advertise<std_msgs::Float32>("LIDAR_MEASURES", 1000);

    ros::ServiceServer service = n.advertiseService<pfebreakbot::LIDAR::Request,pfebreakbot::LIDAR::Response>("LIDAR_COMMAND", Command(fd,publisher));
    ROS_INFO("LIDAR_ROS Ready");
    ros::spin();

    return 0;
}

























