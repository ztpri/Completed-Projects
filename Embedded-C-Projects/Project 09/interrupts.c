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
extern unsigned int clk_one; // clock 1 interrupt counter
extern unsigned int clk_two; // clock 2 interrupt counter
extern unsigned int debounce_count_one;
extern unsigned int debounce_count_two;
extern unsigned int debounce_state_one;
extern unsigned int debounce_state_two;
extern unsigned int sw1_state;
extern unsigned int LCD_state;
extern unsigned int LCD_update_count;
extern unsigned int ADC_Thumb;
extern unsigned int ADC_Channel;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern char L_det_string[GO_FIVE];
extern char R_det_string[GO_FIVE];
extern char temp_char[GO_FIVE];
extern unsigned int IR_state;
extern unsigned int car_state;
extern unsigned int DAC_wait;
extern unsigned int baud_state;
extern unsigned int tx_state;
extern unsigned int rx_i;
extern unsigned int tx_i;
extern unsigned int com_state;
extern char Rx_string[STRING_SIZE];
extern char Tx_string[STRING_SIZE];
extern unsigned int str_clk;
extern unsigned int str_clk2;
extern unsigned int rst_clk;

void Init_Timer_B0(void);
void Init_SW1_Int(void);
void Init_SW2_Int(void);
void Debounce(void);
void Init_ADC(void);

void Init_Timer_B3(void);



//      initiations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Init_Timer_B0(void) {
  TB0CTL = TBSSEL__SMCLK; // SMCLK source
  TB0CTL |= TBCLR; // Resets TB0R, clock divider, count direction
  TB0CTL |= MC__CONTINOUS; // Continuous up
  TB0CTL |= ID__8; // Divide clock by 8
  
  TB0EX0 = TBIDEX__8; // Divide clock by an additional 8
  
  TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
  TB0CCTL0 |= CCIE; // CCR0 enable interrupt
  
  TB0CCR1 = TB0CCR1_INTERVAL; // CCR1
  TB0CCTL1 &= ~CCIE; // 
  
  TB0CCR2 = TB0CCR2_INTERVAL; // CCR2
  TB0CCTL2 &= ~CCIE; // 
  
  TB0CTL &= ~TBIE; // Disable Overflow Interrupt
  TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
}

void Init_SW1_Int(void){
  P4IFG &= ~SW1; // interrupt flag SW1 cleared
  P4IE |= SW1; // SW1 interrupt Enabled
}

void Init_SW2_Int(void){
  P2IFG &= ~SW2; // interrupt flag SW1 cleared
  P2IE |= SW2; // SW2 interrupt Enabled
}



void Init_Timer_B3(void) {
  //------------------------------------------------------------------------------
  // SMCLK source, up count mode, PWM Right Side
  // TB3.1 P6.0 R_FORWARD
  // TB3.2 P6.1 L_FORWARD
  // TB3.3 P6.2 R_REVERSE
  // TB3.4 P6.3 L_REVERSE
  //------------------------------------------------------------------------------
  TB3CTL = TBSSEL__SMCLK; // SMCLK
  TB3CTL |= TBCLR; // Clear TAR
  TB3CTL |= MC__UP; // Up Mode
  
  TB3CCR0 = WHEEL_PERIOD; // PWM Period
  //TB3CCTL0 |= CCIE;
  
  TB3CCTL1 = OUTMOD_7; // CCR1 reset/set
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM duty cycle
  
  TB3CCTL2 = OUTMOD_7; // CCR2 reset/set
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM duty cycle
  
  TB3CCTL3 = OUTMOD_7; // CCR3 reset/set
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
  
  TB3CCTL4 = OUTMOD_7; // CCR4 reset/set
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM duty cycle
  //------------------------------------------------------------------------------
}




void Init_ADC(void){
  //------------------------------------------------------------------------------
  // V_DETECT_L (0x04) // Pin 2 A2
  // V_DETECT_R (0x08) // Pin 3 A3
  // V_THUMB (0x20) // Pin 5 A5
  //------------------------------------------------------------------------------
  // ADCCTL0 Register
  ADCCTL0 = 0; // Reset
  ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
  ADCCTL0 |= ADCMSC; // MSC
  ADCCTL0 |= ADCON; // ADC ON
  
  // ADCCTL1 Register
  ADCCTL2 = GO_ZERO; // Reset
  ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
  ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
  ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
  ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
  ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
  ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
  // ADCCTL1 & ADCBUSY identifies a conversion is in process
  
  // ADCCTL2 Register
  ADCCTL2 = GO_ZERO; // Reset
  ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
  ADCCTL2 |= ADCRES_0; // ADC resolution 10b = 12 bit (14 clock cycle conversion time)
  ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
  ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
  
  // ADCMCTL0 Register
  ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
  ADCMCTL0 |= ADCINCH_5; // V_THUMB (0x20) Pin 5 A5
  ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
  ADCCTL0 |= ADCENC; // ADC enable conversion.
  ADCCTL0 |= ADCSC; // ADC start conversion.
}


