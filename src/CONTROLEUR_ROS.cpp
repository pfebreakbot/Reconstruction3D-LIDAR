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

    //ros::Rate loop_rate(400);

//*
     //bool pair=false;
     for(float i =0; i< 400 && ros::ok(); i+=1)//pour 0.9
     {	
       	//pair=!pair;
	 if(clientMPP.call(srvMPP))
         {
             //loop_rate.sleep();
            // ROS_INFO("MPP: %f pas",i);
		
		//if(pair)
		//{
             		for(float j =-1.0472; j<= 1.0472; j+=0.0174533)//pour 0.9
             		{
                 		srvSERVO.request.angle_rad=j;
		                if(clientSERVO.call(srvSERVO) == false)
                		      ROS_ERROR("Failed to call SERVO service");
		                 //ROS_INFO("MPP: %d pas sur 400",j);
		                 //loop_rate.sleep();
				 //if(j==-1.0472) sleep(1);
                		 if (clientLIDAR.call(srvLIDAR) == false)
		                     ROS_ERROR("Failed to call LIDAR service");
                		 //ROS_INFO("Successed to call LIDAR service");
		                 //loop_rate.sleep();
				//sleep(1);
	             }
			//srvSERVO.request.angle_rad=-1.0472;
			//clientSERVO.call(srvSERVO);
		/*}
		else
		{
			for(float j =1.0472; j >= -1.0472; j-=0.0174533)//pour 0.9
		        {
                 		 srvSERVO.request.angle_rad=j; 
		                 if(clientSERVO.call(srvSERVO) == false)
                		       	ROS_ERROR("Failed to call SERVO service");
                			//ROS_INFO("MPP: %d pas sur 400",j);
			                //loop_rate.sleep();
		                 if (clientLIDAR.call(srvLIDAR) == false)
                		      ROS_ERROR("Failed to call LIDAR service");
		                     //ROS_INFO("Successed to call LIDAR service");
                  			//loop_rate.sleep();
	              }
		}*/
         }
         else
         {
             ROS_ERROR("Failed to call MPP service");
             return 1;
         }
     }//*/	

    return 0;
}






































