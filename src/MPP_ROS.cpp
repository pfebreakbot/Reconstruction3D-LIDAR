/**
 * \file MPP_ROS.cpp
 * \brief ROS node to initialize and step the step motor
 * \author pfebreakbot
 * \version 0.1
 * \date 4 January 2016
 */

#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "pfebreakbot/MPP.h"

#include <cstdio>
#include <wiringPi.h> // Include WiringPi library
#include <unistd.h>
#include <cstdlib>

#define pinDir 5 // Direction of the Motor
#define pinStep 6 // Signal de PAS (avancement)
#define pinEnable 13 // Activation du driver/pilote
#define Step0 19 // Controle des pas
#define Step1 26 // Controle des pas
//#define _debug_

class Command
{
    ros::Publisher m_publisher;
    int m_direction_mot;
    int m_precision;
    float *m_position;

    public:
    Command( ros::Publisher publisher,int direction_mot,int precision,float *position)
    {
        m_publisher = publisher;
        m_position = position;
        m_precision = precision;
        m_direction_mot = direction_mot;
    }

    bool operator()(pfebreakbot::MPP::Request& req, pfebreakbot::MPP::Response& res)
    {
        int delay1=0,delay2=0;

        digitalWrite(pinEnable,0); // Enable the Motor
        #ifdef _debug_
            int ch = digitalRead(pinEnable);// Check state of the Enable PIN
            printf("state of the Enable PIN: %d\n",dir);
        #endif

        digitalWrite(pinDir,m_direction_mot); // Direction avant
        #ifdef _debug_
            int dir=digitalRead(pinDir);
            printf("Direction: %d\n",dir);
        #endif

        switch(m_precision)
        {
            case 1:
                delay1=1000;
                delay2=5000;
                if (m_direction_mot ==0)
                    *m_position -= 0.0314159265359;
                else
                    *m_position += 0.0314159265359;
                break;
            case 2:
                delay1=200;
                delay2=2500;
                if (m_direction_mot ==0)
                    *m_position -= 0.0157079632679;
                else
                    *m_position += 0.0157079632679;
                break;
            case 8:
                delay1=200;
                delay2=800;
                if (m_direction_mot ==0)
                    *m_position -= 0.0039269908170;
                else
                    *m_position += 0.0039269908170;
                break;
            default:
                delay1=500;
                delay2=5000;
                if (m_direction_mot ==0)
                    *m_position -= 0.0019634954085;
                else
                    *m_position += 0.0019634954085;
                break;
        }

        // COMMAND OF NEXT STEP
        digitalWrite(pinStep,1);
        usleep(delay1);
        digitalWrite(pinStep,0);
        usleep(delay2);

	
        #ifdef _debug_
            printf("CONTROL Precision: %d\n",m_precision); //LOG
            printf("CONTROL POSITION: %f \n ",*m_position); //LOG
            printf("CONTROL FIN Boucle \n");
        #endif

        std_msgs::Float32 msg;
        msg.data = *m_position;
        ROS_INFO("%f", msg.data);
        m_publisher.publish(msg);

        return true;
    }
};


void init_pap(int precision)
{
    wiringPiSetupSys();
    system("gpio export 5 out");
    system("gpio export 6 out");
    system("gpio export 13 out");
    system("gpio export 19 out");
    system("gpio export 26 out");

    #ifdef _debug_
        system("gpio exports");
        printf("Initialisation Moteur Pap\n"); // Log
    #endif

    pinMode(pinEnable,OUTPUT);
    pinMode(pinDir   ,OUTPUT);//Motor's direction bit
    pinMode(pinStep  ,OUTPUT);//Step Pin -> to order to go to the next Step
    pinMode(Step0    ,OUTPUT);//M0-Bit 0 Precision Step
    pinMode(Step1    ,OUTPUT);//M1-Bit 1

    digitalWrite(pinStep, 0);

    switch(precision)
    {
        case 2:
            #ifdef _debug_
                printf("Precision: 1/2 STEP\n");// LOG
            #endif
            digitalWrite( Step0 , 1); //M0
            digitalWrite( Step1 , 0); //M1
            break;
        case 8:
            #ifdef _debug_
                printf("Precision: 1/8 STEP\n");// LOG
            #endif
            digitalWrite( Step0 , 0); //M0
            digitalWrite( Step1 , 1); //M1
            break;
        case 16:
            #ifdef _debug_
                printf("Precision: 1/16 STEP\n");// LOG
            #endif
            digitalWrite( Step0 , 1); //M0
            digitalWrite( Step1 , 1); //M1
            break;
        default:
            #ifdef _debug_
                printf("Precision: FULL STEP \n");// LOG
            #endif
            digitalWrite( Step0 , 0); //M0
            digitalWrite( Step1 , 0); //M1
            break;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "MPP");
    ros::NodeHandle n;

    init_pap(2);
    float x=0;

    ros::Publisher publisher = n.advertise<std_msgs::Float32>("MPP_MEASURES", 1000);
    ros::ServiceServer service = n.advertiseService<pfebreakbot::MPP::Request,pfebreakbot::MPP::Response>("MPP_COMMAND", Command(publisher,0,2,&x));
    ROS_INFO("MPP_ROS Ready");
    ros::spin();

    return 0;
}


