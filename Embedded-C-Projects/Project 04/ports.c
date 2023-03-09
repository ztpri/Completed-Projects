//------------------------------------------------------------------------------
//
//  Description: This file contains port initiation functions
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
#include "macros.h"





void Init_Ports(void){  //This function will call all initiation functions
  Init_Port1();
  
  Init_Port2();
  
  Init_Port3();
  
  Init_Port4();
  
  Init_Port5();
  
  Init_Port6();
  
}



void Init_Port1(void){  // This function will initiate port 1
  P1OUT = 0x00; // set all GPIO pins LOW
  P1DIR = 0x01; // Set all GPIO pins to input
  
  P1SEL0 &= ~RED_LED;    // set GPIO operation on bit 0
  P1SEL1 &= ~RED_LED;    // set GPIO operation on bit 1
  P1OUT &= ~RED_LED;     // initial output is 0
  P1DIR |= RED_LED;      // set as output
  
  P1SEL0 |= A1_SEEED;    // set GPIO operation on bit 0
  P1SEL1 |= A1_SEEED;    // set GPIO operation on bit 1
  
  P1SEL0 |= V_detect_L;    // set GPIO operation on bit 0
  P1SEL1 |= V_detect_L;    // set GPIO operation on bit 1
  
  P1SEL0 |= V_detect_R;    // set GPIO operation on bit 0
  P1SEL1 |= V_detect_R;    // set GPIO operation on bit 1
  
  P1SEL0 |= A4_SEEED;    // set GPIO operation on bit 0
  P1SEL1 |= A4_SEEED;    // set GPIO operation on bit 1 
  
  P1SEL0 |= V_thumb;    // set GPIO operation on bit 0
  P1SEL1 |= V_thumb;    // set GPIO operation on bit 1
  
  P1SEL0 |= UCA0RXD;    // set GPIO operation on bit 0
  P1SEL1 &= ~UCA0RXD;    // set GPIO operation on bit 1
  
  P1SEL0 |= UCA0TXD;    // set GPIO operation on bit 0
  P1SEL1 &= ~UCA0TXD;    // set GPIO operation on bit 1
}

void Init_Port2(void){  // This function will initiate port 2
  P2OUT = 0x00; // P2 set Low
  P2DIR = 0x01; // Set P2 direction to input
  
  P2SEL0 &= ~DAC_ENB; // P2_0 GPIO operation
  P2SEL1 &= ~DAC_ENB; // P2_0 GPIO operation
  P2OUT &= ~DAC_ENB; // Direction = output
  P2DIR |= DAC_ENB; // Direction = output
  
  P2SEL0 &= ~IR_LED; // IR_LED GPIO operation
  P2SEL1 &= ~IR_LED; // IR_LED GPIO operation
  P2OUT &= ~IR_LED; // Initial Value = Low / Off
  P2DIR |= IR_LED; // Direction = output
  
  P2SEL0 &= ~P2_2; // P2_2 GPIO operation
  P2SEL1 &= ~P2_2; // P2_2 GPIO operation
  P2DIR &= ~P2_2; // Direction = input
  
  P2SEL0 &= ~SW2; // SW2 Operation
  P2SEL1 &= ~SW2; // SW2 Operation
  P2OUT |= SW2; // Configure pullup resistor
  P2DIR &= ~SW2; // Direction = input
  P2REN |= SW2; // Enable pullup resistor
  
  // P2IES |= SW2; // P2.0 Hi/Lo edge interrupt
  // P2IFG &= ~SW2; // Clear all P2.6 interrupt flags
  // P2IE |= SW2; // P2.6 interrupt enabled
  P2SEL0 &= ~IOT_PROG_SEL; // IOT_PROG_SEL GPIO operation
  P2SEL1 &= ~IOT_PROG_SEL; // IOT_PROG_SEL GPIO operation
  P2OUT &= ~IOT_PROG_SEL; // Initial Value = Low / Off
  P2DIR |= IOT_PROG_SEL; // Direction = input
  
  P2SEL0 &= ~P2_5; // P2_5 GPIO operation
  P2SEL1 &= ~P2_5; // P2_5 GPIO operation
  P2DIR &= ~P2_5; // Direction = input
  
  P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
  P2SEL1 |= LFXOUT; // LFXOUT Clock operation
  P2SEL0 &= ~LFXIN; // LFXIN Clock operation
  P2SEL1 |= LFXIN; // LFXIN Clock operation
}

