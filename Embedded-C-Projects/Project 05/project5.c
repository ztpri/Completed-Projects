//------------------------------------------------------------------------------
//
//  Description: This file contains the movement functions for project 5
//
//
//  Zachary Price
//  2021
//  Built with IAR Embedded Workbench Version: V7.10.2 (8.0.6.4651)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"


// if(P6OUT & (L_FORWARD | L_REVERSE))  or  if((P6OUT & L_FORWARD) && (P6OUT & L_REVERSE))    for checking if both are on


void CompleteStop(void);        // turn off all forward and reverse movements
void Forward(void);             // make car go forward
void TurnLeft(void);
void TurnRight(void);
void Reverse(void);
void BackoutLeft(void);
void BackoutRight(void);
unsigned int CheckMagicSmoke(void);


void CompleteStop(void){
  P6OUT &= ~R_FORWARD;
  P6OUT &= ~L_FORWARD;
  
  P6OUT &= ~R_REVERSE;
  P6OUT &= ~L_REVERSE;
  
  return;
}

void Forward(void){
  P6OUT &= ~R_REVERSE;  // turn off reverse first for safety
  P6OUT &= ~L_REVERSE;
  
  P6OUT |= R_FORWARD;
  P6OUT |= L_FORWARD;
  
  return;
}

void TurnLeft(void){
  CompleteStop();
  
  P6OUT |= R_FORWARD;   // right forward and left off so it goes left
  P6OUT |= L_REVERSE;
  
  return;
}

void TurnRight(void){
  P6OUT &= ~R_REVERSE;  // turn off reverse first for safety
  P6OUT &= ~L_REVERSE;
  
  P6OUT &= ~R_FORWARD;   // left forward and right off so it goes right
  P6OUT |= L_FORWARD;
  
  return;
}

void Reverse(void){
  P6OUT &= ~R_FORWARD;  // turn off forward first for safety
  P6OUT &= ~L_FORWARD;
  
  P6OUT |= R_REVERSE;
  P6OUT |= L_REVERSE;
  
  return;
}

void BackoutLeft(void){
  CompleteStop();
  
  P6OUT |= R_REVERSE;
  P6OUT |= L_FORWARD;
  
  return;
}

void BackoutRight(void){
  P6OUT &= ~R_FORWARD;  // turn off forward first for safety
  P6OUT &= ~L_FORWARD;
  
  P6OUT &= ~R_REVERSE;
  P6OUT |= L_REVERSE;
  
  return;
}

unsigned int CheckMagicSmoke(void){
  unsigned int smoke_state;
  
  if(( (P6OUT & L_FORWARD) && (P6OUT & L_REVERSE) ) || ( (P6OUT & R_FORWARD) && (P6OUT & R_REVERSE) )){
    CompleteStop();
    
    P1OUT |= RED_LED;
    
    smoke_state = SMOKE;
  }
  else{
    smoke_state = CLEAR;
  }
  
  return smoke_state;
}