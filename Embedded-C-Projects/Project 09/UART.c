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
extern char Rx_ring[STRING_SIZE];
extern char Tx_string[STRING_SIZE];
extern unsigned int tx_state;           // pc tx string
extern unsigned int proc_state;
extern char PC_string[STRING_SIZE];     // pc rx string
extern unsigned int pc_i;
extern unsigned int pc_state;
extern unsigned int com_state;
extern unsigned int clk_two; // clock 2 interrupt counter
extern unsigned int command_dog;
extern char IOT_string[IOT_STRING_SIZE];        // iot rx string
extern char IOT_deliver[IOT_STRING_SIZE];       // iot tx string
extern unsigned int iot_i;
extern unsigned int iot_k;
extern unsigned int iot_state;
extern unsigned int str_clk;
extern unsigned int str_clk2;
extern unsigned int rst_clk;


void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);


//      initiations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

void Init_Serial_UCA1(void){
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
  UCA1CTLW0 = GO_ZERO;
  UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA1CTLW0 &= ~UCPEN; // No Parity
  UCA1CTLW0 &= ~UCSYNC;
  UCA1CTLW0 &= ~UC7BIT;
  UCA1CTLW0 |= UCMODE_0;
  
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // UCA?MCTLW = UCSx + UCFx + UCOS16
  
  UCA1BRW = BAUD_115200 ; // 115,200 baud
  UCA1MCTLW = BAUD_115200_OTHER ;   
  UCA1CTLW0 &= ~UCSWRST ; // release from reset
  //UCA1TXBUF = NULL; // Prime the Pump
  UCA1IE |= UCRXIE; // Enable RX interrupt
  UCA1IE &= ~UCTXIE; // Disable TX interrupt
}




//      Communications
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  unsigned int temp;
  
  switch(__even_in_range(UCA0IV,HEX_EIGHT)){
    case GO_ZERO: // Vector 0 - no interrupt
      break;
      
    case GO_TWO: // Vector 2 – RXIFG
    // code for Receive
      
      IOT_string[iot_i] = UCA0RXBUF;
      temp = IOT_string[iot_i];
      iot_i++;
      
      if(temp == CAR_RET){
        iot_i = sizeof(IOT_string);
      }
      
      if(iot_i >= sizeof(IOT_string) - GO_ONE){
        iot_i = GO_ZERO;
        
        pc_state = SEND_TO;
        iot_state = GET_FROM;
        str_clk = GO_ZERO;
      }
      
      break;
      
    case GO_FOUR: // Vector 4 – TXIFG
    // Code for Transmit
      UCA0TXBUF = IOT_deliver[iot_k];
      iot_k++;
      
      if(iot_k >= sizeof(IOT_deliver)){
        iot_k = GO_ZERO;
        tx_state = SENT;
        iot_state = GET_FROM;
        
        UCA0IE &= ~UCTXIE; // Disable TX interrupt
      }
      
      break;
      
    default: break;
  }
}

#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
  char temp;
  
  switch(__even_in_range(UCA1IV,HEX_EIGHT)){
    case GO_ZERO: // Vector 0 - no interrupt
      break;
      
    case GO_TWO: // Vector 2 – RXIFG
    // code for Receive
      temp = UCA1RXBUF;
      
      // if command is found, check which command
      if(command_dog == BARKING){
        switch(temp){
          case FAST_RATE:
            baud_state = UPPER_RATE;
            UCA0BRW = BAUD_115200 ;
            UCA0MCTLW = BAUD_115200_OTHER ;
            
            break;
          
          case SLOW_RATE:
            baud_state = LOWER_RATE;
            UCA0BRW = BAUD_9600 ;
            UCA0MCTLW = BAUD_9600_OTHER ;
            break;
            
          case CARET:
            strcpy(Tx_string, "   EGG!   ");
            pc_state = NOW;
            
            break;
            
          case RESET:
            iot_state = RST;
            rst_clk = GO_ZERO;
            break;
            
          case WIPE:
            pc_i = GO_ZERO;
            break;
            
          default: break;
        }
      }
      
      // check if command is incoming, and if we keep received character
      if(temp == CARET){
        command_dog = BARKING;
      }
      else{
        if(command_dog == QUIET){       // if already quiet
          PC_string[pc_i] = temp;       // save character
          pc_i++;       // increment index
        }
        
        command_dog = QUIET;
      }
      
      // if end of desired string, send string
      if(temp == CAR_RET){
        pc_i = sizeof(PC_string);
        
        iot_state = SEND_TO;
        str_clk2 = GO_ZERO;
      }
      
      
      // check ring buffer
      if(pc_i >= (sizeof(PC_string) - GO_ONE)){
        pc_i = GO_ZERO;
        
        
      }
      
      break;
      
    case GO_FOUR: // Vector 4 – TXIFG
    // Code for Transmit
      
      UCA1TXBUF = Tx_string[tx_i];
      tx_i++;
      
      
      if(tx_i >= sizeof(Tx_string)){
        tx_i = GO_ZERO;
        tx_state = SENT;
        
        UCA1IE &= ~UCTXIE; // Disable TX interrupt
        iot_state = GET_FROM;
        pc_state = GET_FROM;
      }
      
      
      break;
      
    default: break;
  }
}
