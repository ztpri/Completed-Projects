//------------------------------------------------------------------------------
//
//  Description: This file contains wheel functions
//
//
//  Zachary T Price
//  September 8
//  Built with IAR Embedded Workbench Version: V7.20.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"



void Forward(unsigned int perc_speed);
void FullStop(void);
void SpinCW(unsigned int perc_speed);
void ForwardLine(unsigned int right, unsigned int left);
void SpinCCW(unsigned int perc_speed);



void Forward(unsigned int perc_speed){
  RIGHT_FORWARD_SPEED = perc_speed;
  LEFT_FORWARD_SPEED = perc_speed + CORRECTION;
}

void FullStop(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void SpinCW(unsigned int perc_speed){
  RIGHT_REVERSE_SPEED = perc_speed - HUNDRED - HUNDRED - HUNDRED;
  LEFT_FORWARD_SPEED = perc_speed + HUNDRED + HUNDRED + HUNDRED;
}

void SpinCCW(unsigned int perc_speed){
  RIGHT_FORWARD_SPEED = perc_speed - HUNDRED - HUNDRED - HUNDRED;
  LEFT_REVERSE_SPEED = perc_speed + HUNDRED + HUNDRED + HUNDRED;
}

void ForwardLine(unsigned int right, unsigned int left){
  RIGHT_FORWARD_SPEED = right;
  LEFT_FORWARD_SPEED = left + HUNDRED + HUNDRED + HUNDRED;
}