void Init_Port3(void){  // This function will initiate port 3
  P3OUT = 0x00; // set all GPIO pins LOW
  P3DIR = 0x01; // Set all GPIO pins to input
  
  P3SEL0 &= ~TEST_PROBE;        // set GPIO operation on bit 0
  P3SEL1 &= ~TEST_PROBE;        // set GPIO operation on bit 1
  P3OUT &= ~TEST_PROBE;         // set output LOW
  P3DIR |= TEST_PROBE;          // set pin to output
  
  P3SEL0 |= OPT_INT;        // set GPIO operation on bit 0
  P3SEL1 |= OPT_INT;        // set GPIO operation on bit 1
  
  P3SEL0 |= OA2N;        // set GPIO operation on bit 0
  P3SEL1 |= OA2N;        // set GPIO operation on bit 1
  
  P3SEL0 |= OA2P;        // set GPIO operation on bit 0
  P3SEL1 |= OA2P;        // set GPIO operation on bit 1
  
  
  P3SEL0 |= SMCLK_OUT;        // set GPIO operation on bit 0
  P3SEL1 &= ~SMCLK_OUT;        // set GPIO operation on bit 1
  P3OUT &= ~SMCLK_OUT;         // set output LOW
  P3DIR |= SMCLK_OUT;          // set pin to output
  
  // not sure if GPIO, but setting it as one to keep the pin safe
  P3SEL0 &= ~DAC_CNTL;        // set GPIO operation on bit 0
  P3SEL1 &= ~DAC_CNTL;        // set GPIO operation on bit 1
  P3OUT &= ~DAC_CNTL;         // set output LOW
  P3DIR |= DAC_CNTL;          // set pin to output
  
  P3SEL0 &= ~IOT_LINK;        // set GPIO operation on bit 0
  P3SEL1 &= ~IOT_LINK;        // set GPIO operation on bit 1
  P3OUT &= ~IOT_LINK;         // set output LOW
  P3DIR |= IOT_LINK;          // set pin to output
  
  P3SEL0 &= ~IOT_RESET;        // set GPIO operation on bit 0
  P3SEL1 &= ~IOT_RESET;        // set GPIO operation on bit 1
  P3OUT &= ~IOT_RESET;         // set output LOW
  P3DIR |= IOT_RESET;          // set pin to output
}

void Init_Port4(void){  // This function will initiate port 4
  P4OUT = 0x00; // P4 set Low
  P4DIR = 0x01; // Set P4 direction to input
  
  P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
  P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
  P4OUT |= RESET_LCD; // Set RESET_LCD Off [High]
  P4DIR |= RESET_LCD; // Set RESET_LCD direction to output
  
  P4SEL0 &= ~SW1; // SW1 GPIO operation
  P4SEL1 &= ~SW1; // SW1 GPIO operation
  P4OUT |= SW1; // Configure pullup resistor
  P4DIR &= ~SW1; // Direction = input
  P4REN |= SW1; // Enable pullup resistor
  
  // P4IES |= SW1; // P4.2 Hi/Lo edge interrupt
  // P4IFG &= ~SW1; // Clear all P2.6 interrupt flags
  // P4IE |= SW1; // P4.2 interrupt enabled
  
  P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
  P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation
  
  P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
  P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation
  
  P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
  P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
  P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
  P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output
  
  P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
  P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation
  
  P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
  P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation
  
  P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
  P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
}

