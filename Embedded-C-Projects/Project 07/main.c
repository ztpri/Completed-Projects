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
extern char move_state;
extern char next_state;
extern char last_state;
extern volatile unsigned char display_changed;
extern volatile unsigned int update_display_count;
char display_adc;
char state;
extern char iot_start;
unsigned int safe_state;
unsigned int clk_one;     // clock 1 interrupt counter
unsigned int LCD_state;
unsigned int debounce_count_one;
unsigned int debounce_count_two;
unsigned int debounce_state_one;
unsigned int debounce_state_two;
unsigned int sw1_state;
unsigned int LCD_update_count;
unsigned int smoke_state = CLEAR;
unsigned int ADC_Thumb;
char adc_char[GO_TEN];
unsigned int ADC_Channel;
unsigned int ADC_Right_Detect;
unsigned int ADC_Left_Detect;
char temp_char[GO_FIVE];
char L_det_string[GO_FIVE];
char R_det_string[GO_FIVE];
char display_detect[GO_TEN];
unsigned int IR_state;
unsigned int go_state = GO_ZERO;
unsigned int found_line = NO;
unsigned int pause = NO;
unsigned int clk_two; // clock 2 interrupt counter
unsigned int car_state;
unsigned int DAC_wait;
unsigned int display_update;
unsigned int right_speed;
unsigned int left_speed;
unsigned int base_speed;
unsigned int last_off;
unsigned int r_fence;
unsigned int l_fence;
unsigned int ADC_Right;
unsigned int ADC_Left;


void Init_Timer_B0(void);
void Init_SW1_Int(void);
void Init_SW2_Int(void);
void Debounce(void);
void Init_ADC(void);
void LCD_Update(void);
void FindLine(void);
void StartingTurn(void);
void Init_REF(void);
void Init_Timer_B3(void);
void Forward(unsigned int perc_speed);
void FullStop(void);
void SpinCW(unsigned int perc_speed);
void SpinCCW(unsigned int perc_speed);
void ForwardLine(unsigned int right, unsigned int left);
void FollowLine(void);
void GetPerp(void);
void GetBack(void);


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
  Init_ADC();
  Init_REF();
  Init_DAC();  
  Init_LCD();                          // Initialize LCD
  
  Init_Timer_B0();                      // initialize interrupt for timers B0
  Init_SW1_Int();                      // initialize sw1 interrupt
  Init_SW2_Int();                      // initialize sw2 interrupt

  display_mode = ORIGINAL;
  display_adc = GO_ONE;
