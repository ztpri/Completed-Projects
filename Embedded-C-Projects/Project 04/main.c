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
#include  <string.h>
#include  "macros.h"
#include  "project4.h"


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
unsigned int Last_Time_Sequence;
unsigned int cycle_time;
unsigned int time_change;
unsigned int shape;             // shape to be made by car
unsigned int wheel_state;       // whether the wheel is on or off
unsigned int cycle_count;       // amount of times the OS loop cycles
unsigned int run_count;         // amount of times the shape was run
unsigned int figure_loop;       // which loop of figure 8 
unsigned int triangle_state;    // which part of triangle: straight or curve
unsigned int line_count;        // how many times a line was completed

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
  Init_Timers();                       // Initialize Timers
  Init_ADC();
  Init_DAC();  
  Init_LCD();                          // Initialize LCD
  Init_Switches();                     // Initialize Switches

  display_mode = ORIGINAL;
  display_adc = GO_ONE;
//  state = ADC_OPERATION;

  // initialize LCD
  strcpy(display_line[0], "~~~~~~~~~~");
  update_string(display_line[0], 0);
  strcpy(display_line[1], "~~~~~~~~~~");
  update_string(display_line[1], 1);
  strcpy(display_line[2], "~~~~~~~~~~");
  update_string(display_line[2], 2);
  strcpy(display_line[3], "~~~~~~~~~~");
  update_string(display_line[3], 3);
  display_changed = 1;
  Display_Process();
  
  // give value to movement variables
  running = 0;
  wheel_on_count = 0;
  wheel_direction = 1;
  number_of_runs = 5;
//  move_state = STOP;
  
  // give value to state variables
  Last_Time_Sequence = 0;
  shape = CIRCLE;
  wheel_state = 0;
  cycle_count = 0;
  cycle_time = 0;
  display_changed = 0;
  run_count = 0;
  figure_loop = loop_one;
  triangle_state = TRIANGLE;
  line_count = 0;
    
  
  while(ALWAYS){
    //------------------------------------------------------------------------------
    //  timing code
    //------------------------------------------------------------------------------
    if(Last_Time_Sequence != Time_Sequence){
      Last_Time_Sequence = Time_Sequence;
      time_change = 1;
      cycle_time++;
    }
      
    
    //------------------------------------------------------------------------------
    //  movement code
    //------------------------------------------------------------------------------
    switch(shape){
      case CIRCLE: // Circle
        strcpy(display_line[1], "CIRCLE  :D");
        update_string(display_line[1], 1);
        display_changed = 1;
        Display_Process();
        
        if(cycle_time < (SINGLE_CIRCLE * 2)){
          P6OUT |= R_FORWARD;
          
          if((cycle_time % PWM_TIME) == 0){
            P6OUT |= L_FORWARD;
          }
          else{
            P6OUT &= ~L_FORWARD;
          }
        }
        else{
          Stop();
          
          if(!(SW2 & P2IN)){
            shape = FIGURE;
            cycle_time = 0;
          }
        }
        
        break; //
        
        
      case FIGURE:  // figure 8
        strcpy(display_line[1], " FIGURE 8 ");
        update_string(display_line[1], 1);
        display_changed = 1;
        Display_Process();
        
        if(run_count < 2){
          if(figure_loop == loop_one){    // first half of figure 8
            if(cycle_time < SINGLE_CIRCLE){
              P6OUT |= R_FORWARD;
          
          
              if((cycle_time % PWM_TIME) == 0){
                P6OUT |= L_FORWARD;
              }
              else{
                P6OUT &= ~L_FORWARD;
              }
            }
            else{
              P6OUT &= ~L_FORWARD;
              P6OUT &= ~R_FORWARD;
              figure_loop = loop_two;
              cycle_time = 0;
            }
          }
          else{           // second half of figure 8
            if(cycle_time <= (SINGLE_CIRCLE)){
              P6OUT |= L_FORWARD;
          
          
              if((cycle_time % (PWM_TIME)) == 0){
                P6OUT |= R_FORWARD;
              }
              else{
                P6OUT &= ~R_FORWARD;
              }
            }
            else{
              P6OUT &= ~L_FORWARD;
              P6OUT &= ~R_FORWARD;
              figure_loop = loop_one;
              cycle_time = 0;
              ++run_count;
            }
          }
        }
        else{
          if(!(SW2 & P2IN)){
              shape = TRIANGLE;
              cycle_time = 0;
              run_count = 0;
          }
        }
        
        break;
        
        
      case TRIANGLE:  // triangle
        if(triangle_state != END){
          strcpy(display_line[1], " TRIANGLE ");
          update_string(display_line[1], 1);
          display_changed = 1;
          Display_Process();
        }
        else{
          strcpy(display_line[1], "   DONE   ");
          update_string(display_line[1], 1);
          display_changed = 1;
          Display_Process();
        }
        
        // configure movement state. remember it starts in straight state
        if((line_count == 1)){
          triangle_state = CURVE;
        }
        
        if(line_count == 2){
          triangle_state = STRAIGHT;
        }
        
        if((line_count == 3)){
          triangle_state = CURVE2;
        }
        
        if((line_count == 4)){
          triangle_state = STRAIGHT;
        }
        
        if((line_count == 5)){
          triangle_state = CURVE;
        }
        
        if((line_count == 6)){
          triangle_state = STRAIGHT2;
        }
        
        if((line_count == 7)){
          triangle_state = END;
        }
        
        
        // movement control
        if(triangle_state == STRAIGHT){
            if(cycle_time < LINE_TIME){
              P6OUT |= L_FORWARD;
              P6OUT |= R_FORWARD;
            }
            else{
              Stop();
              ++line_count;
              cycle_time = 0;
            }
        }
          
        if(triangle_state == CURVE){
            if(cycle_time < SINGLE_CURVE){
              P6OUT |= R_FORWARD;
              
              if((cycle_time % (PWM_TIME + 3)) == 0){
                P6OUT |= L_FORWARD;
              }
              else{
                P6OUT &= ~L_FORWARD;
              }
            }
            else{
              Stop();
              ++line_count;
              cycle_time = 0;
            }
        }
        
        if(triangle_state == CURVE2){
            if(cycle_time < SINGLE_CURVE2){
              P6OUT |= R_FORWARD;
              
              if((cycle_time % (PWM_TIME + 3)) == 0){
                P6OUT |= L_FORWARD;
              }
              else{
                P6OUT &= ~L_FORWARD;
              }
            }
            else{
              Stop();
              ++line_count;
              cycle_time = 0;
            }
        }
        
        if(triangle_state == STRAIGHT2){
            if(cycle_time < LINE_TIME2){
              P6OUT |= R_FORWARD;
              P6OUT |= L_FORWARD;
            }
            else{
              Stop();
              ++line_count;
              cycle_time = 0;
            }
        }
        
        if(triangle_state == END){
          Stop();
          
          if(run_count < 1){
            ++run_count;
            cycle_time = 0;
            triangle_state = STRAIGHT;
            line_count = 0;
          }
        }
        
        break;
                
      default: break;
    }
    
    ++cycle_count;
  }
}
