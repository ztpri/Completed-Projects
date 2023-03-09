//------------------------------------------------------------------------------
//
//  Description: This file contains all interrupts
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


extern volatile unsigned char update_display;
extern unsigned int clk_int_count; // clock interrupt counter





void Init_Timer_B0(void) {
  TB0CTL = TBSSEL__SMCLK; // SMCLK source
  TB0CTL |= TBCLR; // Resets TB0R, clock divider, count direction
  TB0CTL |= MC__CONTINOUS; // Continuous up
  TB0CTL |= ID__8; // Divide clock by 8
  
  TB0EX0 = TBIDEX__8; // Divide clock by an additional 8
  
  TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
  TB0CCTL0 |= CCIE; // CCR0 enable interrupt
  
  // TB0CCR1 = TB0CCR1_INTERVAL; // CCR1
  // TB0CCTL1 |= CCIE; // CCR1 enable interrupt
  // TB0CCR2 = TB0CCR2_INTERVAL; // CCR2
  // TB0CCTL2 |= CCIE; // CCR2 enable interrupt
  
  TB0CTL &= ~TBIE; // Disable Overflow Interrupt
  TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
  ++clk_int_count;
  update_display = 1;
  P1OUT ^= RED_LED;
  TB0CCR0 += TB0CCR0_INTERVAL;
}