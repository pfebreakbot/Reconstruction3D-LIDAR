// libpap.h
#ifndef LIBPAP
#define LIBPAP

#include <stdio.h>
#include <wiringPi.h> // Include WiringPi library
#include <unistd.h>
#include <stdlib.h>

//DEFINE CONTROL GPIO PINS
#define pinDir 5 // Direction of the Motor
#define pinStep 6 // Signal de PAS (avancement)
#define pinEnable 13 // Activation du driver/pilote
#define Step0 19 // Controle des pas
#define Step1 26 // Controle des pas
//#define _debug_

int init_pap(int step_precision);
int direction_moteur_PAP(int direction_mot);
int get_step_number(int step_precision, float angle_radian);
int retour_angle_moteur_PAP(int step_nb);
int activate_motor();
int free_motor();
float control_motor(int direction_mot,int precision, float *position);

#endif

