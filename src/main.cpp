//clear && g++ main.cpp -lwiringPi -lpthread && ./a.out

#include "LIDAR.hpp"
#include "testTime.h"

using namespace std;

/*
class LIDAR
{
    public:
        LIDAR(){};

        int init(bool fasti2c = true)
        {
            int sys;
            if(fasti2c)
                sys=system("gpio load i2c 400");
            else
                sys=system("gpio load i2c");

            fd=wiringPiI2CSetup(0x62);
            if(fd == -1 || sys != 0) return 1;

            configuration();

            return 0;
        }

        int reset()
        {
            int returnValue=wiringPiI2CWriteReg8(fd,0x00,0x00);
            if(returnValue == -1) return 1;
            delay(20);
            return 0;
        }

        int configuration()
        {
            //int returnValue=wiringPiI2CWriteReg8(fd,0x04,0x00);
            int returnValue=wiringPiI2CWriteReg8(fd,0x1c,0x20);
            if(returnValue == -1) return 1;
            return 0;
        }

        int command(bool stablizePreampFlag = true)
        {
            int returnValue;

            while(((returnValue=wiringPiI2CReadReg8(fd,0x01))&0x01));
            if(returnValue == -1) return 1;

            if(stablizePreampFlag)
            {
                // Take acquisition & correlation processing with DC correction
                returnValue=wiringPiI2CWriteReg8(fd,0x00,0x04);
                if(returnValue == -1) return 1;
            }
            else
            {
                // Take acquisition & correlation processing without DC correction
                returnValue=wiringPiI2CWriteReg8(fd,0x00,0x03);
                if(returnValue == -1) return 1;
            }

            while(((returnValue=wiringPiI2CReadReg8(fd,0x01))&0x01));
            if(returnValue == -1) return 1;

            distH = wiringPiI2CReadReg8(fd,0x0f);
            distL = wiringPiI2CReadReg8(fd,0x10);

            return 0;
        }

        int mesure(bool debug = false)
        {
            if(debug)
            {
                printToBinary(distH);
                printToBinary(distL);
            }
            int distance=(distH<<8)+distL ;
            if (distance < 0) return 1;

            return distance;
        }

        void printToBinary(unsigned char number)
        {
            cout    << ((number&0x80)?1:0)
                    << ((number&0x40)?1:0)
                    << ((number&0x20)?1:0)
                    << ((number&0x10)?1:0)
                    << ((number&0x08)?1:0)
                    << ((number&0x04)?1:0)
                    << ((number&0x02)?1:0)
                    << ((number&0x01)?1:0)
                    << endl;
        }

    private:
        int fd;
        unsigned char distH,distL;
};
//*/

int main(int argc, char **argv)
{
    //TIME_INIT

    LIDAR lidar;

    lidar.init();

    lidar.reset();

    //cout << lidar.configuration() << endl;

    //TIME_START
    //for(int i=0;i<1000;i++)
    //{
        lidar.command();
        cout << lidar.mesure() << endl;
    //}
    //TIME_STOP

    return 0;
}


































