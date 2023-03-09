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
unsigned int baud_state;
char Tx_array_one[GO_NINE];    // NCSU  #1
char RingBuffer[RING_BUFFER_SIZE];
char ProcBuffer[PROC_BUFFER_SIZE];
char Tx_char;
char Rx_char;
unsigned int rx_wr;
unsigned int temp;
unsigned int tx_i;
unsigned int rx_i;
char Rx_string[STRING_SIZE];
char Tx_string[STRING_SIZE];
unsigned int tx_state;
unsigned int com_state;


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
void Init_Serial_UCA0(void);
void LCD_Config(void);

unsigned int check_flag;

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
  Init_Serial_UCA0();
  
  
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
  while(DAC_wait <= HUNDRED){       // give DAC 5 seconds to be ready
  }
  
  P2OUT   |=  DAC_ENB;
  
  P6OUT |= LCD_BACKLIGHT; // Set output as high
  P2OUT &= ~IR_LED; // Initial Value = Low / Off
  
  //------------------------------------------------------------------------------
  // Variable setup
  //------------------------------------------------------------------------------
  strcpy(display_line[GO_ZERO], "~~~~~~~~~~");
  update_string(display_line[GO_ZERO], GO_ZERO);
  strcpy(display_line[GO_ONE], "~~~~~~~~~~");
  update_string(display_line[GO_ONE], GO_ONE);
  strcpy(display_line[GO_TWO], "~~~~~~~~~~");
  update_string(display_line[GO_TWO], GO_TWO);
  strcpy(display_line[GO_THREE], "~~~~~~~~~~");
  update_string(display_line[GO_THREE], GO_THREE);
  
  display_changed = GO_ONE;
  Display_Update(GO_ZERO ,GO_ZERO ,GO_ZERO ,GO_ZERO);
  display_changed = GO_ZERO;
  
  strcpy(Tx_array_one, "NCSU  #1~");
  strcpy(Rx_string, "    rx    ");
  strcpy(Tx_string, "    tx    ");
  Tx_char = 'c';
  Rx_char = NULL;
  
  ADC_Channel = CH_W;
  safe_state = CLEAR;
  LCD_state = ON;
  debounce_state_one = STILL;
  debounce_state_two = STILL;
  sw1_state = GO_ZERO;
  LCD_update_count = GO_ZERO;
  IR_state = OFF;
  car_state = WAIT;
  found_line = NO;
  pause = NO;
  base_speed = BASE_SPEED;
  //last_off = FULL_ON;
  l_fence = OVER;
  r_fence = OVER;
  baud_state = LOWER_RATE;
  tx_i = GO_ZERO;
  rx_i = GO_ZERO;
  tx_state = SENDING;
  com_state = WAITING;
  
  debounce_count_one = GO_ZERO;
  debounce_count_two = GO_ZERO;
  DAC_wait = GO_ZERO;
  clk_one = GO_ZERO;
  clk_two = GO_ZERO;
  
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    //          Non-movement
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Tx and Rx stuff
    if(clk_one >= (ONE_SEC * GO_TWO)){
      if(com_state == TRANSMIT){
        if(tx_state == SENDING){
          UCA0IE |= UCTXIE; // Enable TX interrupt
          //strcpy(Tx_string, Rx_string);
          //UCA0TXBUF = NULL; // Prime the Pump
        }
        else{
          UCA0IE &= ~UCTXIE;
        }
      }
      else{
        UCA0IE &= ~UCTXIE;
      }
    }
    
    // LCD stuff
    if(LCD_update_count >= GO_FOUR){
      LCD_Config();
    }
    
    // Debounce switch
    /*
    if(!debounce_state_one){
      Debounce();
    }
    
    if(!debounce_state_two){
      Debounce();
    }
    */
    
    HEXtoBCD(ADC_Right_Detect); // Convert result to String
    strcpy(R_det_string, temp_char);
    
    HEXtoBCD(ADC_Left_Detect); // Convert result to String
    strcpy(L_det_string, temp_char);
    
    
    //          Movement
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /*
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
    */
  }
}



