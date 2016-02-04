#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv )
{

    FILE *f1=NULL;
    float angle=0;
    int angleint=0;
    float pi = 3.1415926535;

    if( argc==1)
        printf("An argument from 0 to 3.1415926535 is needed\n");
    if(argc > 2)
        printf("Only one argument from 0 to 3.1415926535 is needed");
    angle=atof(argv[1]);
    printf("angle saisi %f\n",angle);

    angle=angle*180/pi;

    f1=fopen("/dev/servoblaster","w");
    if(f1==NULL)
    {
        printf("Error opening the file \n");
        return 0;
    }
    angleint = (int) (angle *10)+600;

    fprintf(f1,"0=%dus\n",angleint);

    printf("%f°\n",angle);

    printf("0=%dus\n",angleint);

    fclose(f1);

    return 0;
}

