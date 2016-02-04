#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <cstdlib>
#include <unistd.h>

class LIDAR
{       int fd;
        unsigned char distH,distL;

    public:
        //LIDAR();
        int init(bool fasti2c = true);
        int reset();
        int configuration();
        int command(bool stablizePreampFlag = true);
        int mesure(bool debug = false);
        void printToBinary(unsigned char number);
};