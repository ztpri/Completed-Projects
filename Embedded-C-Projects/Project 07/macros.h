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
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // 6 GREEN LED
#define SW2                  (0x08) // 2.3 SW2
#define SW1                  (0x02) // 4.1 SW1
#define Time_Sequence_Rate         (50)
#define S1250 (1250/Time_Sequence_Rate) //
#define S1000 (1000/Time_Sequence_Rate) //
#define S750   (750/Time_Sequence_Rate) //
#define S500   (500/Time_Sequence_Rate) //
#define S250   (250/Time_Sequence_Rate) //
#define S10    (10/Time_Sequence_Rate)
#define DISPLAY_LINE_ROW (4)
#define DISPLAY_LINE_COLUMN (11)
#define DISPLAY_FOUR (4)
#define GO_ZERO (0)
#define GO_ONE (1)
#define GO_TWO (2)
#define GO_THREE (3)
#define GO_FOUR (4)
#define GO_FIVE (5)
#define GO_SIX (6)
#define GO_SEVEN (7)
#define GO_EIGHT (8)
#define GO_NINE (9)
#define GO_TEN (10)
#define GO_ONCE (11)
#define GO_DOCE (12)
#define GO_TRECE (13)
#define SMOKE (12)
#define CLEAR (24)
#define NUM_TIMER_CYCLES (2)        // number of path cycles completed
#define TB0CCR0_INTERVAL (6250)        // 50ms
#define TB0CCR1_INTERVAL (6250)
#define P4PUD (P4OUT)
#define ON (1)
#define OFF (0)
#define BOUNCING (0)
#define STILL (1)
#define i0 (0)  // index number x, x = 0 in this case
#define i1 (1)
#define i2 (2)
#define i3 (3)
#define i4 (4)
#define i5 (5)
#define i6 (6)
#define i7 (7)
#define i8 (8)
#define i9 (9)
#define THOUSAND (1000)
#define HUNDRED (100)
#define HEX_CV (0x30)
#define CH_W (0x00)
#define CH_L (0x01)     // ch 2
#define CH_R (0x02)     // ch 3
#define YES (1)
#define NO (0)
#define THREE_SEC (60)  // amount interrupts needed for 3 seconds to pass
#define ONE_SEC (20)
#define BOUNCE_BOUNCE (40)      // interrupts needed for debounce to finish
#define WAIT (0)
#define INTER (1)       // intercepting/finding line
#define TURN (2)
#define CIRC (3)
#define STOP (4)
#define PERP (5)
#define TB0CCR2_INTERVAL (1000)
#define RIGHT_STANDARD (172)
#define LEFT_STANDARD (155)
#define PERC_CORRECTION (0)
#define BASE_SPEED (5000);
#define FIFTY (50)
#define RIGHT (12)
#define LEFT (24)
#define FULL_ON (5)
#define NINETY (90)
#define UNDER (0)
#define OVER (1)
#define CAL (202)
#define READY (101)

#define RIGHT_FORWARD_SPEED (TB3CCR1)
#define LEFT_FORWARD_SPEED (TB3CCR2)
#define RIGHT_REVERSE_SPEED (TB3CCR3)
#define LEFT_REVERSE_SPEED (TB3CCR4)
#define WHEEL_PERIOD (40000)       // arbitrary number used as a ratio, 100/number is the percentage of speed where number is some integer below the period     
#define WHEEL_OFF (0)
#define CORRECTION (360)

#define INTERCEPT_SPEED (4000)
#define SPIN_SPEED (17000)


// port 1 define
#define RED_LED         (0x01)  // RED LED 0
#define A1_SEEED        (0x02)  // A1_SEEED
#define V_detect_L      (0x04)  // V_DETECT_L
#define V_detect_R      (0x08)  // V_DETECT_R
#define V_BAT           (0x10)  // A4_SEEED / BATTERY
#define A4_SEED         (0x10)  // A4_SEEED / BATTERY
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
// port 3 GPIO or switch if defiens
#define USE_GPIO (0x00)
#define USE_SMCLK (0x01)


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