//------------------------------------------------------------------------------
// Functions because I am too lazy to make another file
//------------------------------------------------------------------------------
void LCD_Config(void){
  // line 1, COM state
  if(com_state == WAITING){
    strcpy(display_line[GO_ZERO], " Waiting  ");
    update_string(display_line[GO_ZERO], GO_ZERO);
  }
      
  if(com_state == RECEIVE){
    strcpy(display_line[GO_ZERO], " Receive  ");
    update_string(display_line[GO_ZERO], GO_ZERO);
  }
      
  if(com_state == TRANSMIT){
    strcpy(display_line[GO_ZERO], " Transmit ");
    update_string(display_line[GO_ZERO], GO_ZERO);
  }
      
      
  // line 2, Tx or Rx string
  if(com_state == WAITING){
    strcpy(display_line[GO_ONE], "~~~~~~~~~~");
    update_string(display_line[GO_ONE], GO_ONE);
  }
      
  if(com_state == RECEIVE){
    strcpy(display_line[GO_ONE], Rx_string);
    update_string(display_line[GO_ONE], GO_ONE);
  }
      
  if(com_state == TRANSMIT){
    //strcpy(Tx_string, Rx_string);
    strcpy(display_line[GO_ONE], Rx_string);
    update_string(display_line[GO_ONE], GO_ONE);
  }
      
      
  // line 3, Baud label
  strcpy(display_line[GO_TWO], "   Baud   ");
  update_string(display_line[GO_TWO], GO_TWO);
      
      
  // line 4, Baud Rate
  if(baud_state == LOWER_RATE){     // if lower rate, display lower baud
    strcpy(display_line[GO_THREE], " 115,200  ");
    update_string(display_line[GO_THREE], GO_THREE);
  }
  else{     // if higher rate, display higher baud
    strcpy(display_line[GO_THREE], " 460,800  ");
    update_string(display_line[GO_THREE], GO_THREE);
  }
      
      
      // send to display
  display_changed = GO_ONE;
      
  LCD_Update();
      
  LCD_update_count = GO_ZERO;
}


void LCD_Update(void){
  if(display_changed == GO_ONE){
    Display_Update(GO_ZERO,GO_ZERO,GO_ZERO,GO_ZERO);
        
    display_changed = GO_ZERO;
    display_update = GO_ZERO;
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
  if(clk_two >= (GO_TEN * GO_TWO)){
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
            if(clk_one < (THREE_SEC + GO_FIVE)){
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
  if(ADC_Right_Detect < RIGHT_STRAIGHT_VAL){
    right_speed = base_speed;
    left_speed = base_speed;
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= RIGHT_STRAIGHT_VAL){
    right_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_ONE);
    left_speed = base_speed - (HUNDRED * GO_FOUR);
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= (RIGHT_STRAIGHT_VAL - (GO_TEN * GO_ONE))){
    right_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_TWO);
    left_speed = base_speed - (HUNDRED * GO_FOUR);
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= (RIGHT_STRAIGHT_VAL - (GO_TEN * GO_TWO))){
    right_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_THREE);
    left_speed = base_speed - (HUNDRED * GO_FOUR);
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= (RIGHT_STRAIGHT_VAL - (GO_TEN * GO_THREE))){
    right_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_FOUR);
    left_speed = base_speed - (HUNDRED * GO_FOUR);
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= (RIGHT_STRAIGHT_VAL - (GO_TEN * GO_FOUR))){
    right_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_FIVE);
    left_speed = base_speed - (HUNDRED * GO_FOUR);
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= (RIGHT_STRAIGHT_VAL - (GO_TEN * GO_FIVE))){
    right_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_SIX);
    left_speed = base_speed - (HUNDRED * GO_FOUR);
    
    r_fence = OVER;
  }
  if(ADC_Right_Detect <= HUNDRED){
    FullStop();
    
    last_off = RIGHT;
    r_fence = UNDER;
  }
  
  
  // Left detect configurations
  if(ADC_Left_Detect > LEFT_STRAIGHT_VAL){
    right_speed = base_speed;
    left_speed = base_speed;
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= LEFT_STRAIGHT_VAL){
    right_speed = base_speed - (HUNDRED * GO_FOUR);
    left_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_ONE);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= (LEFT_STRAIGHT_VAL - (GO_TEN * GO_ONE))){
    right_speed = base_speed - (HUNDRED * GO_FOUR);
    left_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_TWO);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= (LEFT_STRAIGHT_VAL - (GO_TEN * GO_TWO))){
    right_speed = base_speed - (HUNDRED * GO_FOUR);
    left_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_THREE);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= (LEFT_STRAIGHT_VAL - (GO_TEN * GO_THREE))){
    right_speed = base_speed - (HUNDRED * GO_FOUR);
    left_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_FOUR);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= (LEFT_STRAIGHT_VAL - (GO_TEN * GO_FOUR))){
    right_speed = base_speed - (HUNDRED * GO_FOUR);
    left_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_FIVE);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= (LEFT_STRAIGHT_VAL - (GO_TEN * GO_FIVE))){
    right_speed = base_speed - (HUNDRED * GO_FOUR);
    left_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_SIX);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= (LEFT_STRAIGHT_VAL - (GO_TEN * GO_SIX))){
    right_speed = base_speed - (HUNDRED * GO_FOUR);
    left_speed = base_speed + ((HUNDRED + (GO_TEN * GO_THREE)) * GO_SEVEN);
    
    l_fence = OVER;
  }
  if(ADC_Left_Detect <= HUNDRED){
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
    right_speed = base_speed - (HUNDRED * GO_FOUR);
    left_speed = base_speed + (HUNDRED * GO_DOCE);
  }
  
  ForwardLine(right_speed, left_speed);
}