//  state = ADC_OPERATION;
  
  Init_Timer_B3();
  

  
  
  strcpy(display_line[GO_ZERO], "DAC setup ");
  update_string(display_line[GO_ZERO], GO_ZERO);
  strcpy(display_line[GO_ONE], "in prog.  ");
  update_string(display_line[GO_ONE], GO_ONE);
  strcpy(display_line[GO_TWO], "just wait ");
  update_string(display_line[GO_TWO], GO_TWO);
  strcpy(display_line[GO_THREE], "    :D    ");
  update_string(display_line[GO_THREE], GO_THREE);
  
  display_changed = GO_ONE;
  Display_Update(GO_ZERO ,GO_ZERO ,GO_ZERO ,GO_ZERO);
  display_changed = GO_ZERO;
  
  adc_char[i4] = ' ';
  adc_char[i5] = ' ';
  adc_char[i6] = ' ';
  adc_char[i7] = ' ';
  adc_char[i8] = ' ';
  adc_char[i9] = NULL;
  strcpy(display_detect, "~~~~~~~~~~");
  strcpy(R_det_string, "~~~~");
  strcpy(L_det_string, "~~~~");
  //display_detect[i9] = NULL;
  
  
  
  //------------------------------------------------------------------------------
  // DAC configuration before variable setup
  //------------------------------------------------------------------------------
  while(DAC_wait <= 100){       // give DAC 5 seconds to be ready
  }
  
  P2OUT   |=  DAC_ENB;
  
  P6OUT |= LCD_BACKLIGHT; // Set output as high
  P2OUT &= ~IR_LED; // Initial Value = Low / Off
  
  ADC_Channel = CH_W;
  safe_state = CLEAR;
  LCD_state = ON;
  sw1_state = GO_ZERO;
  LCD_update_count = GO_ZERO;
  IR_state = OFF;
  car_state = WAIT;//
  found_line = NO;
  pause = NO;
  base_speed = BASE_SPEED;
  //last_off = FULL_ON;
  l_fence = OVER;
  r_fence = OVER;
  
  debounce_count_one = GO_ZERO;
  debounce_count_two = GO_ZERO;
  DAC_wait = GO_ZERO;
  clk_one = GO_ZERO;
  clk_two = GO_ZERO;
  
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    //P6OUT |= R_FORWARD;
    //RIGHT_FORWARD_SPEED = 10000;
    //LEFT_FORWARD_SPEED = 10000;
    
    //          Non-movement
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(LCD_update_count >= GO_FOUR){
      // line 1, IR LED on/off
      if(IR_state == OFF){
        strcpy(display_line[GO_ZERO], "  IR: OFF ");
        update_string(display_line[GO_ZERO], GO_ZERO);
      }
      else{
        strcpy(display_line[GO_ZERO], "  IR: ON  ");
        update_string(display_line[GO_ZERO], GO_ZERO);
      }
      
      
      // line 2, black line or white space
      if(ADC_Left_Detect >= HUNDRED){       // black line
        strcpy(display_line[GO_ONE], " BLK LINE ");
        update_string(display_line[GO_ONE], GO_ONE);
      }
      else{
        strcpy(display_line[GO_ONE], " WHT SPACE");
        update_string(display_line[GO_ONE], GO_ONE);
      }
      
      
      // line 3, IR sensors
      display_detect[i0] = R_det_string[i0];
      display_detect[i1] = R_det_string[i1];
      display_detect[i2] = R_det_string[i2];
      display_detect[i3] = R_det_string[i3];
      
      display_detect[i4] = '|';
      
      display_detect[i5] = L_det_string[i0];
      display_detect[i6] = L_det_string[i1];
      display_detect[i7] = L_det_string[i2];
      display_detect[i8] = L_det_string[i3];
      
      if(car_state == CAL){
        strcpy(display_line[GO_TWO], "0002|0102 ");
        update_string(display_line[GO_TWO], GO_TWO);
      }
      else{
        strcpy(display_line[GO_TWO], display_detect);
        update_string(display_line[GO_TWO], GO_TWO);
      }
      
      
      
      
      // line 4, wheel
      HEXtoBCD(ADC_Thumb);
      adc_char[i0] = temp_char[i0];
      adc_char[i1] = temp_char[i1];
      adc_char[i2] = temp_char[i2];
      adc_char[i3] = temp_char[i3];
      
      strcpy(display_line[GO_THREE], adc_char);
      update_string(display_line[GO_THREE], GO_THREE);
      
      
      //display
      display_changed = GO_ONE;
      
      LCD_Update();
      
      LCD_update_count = GO_ZERO;
    }
    
    // Debounce switch
    if(!debounce_state_one){
      Debounce();
    }
    
    if(!debounce_state_two){
      Debounce();
    }
    
    HEXtoBCD(ADC_Right_Detect); // Convert result to String
    strcpy(R_det_string, temp_char);
    
    HEXtoBCD(ADC_Left_Detect); // Convert result to String
    strcpy(L_det_string, temp_char);
    
    
    //          Movement
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(car_state == CAL){
      if(ADC_Left_Detect > HUNDRED){
        ADC_Left = ADC_Left_Detect;
      }
      else{
        ADC_Right = ADC_Right_Detect;
      }
    }
    
    if(car_state == INTER){
      FindLine();
    }

    if(car_state == TURN){
      StartingTurn();
    }
    
    //if(car_state == PERP){
      //GetPerp();
    //}
    
    if(car_state == CIRC){
      if(clk_one < 5){
        if(r_fence && l_fence){
          FollowLine();
        }
        else{
          clk_one = GO_ZERO;
          
          //GetBack();
        }
      }
    }
  }
  //------------------------------------------------------------------------------
}



//------------------------------------------------------------------------------
// Functions because I am too lazy to make another file
//------------------------------------------------------------------------------
void LCD_Update(void){
  if(display_changed == GO_ONE){
    Display_Update(GO_ZERO,GO_ZERO,GO_ZERO,GO_ZERO);
        
    display_changed = GO_ZERO;
    display_update = 0;
  }
}


