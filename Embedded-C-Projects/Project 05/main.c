//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Zachary Price
//  Sep 2021
//  Built with IAR Embedded Workbench Version: V7.10.2 (8.0.6.4651)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"


// Global Variables
extern char pwm;
volatile char slow_input_down;
extern char display_line[DISPLAY_LINE_ROW][DISPLAY_LINE_COLUMN];
extern char *display[DISPLAY_FOUR];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned int update_display_count;
extern volatile unsigned char update_display;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
volatile unsigned int wheel_run;
extern unsigned int wheel_on_count;
extern char wheels_on;
extern unsigned int running;
extern char wheel_direction;
extern char number_of_runs;
extern char move_state;
extern char next_state;
extern char last_state;
extern volatile unsigned char display_changed;
extern volatile unsigned int update_display_count;
char display_adc;
char state;
extern char iot_start;
unsigned int movement_state;
unsigned int go_around;
unsigned int safe_state;
unsigned int clk_int_count;     // clock interrupt counter

unsigned int smoke_state = CLEAR;

void main(void){
  //------------------------------------------------------------------------------
  // Main Program
  // This is the main routine for the program. Execution of code starts here.
  // The operating system is Back Ground Fore Ground.
  //
  //------------------------------------------------------------------------------
  Init_Ports();                        // Initialize Ports
  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timer_B0();                       // Initialize Timers
  Init_ADC();
  Init_DAC();  
  Init_LCD();                          // Initialize LCD
  Init_Switches();                     // Initialize Switches

  display_mode = ORIGINAL;
  display_adc = GO_ONE;
//  state = ADC_OPERATION;

  strcpy(display_line[GO_ZERO], "~~~~~~~~~~");
  update_string(display_line[GO_ZERO], GO_ZERO);
  strcpy(display_line[GO_ONE], "~~~~~~~~~~");
  update_string(display_line[GO_ONE], GO_ONE);
  strcpy(display_line[GO_TWO], "~~~~~~~~~~");
  update_string(display_line[GO_TWO], GO_TWO);
  strcpy(display_line[GO_THREE], "~~~~~~~~~~");
  update_string(display_line[GO_THREE], GO_THREE);
//  strcpy(display_line[GO_THREE], "L    R    ");
//  update_string(display_line[GO_THREE], GO_THREE);
  update_display = GO_ONE;
  running = GO_ZERO;
  wheel_on_count = GO_ZERO;
  wheel_direction = GO_ONE;
  number_of_runs = GO_FIVE;
//  move_state = STOP;
  movement_state = 0;
  go_around = 0;
  safe_state = CLEAR;
  
  
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    if(clk_int_count >= NUM_TIMER_CYCLES){
      ++movement_state;
      
      clk_int_count = 0;
    }
    
    safe_state = CheckMagicSmoke();
    
    if(safe_state == CLEAR){
      if(movement_state > GO_TRECE){
        strcpy(display_line[GO_ONE], "   STOP   ");
        update_string(display_line[GO_ONE], GO_ONE);
        display_changed = GO_ONE;
        Display_Process();
        
        CompleteStop();
      }
          
      if((movement_state == GO_ONCE) || (movement_state == GO_DOCE) || (movement_state == GO_TRECE)){
        strcpy(display_line[GO_ONE], "BACK LEFT ");
        update_string(display_line[GO_ONE], GO_ONE);
        display_changed = GO_ONE;
        Display_Process();
        
        BackoutLeft();
      }
          
      if(movement_state == GO_TEN){
        CompleteStop();
      }
      
      if((movement_state == GO_SEVEN) || (movement_state == GO_EIGHT) || (movement_state == GO_NINE)){
        strcpy(display_line[GO_ONE], "TURN LEFT ");
        update_string(display_line[GO_ONE], GO_ONE);
        display_changed = GO_ONE;
        Display_Process();
        
        TurnLeft();
      }
      
      if(movement_state == GO_SIX){
        CompleteStop();
      }
      
      if(movement_state == GO_FIVE){
        strcpy(display_line[GO_ONE], " FORWARD  ");
        update_string(display_line[GO_ONE], GO_ONE);
        display_changed = GO_ONE;
        Display_Process();
        
        Forward();
      }
          
      if(movement_state == GO_FOUR){
        CompleteStop();
      }
      
      if((movement_state == GO_TWO) || (movement_state == GO_THREE)){
        strcpy(display_line[GO_ONE], " REVERSE  ");
        update_string(display_line[GO_ONE], GO_ONE);
        display_changed = GO_ONE;
        Display_Process();
        
        Reverse();
      }
      
      if(movement_state == GO_ONE){
        CompleteStop();
      }
      
      if(movement_state == GO_ZERO){
        strcpy(display_line[GO_ONE], " FORWARD  ");
        update_string(display_line[GO_ONE], GO_ONE);
        display_changed = GO_ONE;
        Display_Process();
        
        Forward();
      }
    }
    else{
      CompleteStop();
    }
  }
  //------------------------------------------------------------------------------
}




