
#include "config.h"

#define MAX_BUTTONS 16

#define TICKRATE 1000 //in microseconds

#define DELAY 50

#define DEBOUNCE_MILLISECONDS 50
#define DEBOUNCE_CYCLES (TICKRATE / 1000) * DEBOUNCE_MILLISECONDS //how many ticks

#define COOLDOWN_MILLISECONDS 500
#define COOLDOWN_CYCLES (TICKRATE / 1000) * COOLDOWN_MILLISECONDS

IntervalTimer tick;
uint16_t buttonStates[MAX_BUTTONS];
uint32_t button_cycles [MAX_BUTTONS];

/*
#define KEY_UP_ARROW 0xDA
#define KEY_DOWN_ARROW 0xD9
#define KEY_LEFT_ARROW 0xD8
#define KEY_RIGHT_ARROW 0xD7
*/

typedef struct {
  String keypattern;
  int32_t cycles = 0;
  volatile bool is_down = false;
  uint8_t buttonPin;
} button;

uint16_t keymap [4] = {KEY_UP_ARROW,KEY_DOWN_ARROW,KEY_LEFT_ARROW,KEY_RIGHT_ARROW};


button button_set[MAX_BUTTONS];

void setup()
{

   Serial.begin(9600);

   configureKeys();

   button_set[0].buttonPin = 0;
   button_set[1].buttonPin = 1;
   button_set[2].buttonPin = 2;
   button_set[3].buttonPin = 3;
   button_set[4].buttonPin = 4;
   button_set[5].buttonPin = 5;
   button_set[6].buttonPin = 6;
   button_set[7].buttonPin = 7;
   button_set[8].buttonPin = 8;
   button_set[9].buttonPin = 9;
   button_set[10].buttonPin = 10;
   button_set[11].buttonPin = 11;
   button_set[12].buttonPin = 12;
   button_set[13].buttonPin = 14;
   button_set[14].buttonPin = 15;
   button_set[15].buttonPin = 16;

  tick.begin(tick_callback, TICKRATE); //read every 1 millisecond
  Keyboard.begin ();
  
  for(int i = 0; i < MAX_BUTTONS; i++)
  {
    pinMode(button_set[i].buttonPin, INPUT_PULLUP);
  }
}

void loop ()
{
  for (uint8_t i = 0; i < MAX_BUTTONS; i++)
  {
    button * b = &button_set[i];
    
    if(b->is_down)
    {      
      Keyboard.press(KEY_LEFT_CTRL);
      delay(DELAY*10);
      for(uint8_t i = 0; i < b->keypattern.length(); i++)
      {
        Keyboard.press(b->keypattern[i]);
        delay(DELAY);
        Keyboard.release(b->keypattern[i]);
        delay(DELAY);
      }
      delay(DELAY);
      Keyboard.releaseAll();
      b->is_down = false;
    } 
  }
}

void tick_callback ()
{
  for(uint8_t i = 0; i < MAX_BUTTONS; i++)
  {
    button* b = &button_set[i];
    
    //invert because pullup logic. Button is high when not pressed and low when pressed
    int pressed = !digitalRead(b->buttonPin);
    
    if(pressed) 
    { 
      if(b->cycles++ >= DEBOUNCE_CYCLES && !b->is_down )
      {
        b->is_down = true;
        b->cycles = -COOLDOWN_CYCLES;
      }
    }
    else
    {
      b->cycles = 0;
    }  
  }
}

void configureKeys()
{
   button_set[0].keypattern = KEY0;
   button_set[1].keypattern = KEY1;
   button_set[2].keypattern = KEY2;
   button_set[3].keypattern = KEY3;
   button_set[4].keypattern = KEY4;
   button_set[5].keypattern = KEY5;
   button_set[6].keypattern = KEY6;
   button_set[7].keypattern = KEY7;
   button_set[8].keypattern = KEY8;
   button_set[9].keypattern = KEY9;
   button_set[10].keypattern = KEY10;
   button_set[11].keypattern = KEY11;
   button_set[12].keypattern = KEY12;
   button_set[13].keypattern = KEY13;
   button_set[14].keypattern = KEY14;
   button_set[15].keypattern = KEY15;
}