//      interrupts
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma vector = TIMER0_B0_VECTOR       // central clock used for flickering and debouncing
__interrupt void Timer0_B0_ISR(void){
  ++clk_one;
  ++clk_two;
  ++LCD_update_count; // once = 4, check if any display lines have changed
  ++DAC_wait;
  ++str_clk;
  ++str_clk2;
  ++rst_clk;
  
  /*
  if(!debounce_state_one){
    ++debounce_count_one;
  }
  
  if(!debounce_state_two){
    ++debounce_count_two;
  }
  */
  
  TB0CCR0 += TB0CCR0_INTERVAL;
}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
  switch(__even_in_range(TB0IV,14)){
    case 0: break; // No interrupt
    
    case 2: // CCR1
    //...... Add What you need happen in the interrupt ......
      debounce_count_one++;
      
      if(debounce_count_one > BOUNCE_BOUNCE){
        P4IE |= SW1;
        //P2IE |= SW2;
    
        debounce_state_one = STILL;
        debounce_count_one = GO_ZERO;
        TB0CCTL1 &= ~CCIE;
      }
      
      TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
      break;
      
    case 4: // CCR2
    //...... Add What you need happen in the interrupt ......
      debounce_count_two++;
      
      if(debounce_count_two > BOUNCE_BOUNCE){
        //P4IE |= SW1;
        P2IE |= SW2;
    
        debounce_state_two = STILL;
        debounce_count_two = GO_ZERO;
        TB0CCTL2 &= ~CCIE;
      }
      
      TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
      break;
      
    case 14: // overflow
    //...... Add What you need happen in the interrupt ......
      break;
    
    default: break; 
}
//----------------------------------------------------------------------------
}



#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void){      // if switch is hit, turn off LCD backlight and stall LCD flicker
  // Switch 1
  if (P4IFG & SW1) {
    P4IE &= ~SW1;
    P4IFG &= ~SW1; // IFG SW1 cleared
    
    debounce_state_one = BOUNCING;
    debounce_count_one = GO_ZERO;
    TB0CCTL1 |= CCIE;
    
    /*
    switch(com_state){
      case WAITING:
        com_state = RECEIVE;
        break;
        
      case RECEIVE:
        com_state = TRANSMIT;
        UCA0TXBUF = NULL; // Prime the Pump
        //strcpy(Tx_string, Rx_string);
        tx_i = GO_ZERO;
        rx_i = GO_ZERO;
        tx_state = SENDING;
        
        break;
        
      case TRANSMIT:
        com_state = RECEIVE;
        tx_i = GO_ZERO;
        rx_i = GO_ZERO;
        //tx_state = SENDING;
        
        break;
    }
    */
    
    sw1_state++;
  }
}

#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){      // if switch is hit, start car in intercepting mode and turn on IR
  // Switch 2
  if (P2IFG & SW2) {
    P2IE &= ~SW2;
    P2IFG &= ~SW2; // IFG SW2 cleared
    
    debounce_state_two = BOUNCING;
    debounce_count_two = GO_ZERO;
    TB0CCTL2 |= CCIE;
    
    sw1_state++;
    clk_two = GO_ZERO;
  }
}

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
    case ADCIV_NONE:
      break;
    
    case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
      // before its previous conversion result was read.
      break;
  
    case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
      break;
    
    case ADCIV_ADCHIIFG: // Window comparator interrupt flags
      break;
    
    case ADCIV_ADCLOIFG: // Window comparator interrupt flag
      break;
    
    case ADCIV_ADCINIFG: // Window comparator interrupt flag
      break;
    
    case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
      ADCCTL0 &= ~ADCENC; // Disable ENC bit.
        switch (ADC_Channel++){
          case CH_W: // Channel 5 - thumb wheel
            ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A5, as it wont store value until channel stops
            ADCMCTL0 |= ADCINCH_2; // Enable Next channel A2
            ADC_Thumb = ADCMEM0;
            
            
            break;
            
          case CH_L: // Channel 2 - Left Detector
            ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2, as it wont store value until channel stops
            ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
            ADC_Left_Detect = ADCMEM0; // Move result into Global
            //ADC_Left_Detect = ADC_Left_Detect >> 2; // Divide the result by 4
            
            
            break;
            
          case CH_R: // Channel 3 - Right Detector
            ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A3
            ADCMCTL0 |= ADCINCH_5; // Enable Next channel A5
            ADC_Right_Detect = ADCMEM0; // Move result into Global
            //ADC_Right_Detect = ADC_Left_Detect >> 2; // Divide the result by 4
            
            
            ADC_Channel = CH_W;
            break;
            
          default:
            break;
        }
        
        ADCCTL0 |= ADCENC; // Enable Conversions
        ADCCTL0 |= ADCSC; // Start next sample
    
    default:
      break;
  }
}


//      functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Debounce(void){
  if(!debounce_state_one){
    if(debounce_count_one > BOUNCE_BOUNCE){
      P4IE |= SW1;
      //P2IE |= SW2;
    
      debounce_state_one = STILL;
      debounce_count_one = GO_ZERO;
    }
  }
  
  if(!debounce_state_two){
    if(debounce_count_two > BOUNCE_BOUNCE){
      //P4IE |= SW1;
      P2IE |= SW2;
    
      debounce_state_two = STILL;
      debounce_count_two = GO_ZERO;
    }
  }
  
  /*
  while(debounce_count < BOUNCE_BOUNCE){
    debounce_state = BOUNCING;
  }
    
  debounce_state = STILL;
  
  P4IE |= SW1;
  P2IE |= SW2;
  */
}

