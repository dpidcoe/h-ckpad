IntervalTimer tick;

#define MAX_BUTTONS 16

#define TICKRATE 1000 //in microseconds

#define DEBOUNCE_MILLISECONDS 50
#define DEBOUNCE_CYCLES (TICKRATE / 1000) * DEBOUNCE_MILLISECONDS //how many ticks

#define COOLDOWN_MILLISECONDS 500
#define COOLDOWN_CYCLES = (TICKRATE / 1000) * COOLDOWN_MILLISECONDS

uint16_t buttonStates[MAX_BUTTONS];
uint32_t button_cycles [MAX_BUTTONS];

#define AIRSTRIKE "AIRSTRIKE!"
#define CLUSTER "CLUSTER!"
#define ROCKETS "ROCKETS!"
#define NAPALM "NAPALM!"
#define BOMB "BOMB!"

typedef struct {
  String keypattern;
  int32_t cycles = 0;
  volatile bool is_down = false;
  uint8_t buttonPin;
} button;


button button_set[MAX_BUTTONS];

void setup()
{

   button_set[0].keypattern = AIRSTRIKE;
   button_set[1].keypattern = NAPALM;
   button_set[2].keypattern = ROCKETS;
   button_set[3].keypattern = BOMB;
   button_set[4].keypattern = CLUSTER;

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
      Serial.println("button!");
      for(uint8_t i = 0; i < b->keypattern.length(); i++)
      {
        Keyboard.write(b->keypattern[i]);
        delay(20);
      }
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
        b->cycles = -1000;
      }
    }
    else
    {
      b->cycles = 0;
    }  
  }
}
