//------------------------------------------------------------------------------
//  MSP430FR235x Demo - SAC-L3, DAC Buffer Mode
//
//  Description: Configure SAC-L3 for DAC Buffer Mode. Use the 12 bit DAC to
//  output positive ramp. The OA is set in buffer mode to improve DAC output
//  drive strength. Internal 2.5V reference is selected as DAC reference.
//  Observe the output of OA0O pin with oscilloscope.
//  ACLK = n/a, MCLK = SMCLK = default DCODIV ~1MHz.
//
//                MSP430FR235x
//             -------------------
//         /|\|                   |
//          | |                   |
//          --|RST     DAC12->OA0O|--> oscilloscope
//            |                   |
//            |                   |
//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"

unsigned int DAC_data;
void Init_REF(void);

void Init_DAC(void){

  DAC_data = 4000;
  SAC3DAT  = DAC_data;                  // Initial DAC data
  SAC3DAC  = DACSREF_0;                 // Select AVCC as DAC reference
  SAC3DAC |= DACLSEL_0;                 // DAC latch loads when DACDAT written

  SAC3OA   = NMUXEN;                    // SAC Negative input MUX controL
  SAC3OA  |= PMUXEN;                    // SAC Positive input MUX control
  SAC3OA  |= PSEL_1;                    // 12-bit reference DAC source selected
  SAC3OA  |= NSEL_1;                    // Select negative pin input
  SAC3OA  |= OAPM;                      // Select low speed and low power mode
  SAC3PGA  = MSEL_1;                    // Set OA as buffer mode
  SAC3OA  |= SACEN;                     // Enable SAC
  SAC3OA  |= OAEN;                      // Enable OA

  P3OUT   &= ~DAC_CNTL;                 // Set output to Low
  P3DIR   &= ~DAC_CNTL;                 // Set direction to input
  P3SELC  |=  DAC_CNTL;                 // DAC_CNTL DAC operation
  SAC3DAC |=  DACEN;                     // Enable DAC

  DAC_data =  750;
  SAC3DAT  =  DAC_data;                   // Set DAC to 6.5v.
  
  


// The following line should be done in a timmer interrupt after the board
// has been powered for 5 seconds
  //P2OUT   |=  DAC_ENB;                  // Value = High [enabled]
}

void Init_REF(void){
  // Configure reference module
  PMMCTL0_H = PMMPW_H; // Unlock the PMM registers
  PMMCTL2 = INTREFEN; // Enable internal reference
  PMMCTL2 |= REFVSEL_2; // Select 2.5V reference
  while(!(PMMCTL2 & REFGENRDY)); // Poll till internal reference settles
  // Using a while statement is not usually recommended without an exit strategy.
  // This while statement is the suggested operation to allow the reference to settle.
}

/*
// The interrupt is not used
#pragma vector = SAC1_SAC3_VECTOR
__interrupt void SAC3_ISR(void){
  switch(__even_in_range(SAC0IV,SACIV_4)){
  case SACIV_0: break;
  case SACIV_2: break;
  case SACIV_4:
//   DAC_data++;
//   DAC_data &= 0xFFF;
//   SAC3DAT = DAC_data;                 // DAC12 output positive ramp
    break;
  default: break;
  }
}*/
