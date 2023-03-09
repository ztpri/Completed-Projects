//------------------------------------------------------------------------------
//
//  Description: This file contains the initiation
//
//
//  Zachary T Price
//  September 8
//  Built with IAR Embedded Workbench Version: V7.20.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------



void Stop(void);


void Stop(void){
  P6OUT &= ~R_FORWARD;
  P6OUT &= ~L_FORWARD;
  return;
}