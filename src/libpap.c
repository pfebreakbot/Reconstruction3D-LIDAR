// libpap.c
#include "libpap.h"

float position = 0;

//INITIALISATION MOTEUR PAP
int init_pap(int precision)
{
    wiringPiSetupSys();

    system("gpio export 5 out");
    system("gpio export 6 out");
    system("gpio export 13 out");
    system("gpio export 19 out");
    system("gpio export 26 out");

    #ifdef _debug_
        system("gpio exports");
    #endif

    #ifdef _debug_
        printf("Initialisation Moteur Pap\n"); // Log
    #endif

    //SETUP PIN MODE
    pinMode(pinEnable,OUTPUT);
    pinMode(pinDir   ,OUTPUT);//Motor's direction bit
    pinMode(pinStep  ,OUTPUT);//Step Pin -> to order to go to the next Step
    pinMode(Step0    ,OUTPUT);//M0-Bit 0 Precision Step
    pinMode(Step1    ,OUTPUT);//M1-Bit 1

    // Initialisation step pin & Enable the motor
    digitalWrite(pinStep, 0);

    switch(precision)
    {
        case 2:
            #ifdef _debug_
                printf("Precision: 1/2 STEP\n");// LOG
            #endif
            digitalWrite( Step0 , 0); //M0
            digitalWrite( Step1 , 1); //M1
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
            digitalWrite( Step1 , 0); //M1
            break;
        default:
            #ifdef _debug_
                printf("Precision: FULL STEP \n");// LOG
            #endif
            digitalWrite( Step0 , 0); //M0
            digitalWrite( Step1 , 0); //M1
            break;
    }

    return 0;
}

// DIRECTION MOTEUR PAP
int direction_moteur_PAP(int direction_mot)
{
    // Ressource
    int dir = 0;
    // Direction horaires --> HIGH
    // Direction anti-horaire --> LOW

    digitalWrite(pinDir,direction_mot); // Direction avant
    dir = digitalRead(pinDir);
    #ifdef _debug_
        printf("Direction: %d\n",dir);
    #endif

    if((dir == 0) || (dir == 1))
        return 0;
    else
        return 1;
}

// GET STEP NUMBER IN FUNCTION OF STEP PRECISION AND ANGLE TO REACH IN RADIAN
int get_step_number(int step_precision, float angle_radian)
{

    float fstep_precision= (float)((float)step_precision)*((float)200);
    float coeff = (float)(angle_radian / 6.283185307);

    return ((int)(coeff * fstep_precision));// 360°=  6.283185307rd
}




int activate_motor()
{
    digitalWrite(pinEnable,0); // Enable the Motor
    int ch = digitalRead(pinEnable);// Check state of the Enable PIN

    return ch; // Return if OK or not
}

// FREE THE MOTOR'S ROTOR
int free_motor()
{
    digitalWrite(pinEnable,1); // Disable the motor -> rotor is free
    int ch = digitalRead(pinEnable);// Check state of the Enable PIN

    #ifdef _debug_
        printf("Enable: %d \n",ch); //LOG
    #endif

    return (!ch); // Return if OK or not
}

//  CONTROL MOTOR IS THE FUNCTION TO CALL TO MAKE A MOTOR COMMAND
float control_motor(int direction_mot,int precision, float *position)
{
    // Ressources
    int check_motor_activated = 1; // Return if the motor is well activated
    int check_direction = 1; // Check the direction set
    int step_number = 0 ; // Get Step Number to do
    int delay1 = 0;
    int delay2 = 0;

    check_motor_activated = activate_motor(); // Enable the Motor to get driven

    check_direction = direction_moteur_PAP(direction_mot); //direction_mot: Horaire: 1 - Anti-horaire:0

    switch(precision)
    {
        case 1:
            delay1=1000;
            delay2=5000;
            if (direction_mot ==0)
		*position -= 0.0314159265359;
	    else
		*position += 0.0314159265359;
            break;
        case 2:
            delay1=200;
            delay2=2500;
	    if (direction_mot ==0)
                *position -= 0.0157079632679;
            else
                *position += 0.0157079632679;
            break;
        case 8:
            delay1=200;
            delay2=800;
	    if (direction_mot ==0)
                *position -= 0.0039269908170;
            else
                *position += 0.0039269908170;
            break;
        default:
            delay1=500;
            delay2=5000;
	    if (direction_mot ==0)
                *position -= 0.0019634954085;
            else
                *position += 0.0019634954085;
            break;
    }

    // COMMAND OF NEXT STEP
    digitalWrite(pinStep,1);
    usleep(delay1);
    digitalWrite(pinStep,0);
    usleep(delay2);

    #ifdef _debug_
        printf("CONTROL Precision: %d\n",precision); //LOG
        printf("CONTROL POSITION: %f \n ",*position); //LOG
        printf("CONTROL FIN Boucle \n");
    #endif

    // Check the functions are executed
    if ((step_number!=0) && (check_direction == 0) && (check_motor_activated == 0))
        return *position; // Set OK if all the functions executed
    else
        return 1;
}




