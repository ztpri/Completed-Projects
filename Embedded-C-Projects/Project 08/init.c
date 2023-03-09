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

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"


extern char display_line[DISPLAY_LINE_ROW][DISPLAY_LINE_COLUMN];
extern char *display[DISPLAY_FOUR];
extern volatile unsigned char display_changed;
extern volatile unsigned int update_display_count;
extern volatile unsigned char update_display;




void Init_Conditions(void){
  //------------------------------------------------------------------------------
  int i;

  for(i=GO_ZERO;i<GO_ONCE;i++){
    display_line[GO_ZERO][i] = RESET_STATE;
    display_line[GO_ONE][i] = RESET_STATE;
    display_line[GO_TWO][i] = RESET_STATE;
    display_line[GO_THREE][i] = RESET_STATE;
  }
  display_line[GO_ZERO][GO_TEN] = GO_ZERO;
  display_line[GO_ONE][GO_TEN] = GO_ZERO;
  display_line[GO_TWO][GO_TEN] = GO_ZERO;
  display_line[GO_THREE][GO_TEN] = GO_ZERO;

  display[GO_ZERO] = &display_line[GO_ZERO][GO_ZERO];
  display[1] = &display_line[GO_ONE][GO_ZERO];
  display[2] = &display_line[GO_TWO][GO_ZERO];
  display[3] = &display_line[GO_THREE][GO_ZERO];
  update_display = GO_ZERO;
  update_display_count = GO_ZERO;

  // Interrupts are disabled by default, enable them.
  enable_interrupts();
  //------------------------------------------------------------------------------
}


