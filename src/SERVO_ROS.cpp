#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "pfebreakbot/SERVO.h"

#define M_90_to_RAD 1.5707963268
#define M_74_to_RAD 1.29154


class Command
{
    ros::Publisher m_publisher;

    public:
    Command( ros::Publisher publisher)
    {
        m_publisher = publisher;

    }

    bool operator()(pfebreakbot::SERVO::Request& req, pfebreakbot::SERVO::Response& res)
    {
        //-60   60

        //+90 -> 1.5707963268

        //30  150

        //0  180
        float angle=((req.angle_rad+M_74_to_RAD)*180)/M_PI;

        FILE *f1=fopen("/dev/servoblaster","w");
        if(f1==NULL) { ROS_ERROR("cannot open /dev/servoblaster file"); return false;}

        fprintf(f1,"0=%dus\n",(int) (angle*10)+600);
        fclose(f1);

        std_msgs::Float32 msg;
        msg.data = req.angle_rad;
        ROS_INFO("%f", msg.data);
        m_publisher.publish(msg);

        return true;
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "SERVO");
    ros::NodeHandle n;

    ros::Publisher publisher = n.advertise<std_msgs::Float32>("SERVO_MEASURES", 1000);
    ros::ServiceServer service = n.advertiseService<pfebreakbot::SERVO::Request,pfebreakbot::SERVO::Response>("SERVO_COMMAND", Command(publisher));
    ROS_INFO("SERVO_ROS Ready");
    ros::spin();

    return 0;
}
