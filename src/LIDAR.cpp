#include "LIDAR.hpp"

//LIDAR::LIDAR(){}

int LIDAR::init(bool fasti2c)
{
    int sys;
    if(fasti2c)
        sys=system("gpio load i2c 400");
    else
        sys=system("gpio load i2c");

    fd=wiringPiI2CSetup(0x62);
    std::cout << fd << std::endl;
    if(fd == -1 || sys != 0) return 1;

    int returnValue=reset();
    if(returnValue == -1) return 1;

    returnValue =configuration();
    if(returnValue == -1) return 1;

    return 0;
}

int LIDAR::reset()
{
    int returnValue=wiringPiI2CWriteReg8(fd,0x00,0x00);
    if(returnValue == -1) return 1;
    delay(20);
    return 0;
}

int LIDAR::configuration()
{
    //int returnValue=wiringPiI2CWriteReg8(fd,0x04,0x00);
    int returnValue=wiringPiI2CWriteReg8(fd,0x1c,0x20);
    if(returnValue == -1) return 1;
    return 0;
}

int LIDAR::command(bool stablizePreampFlag)
{
    std::cout << fd << std::endl;
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

int LIDAR::mesure(bool debug)
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

void LIDAR::printToBinary(unsigned char number)
{
    std::cout    << ((number&0x80)?1:0)
            << ((number&0x40)?1:0)
            << ((number&0x20)?1:0)
            << ((number&0x10)?1:0)
            << ((number&0x08)?1:0)
            << ((number&0x04)?1:0)
            << ((number&0x02)?1:0)
            << ((number&0x01)?1:0)
            << std::endl;
}