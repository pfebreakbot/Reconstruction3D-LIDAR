#include "libpap.h"

int main(void)
{
    float x=0;
    float *position=&x;

    if(init_pap(8) == 0)
        printf("INIT OK\n");

    printf("MOTOR's COMMAND \n ");

    int i;
    for(i=0;i<1600;i++)
    {
        if(control_motor(0,8,position) != 0)
            printf("Commande Moteur bien envoyee pour la %deme fois \n ",i);
    }


    //free_motor();
    return 0;
}




