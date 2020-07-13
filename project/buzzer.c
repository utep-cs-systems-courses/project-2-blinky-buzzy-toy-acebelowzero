#include <msp430.h>
#include "led.h"
#include "buzzer.h"
#include "timer.h"

static int song[] = {E7, 0, 0, 0, A7, 0, 0, C6, 0, 0, 0, A7, 0, 0, 0, FS7, 0, D8, 0, 0, D8, 0, 0, D8, 0, 0, 0, 0, E7, 0, 0, 0, A7, 0, 0, C6, 0, 0, 0, A7, 0, 0, 0, FS7, 0, E7, 0, 0, 0, DS8, 0, 0, D8,0, 0, 0, 0, GS7, 0, 0, 0, CS7, 0, 0, FS7, 0, 0, 0, CS7, 0, 0, GS7, 0, 0, CS7, 0, 0, G7, 0, 0, FS7,00,0}; //wii theme song kinda

static int song_pace [] = {15, 10, 10, 15, 15, 10, 12, 13, 10, 10, 20, 15, 10, 10, 10, 15, 10, 7, 50, 50, 7, 50, 50, 7, 5, 5, 5, 10, 15, 10, 10, 10, 15, 10, 10, 15, 10, 10, 10, 15, 10, 10, 10, 15, 10, 4, 10, 10, 10, 6, 65, 65, 6, 5, 5, 5, 4, 15, 10, 10, 20, 13, 10, 10, 15, 10, 10, 20, 15, 5, 10, 15, 6, 6, 15, 7, 7, 7, 40, 40, 10, 40, 40, 40};

static unsigned short duration = 400; //250 ms
static unsigned short current_note = 0;
static unsigned short total_duration = 0; //total duration

char buzzer_state = 0;

void buzzer_init(){ //initialize speaker and buzzer method
  timerAUpmode(); // used to drive speaker

  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR |= BIT6; //enable output to speaker (P2.6)

  total_duration = (int)(duration / song_pace[0]);
  buzzer_state = BUZZER_OFF;
  current_note = 0;
}//end buzzer_init

void buzzer_set_period(short cycles){
  CCR0 = cycles;
  CCR1 = cycles >> 1; //one half cycle
}//end buzzer_set_period

void buzzer_play(){
  buzzer_state = BUZZER_ON; //buzzer is playing set the state

  int note = song[current_note]; //set current note to song

  if (note < 0){
    buzzer_state = BUZZER_OFF;
    current_note = 0;
    return;
  }//end note < 0

  if (note == 0){
    led_state(1,0); //RED LED on when song off
  }//end note == 0

  else{
    led_state(0,0); //GREEN LED on when song on
  }//end else
  
  buzzer_set_period(note); //play curr note

  total_duration--; //decrement duration

  if(total_duration <= 1){//check if end of note
    current_note++; //next note
    total_duration = (int)(duration / song_pace[current_note]); //update song timing
  }//end total_duration <= 1

  
}// end buzzer_play





