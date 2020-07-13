#include "timer.h"
#include "state_machine.h"
#include "buzzer.h"
#include "led.h"
#include "buttons.h"

//State transition cases
static enum{START, Blinky_Toy_0,Blinky_Toy_1, BUZZER, LED_0, LED_1, LED_2, LED_ON, LED_OFF, DIM_LED}

current_state = START;

static short delay = 0;

/* This piece of code dims LED light
   The only way to stop it is to  
   interrupt it is by playing the song.
   Bottom switch (s1) Didn't know how
   to fix it :( */
void dim_lights(unsigned int t){
  unsigned int i;
  for(i = t; i > 0; i--)
    __delay_cycles(1);
}//end dim_lights

void dim(){
  unsigned int j;
  while(1){
    for(j = 1; j < 1200; j++){
      led_state(0,1); //GREEN ON
      dim_lights(j);
      led_state(0,0); //LED OFF
      dim_lights(1200-j);
    }

    for(j = 1200; j > 1; j--){
      led_state(0,1); //green on
      dim_lights(j);
      led_state(0,0); //green off
      dim_lights(1200-j);
    }
  }
}//end dim

char buzzer_state; //import from buzzer

void state_update(){
  switch(current_state){
  case START:
    led_state(0,0); //turn off led
    
    buzzer_play(); //start song

    /* If nothing interrupts or skips the song, turn off BOTH leds
       after the song finishes playing! */
    //led_state(0,0); //turn off leds
    
    if(buzzer_state == BUZZER_OFF){ //set buzzer off
      led_state(0,0); //turn leds off
      current_state = Blinky_Toy_0;
    }

    if(top_1 || top_2 || bottom){ //skip song
      led_state(0,0);
      current_state = Blinky_Toy_0;

      timer_set_transition(20); //delay

      buzzer_state = BUZZER_OFF; //reset buzzer
      buzzer_set_period(0);
    }
    break;
    
  case Blinky_Toy_0:
    timer_set_transition(30); //delay
    //led_state(0,0); //Green led on
    current_state = Blinky_Toy_1; //set current state to next state
    break;
    
  case Blinky_Toy_1:
    led_state(1,0);//Red led on
    if(top_1 || top_2)
      current_state = BUZZER;
    else if (top_2)
      current_state = LED_0;
    else
      current_state = Blinky_Toy_0;
    break;

  case BUZZER:
    timer_set_transition(0); //reset timer

    led_state(0,0); //turn off led

    if(bottom){
      current_state = Blinky_Toy_0; //back to first state
      break;
    }

    /*Set buzzer MHZ levels to individual top switches */
    short period = 0;

    if(top_1)
      period = 1000;
    if(top_2)
      period = 3000;
    
    buzzer_set_period(period);
    led_state(period != 0, period == 0);

    break;

  case LED_0:
    led_state(0,0); //Turn off led
    buzzer_set_period(0); //Turn off buzzer

    delay = (short)(rand () % 400) + 50;

    timer_start(); //begin time

    current_state = LED_1; //Point to next state

    timer_set_transition(25); //delay

    break;

  case LED_1:
    timer_set_transition(0); //timer is reset

    if(timer_elapsed() - delay <= 2){ //time passed
      led_state(0,0); //turn on led led_state(1,1)
      buzzer_set_period(1000); //turn on timer

      timer_set_transition(SET_TIME); //set time

      current_state = LED_2; //next state is set
    }

    else if (top_2)
      current_state = LED_OFF;
    break;

  case LED_2:
    led_state(0,0); //led off
    buzzer_set_period(0); //buzzer off

    if (top_2)
      current_state = LED_ON; //next state on
    else
      current_state = LED_OFF; //next state off if switch not pressed
    break;

  case LED_ON:
    led_state(0,1); //GREEN led on

    if(bottom)
      current_state = Blinky_Toy_0; //go back to first state

    else if (top_2)
      current_state = LED_0;
    break;

  case LED_OFF:
    led_state(1,0); //RED led on

    if(bottom)
      current_state = Blinky_Toy_0; //back to first state

    else if (top_2)
      current_state = LED_0;

    break;
  }
}//end state machine and switch cases
