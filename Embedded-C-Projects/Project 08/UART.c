//------------------------------------------------------------------------------
//
//  Description: This file contains the UART stuff
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

extern char Tx_char;
extern char Rx_char;
extern unsigned int baud_state;
extern unsigned int tx_i;
extern char Tx_array_one[GO_NINE];
extern unsigned int rx_i;
extern char Rx_string[STRING_SIZE];
extern char Tx_string[STRING_SIZE];
extern unsigned int tx_state;


void Init_Serial_UCA0(void);


void Init_Serial_UCA0(void){
//------------------------------------------------------------------------------
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
// 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
// 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
//------------------------------------------------------------------------------
// 17 is for baud rate of 460800, 4 is for 115200
// Configure eUSCI_A0 for UART mode
  UCA0CTLW0 = GO_ZERO;
  UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA0CTLW0 &= ~UCPEN; // No Parity
  UCA0CTLW0 &= ~UCSYNC;
  UCA0CTLW0 &= ~UC7BIT;
  UCA0CTLW0 |= UCMODE_0;
  
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // UCA?MCTLW = UCSx + UCFx + UCOS16
  
  UCA0BRW = BAUD_115200 ; // 115,200 baud
  UCA0MCTLW = BAUD_115200_OTHER ;   
  UCA0CTLW0 &= ~UCSWRST ; // release from reset
  UCA0TXBUF = NULL; // Prime the Pump
  UCA0IE |= UCRXIE; // Enable RX interrupt
  UCA0IE &= ~UCTXIE; // Disable TX interrupt
}





#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  //unsigned int temp;
  
  switch(__even_in_range(UCA0IV,HEX_EIGHT)){
    case GO_ZERO: // Vector 0 - no interrupt
      break;
      
    case GO_TWO: // Vector 2 – RXIFG
    // code for Receive
      if(UCA0RXBUF == NULL){
      }
      else{
        Rx_string[rx_i] = UCA0RXBUF;
        rx_i++;
      }
      
      if(rx_i >= sizeof(Rx_string)){
        rx_i = GO_ZERO;
      }
      
      break;
      
    case GO_FOUR: // Vector 4 – TXIFG
    // Code for Transmit
      UCA0TXBUF = Rx_string[tx_i];
      tx_i++;
      
      if(tx_i >= sizeof(Rx_string)){
        tx_i = GO_ZERO;
        tx_state = SENT;
        
        UCA0IE &= ~UCTXIE; // Disable TX interrupt
      }
      
      //UCA0IE &= ~UCTXIE; // Disable TX interrupt
      
      break;
      
    default: break;
  }
}