void HEXtoBCD(int hex_value){
  int value = GO_ZERO;
  
  temp_char[i0] = '0';
  temp_char[i1] = '0';
  temp_char[i2] = '0';
  temp_char[i3] = '0';
  temp_char[i4] = NULL;
  
  while (hex_value > (THOUSAND - GO_ONE)){
    hex_value = hex_value - THOUSAND;
    value = value + GO_ONE;
    temp_char[i0] = HEX_CV + value;
  }
  
  value = GO_ZERO;
  
  while (hex_value > (HUNDRED - GO_ONE)){
    hex_value = hex_value - HUNDRED;
    value = value + GO_ONE;
    temp_char[i1] = HEX_CV + value;
  }
  
  value = GO_ZERO;
  
  while (hex_value > GO_NINE){
    hex_value = hex_value - GO_TEN;
    value = value + GO_ONE;
    temp_char[i2] = HEX_CV + value;
  }
  
  temp_char[i3] = HEX_CV + hex_value;
}


void FindLine(void){
  if(clk_two >= GO_TEN + GO_TEN){
    if(IR_state == ON){
      if((ADC_Left_Detect < HUNDRED)){
        Forward(INTERCEPT_SPEED);
      }
      
      if((ADC_Left_Detect > HUNDRED)){
        if(!found_line){
          FullStop();
        
          found_line = YES;
          clk_one = GO_ZERO;
          IR_state = OFF;
          P2OUT &= ~IR_LED;
          pause = YES;
        }
      }
    }
    else{
      if(found_line){
        if(pause){
          if(clk_one < THREE_SEC){     // 3 seconds
            FullStop();
          }
          else{
            if(clk_one < (THREE_SEC + GO_SEVEN)){
              SpinCW(SPIN_SPEED);
            }
            else{
              FullStop();
              
              car_state = CIRC;
              
              P2OUT |= IR_LED;
              IR_state = ON;
              clk_one = GO_ZERO;
            }
          }
        }
      }
    }
  }
}


void StartingTurn(void){
  if(clk_one > THREE_SEC){
    if(clk_one < (THREE_SEC + GO_SIX)){
      //RIGHT_REVERSE_SPEED = FULL;
      //LEFT_FORWARD_SPEED = FULL;
    }
    else{
      //RIGHT_REVERSE_SPEED = OFF;
      //LEFT_FORWARD_SPEED = OFF;
      
      car_state = CIRC;
    }
  }
}


void FollowLine(void){
  // Right detect configurations
  if(ADC_Right_Detect < 160){
    right_speed = base_speed;
    left_speed = base_speed;
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= 160){
    right_speed = base_speed + ((HUNDRED + 50) * 1);
    left_speed = base_speed - 400;
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= 150){
    right_speed = base_speed + ((HUNDRED + 50) * 2);
    left_speed = base_speed - 400;
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= 140){
    right_speed = base_speed + ((HUNDRED + 50) * 3);
    left_speed = base_speed - 400;
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= 130){
    right_speed = base_speed + ((HUNDRED + 50) * 4);
    left_speed = base_speed - 400;
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= 120){
    right_speed = base_speed + ((HUNDRED + 50) * 5);
    left_speed = base_speed - 400;
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= 110){
    right_speed = base_speed + ((HUNDRED + 50) * 6);
    left_speed = base_speed - 400;
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= 100){
    FullStop();
    
    last_off = RIGHT;
    r_fence = UNDER;
  }
  
  
  // Left detect configurations
  if(ADC_Left_Detect > 170){
    right_speed = base_speed;
    left_speed = base_speed;
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= 170){
    right_speed = base_speed - 400;
    left_speed = base_speed + ((HUNDRED + 30) * 1);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= 160){
    right_speed = base_speed - 400;
    left_speed = base_speed + ((HUNDRED + 30) * 2);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= 150){
    right_speed = base_speed - 400;
    left_speed = base_speed + ((HUNDRED + 30) * 3);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= 140){
    right_speed = base_speed - 400;
    left_speed = base_speed + ((HUNDRED + 30) * 4);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= 130){
    right_speed = base_speed - 400;
    left_speed = base_speed + ((HUNDRED + 30) * 5);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= 120){
    right_speed = base_speed - 400;
    left_speed = base_speed + ((HUNDRED + 10) * 6);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= 110){
    right_speed = base_speed - 400;
    left_speed = base_speed + ((HUNDRED + 30) * 7);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= 100){
    FullStop();
    
    last_off = LEFT;
    l_fence = UNDER;
  }
  
  
  // set speeds into registers
  ForwardLine(right_speed, left_speed);
}

void GetPerp(void){
}

void GetBack(void){
  if(last_off == RIGHT){        // right last off so car on left of line
    right_speed = base_speed - 400;
    left_speed = base_speed + 1200;
  }
  
  ForwardLine(right_speed, left_speed);
}