void Init_Port5(void){  // This function will initiate port 5
  P5OUT = 0x00; // P5 set Low
  P5DIR = 0x01; // Set P5 direction to input
  
  P4SEL0 &= ~CHECK_BATT; // set GPIO operation on bit 0
  P4SEL1 &= ~CHECK_BATT; // set GPIO operation on bit 1
  P4OUT &= ~CHECK_BATT; // Set output as low
  P4DIR |= CHECK_BATT; // Set to output
  
  P4SEL0 &= ~V_BATT; // set GPIO operation on bit 0
  P4SEL1 &= ~V_BATT; // set GPIO operation on bit 1
  P4OUT &= ~V_BATT; // Set output as low
  P4DIR |= V_BATT; // Set to output
  
  P4SEL0 &= ~V_DAC; // set GPIO operation on bit 0
  P4SEL1 &= ~V_DAC; // set GPIO operation on bit 1
  P4OUT &= ~V_DAC; // Set output as low
  P4DIR |= V_DAC; // Set to output
  
  P4SEL0 &= ~v_3_3; // set GPIO operation on bit 0
  P4SEL1 &= ~v_3_3; // set GPIO operation on bit 1
  P4OUT &= ~v_3_3; // Set output as low
  P4DIR |= v_3_3; // Set to output
  
  P4SEL0 &= ~IOT_PROG_MODE; // set GPIO operation on bit 0
  P4SEL1 &= ~IOT_PROG_MODE; // set GPIO operation on bit 1
  P4OUT &= ~IOT_PROG_MODE; // Set output as low
  P4DIR |= IOT_PROG_MODE; // Set to output
}

void Init_Port6(void){  // This function will initiate port 6
  P6OUT = 0x00; // P6 set Low
  P6DIR = 0x01; // Set P6 direction to input
  
  P6SEL0 &= ~R_FORWARD; // set GPIO operation on bit 0
  P6SEL1 &= ~R_FORWARD; // set GPIO operation on bit 1
  P6OUT &= ~R_FORWARD; // Set output as low
  P6DIR |= R_FORWARD; // Set to output
  
  P6SEL0 &= ~L_FORWARD; // set GPIO operation on bit 0
  P6SEL1 &= ~L_FORWARD; // set GPIO operation on bit 1
  P6OUT &= ~L_FORWARD; // Set output as low
  P6DIR |= L_FORWARD; // Set to output
  
  P6SEL0 &= ~R_REVERSE; // set GPIO operation on bit 0
  P6SEL1 &= ~R_REVERSE; // set GPIO operation on bit 1
  P6OUT &= ~R_REVERSE; // Set output as low
  P6DIR |= R_REVERSE; // Set to output
  
  P6SEL0 &= ~L_REVERSE; // set GPIO operation on bit 0
  P6SEL1 &= ~L_REVERSE; // set GPIO operation on bit 1
  P6OUT &= ~L_REVERSE; // Set output as low
  P6DIR |= L_REVERSE; // Set to output
  
  P6SEL0 &= ~LCD_BACKLIGHT; // set GPIO operation on bit 0
  P6SEL1 &= ~LCD_BACKLIGHT; // set GPIO operation on bit 1
  P6OUT |= LCD_BACKLIGHT; // Set output as high
  P6DIR |= LCD_BACKLIGHT; // Set to output
  
  P6SEL0 &= ~P6_5; // set GPIO operation on bit 0
  P6SEL1 &= ~P6_5; // set GPIO operation on bit 1
  P6OUT &= ~P6_5; // Set output as low
  P6DIR |= P6_5; // Set to output
  
  P6SEL0 &= ~GRN_LED; // set GPIO operation on bit 0
  P6SEL1 &= ~GRN_LED; // set GPIO operation on bit 1
  P6OUT &= ~GRN_LED; // Set output as low
  P6DIR |= GRN_LED; // Set to output
}