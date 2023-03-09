//------------------------------------------------------------------------------
//
//  Description: This file contains macros
//
//
//  Zachary T Price
//  September 8
//  Built with IAR Embedded Workbench Version: V7.20.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes
#include  "msp430.h"
#include  "functions.h"
#include <string.h>

// General defines
#define RESET_STATE             (0)
#define ALWAYS                  (1)
#define ORIGINAL             (0x00) //
#define Time_Sequence_Rate         (50)
#define S1250 (1250/Time_Sequence_Rate) //
#define S1000 (1000/Time_Sequence_Rate) //
#define S750   (750/Time_Sequence_Rate) //
#define S500   (500/Time_Sequence_Rate) //
#define S250   (250/Time_Sequence_Rate) //
#define S100   (100/Time_Sequence_Rate) //
#define S200   (200/Time_Sequence_Rate) //
#define S300   (300/Time_Sequence_Rate) //
#define S400   (400/Time_Sequence_Rate) //
#define S600   (600/Time_Sequence_Rate) //
#define S700   (700/Time_Sequence_Rate) //
#define S800   (800/Time_Sequence_Rate) //
#define S900   (900/Time_Sequence_Rate) //
#define S50    (50/Time_Sequence_Rate)  //
#define S10    (10/Time_Sequence_Rate)  //
#define DISPLAY_LINE_ROW (4)
#define DISPLAY_LINE_COLUMN (11)
#define DISPLAY_FOUR (4)
#define GO_ZERO (0)
#define GO_ONE (1)
#define GO_TWO (2)
#define GO_THREE (3)
#define GO_FIVE (5)
#define GO_TEN (10)
#define GO_ONCE (11)
#define CIRCLE (1)
#define FIGURE (2)
#define TRIANGLE (3)
#define NONE (0)
#define PWM_TIME (10)
#define SINGLE_CIRCLE (66) // 64
#define loop_one (1)
#define loop_two (2)
#define STRAIGHT (0)
#define CURVE (1)
#define CURVE2 (2)
#define STRAIGHT2 (3)
#define LINE_TIME (15)
#define LINE_TIME2 (5)
#define SINGLE_CURVE (27)
#define SINGLE_CURVE2 (17)
#define END (4)


// port 1 define
#define RED_LED         (0x01)  // RED LED 0
#define A1_SEEED        (0x02)  // A1_SEEED
#define V_detect_L      (0x04)  // V_DETECT_L
#define V_detect_R      (0x08)  // V_DETECT_R
#define A4_SEEED        (0x10)  // A4_SEEED
#define V_thumb         (0x20)  // V_THUMB
#define UCA0RXD         (0x40)  // Back Channel UCA0RXD
#define UCA0TXD         (0x80)  // Back Channel UCA0TXD

// port 2 define
#define DAC_ENB         (0x01) // DAC Power Circuit Enable
#define IR_LED          (0x02) // IR LED on/off signal
#define P2_2            (0x04)
#define SW2             (0x08) // Switch 2
#define IOT_PROG_SEL    (0x10) // IOT_PROG_SEL 
#define P2_5            (0x20)
#define LFXOUT          (0x40) // XOUTR
#define LFXIN           (0x80) // XINR

// port 3 define
#define TEST_PROBE      (0x01) // 0 TEST PROBE
#define OPT_INT         (0x02) // 1 OPT_INT
#define OA2N            (0x04) // 2 Photodiode Circuit
#define OA2P            (0x08) // 3 Photodiode Circuit
#define SMCLK_OUT       (0x10) // 4 SMCLK
#define DAC_CNTL        (0x20) // 5 DAC signal from Processor
#define IOT_LINK        (0x40) // 6 IOT_LINK 
#define IOT_RESET       (0x80) // 7 IOT_RESET

// port 4 define
#define RESET_LCD (0x01) // 0 LCD Reset
#define SW1 (0x02) // 1 SW1
#define UCA1RXD (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) // 4 Chip Select
#define UCB1CLK (0x20) // 5 SPI mode - clock output—UCB1CLK
#define UCB1SIMO (0x40) // 6 UCB1SIMO
#define UCB1SOMI (0x80) // 7 UCB1SOMI

// port 5 define
#define CHECK_BATT      (0x01)  // battery check
#define V_BATT          (0x02)  // battery voltage
#define V_DAC           (0x04)  // DAC voltage
#define v_3_3           (0X08)  // 3.3 volts
#define IOT_PROG_MODE   (0x10)  // IOT program mode

// port 6 define
#define R_FORWARD       (0x01)      // right forwward
#define L_FORWARD       (0x02)      // left forward
#define R_REVERSE       (0x04)      // right reverse
#define L_REVERSE       (0x08)      // left reverse
#define LCD_BACKLIGHT   (0x10)      // LCD BACKLIGHT
#define P6_5            (0x20)      // GPIO
#define GRN_LED         (0x40)      // green LED