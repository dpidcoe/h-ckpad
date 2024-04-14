IntervalTimer tick;

#define MAX_BUTTONS 16

#define TICKRATE 1000 //in microseconds

#define DELAY 50

#define DEBOUNCE_MILLISECONDS 50
#define DEBOUNCE_CYCLES (TICKRATE / 1000) * DEBOUNCE_MILLISECONDS //how many ticks

#define COOLDOWN_MILLISECONDS 500
#define COOLDOWN_CYCLES = (TICKRATE / 1000) * COOLDOWN_MILLISECONDS

uint16_t buttonStates[MAX_BUTTONS];
uint32_t button_cycles [MAX_BUTTONS];

/*
#define KEY_UP_ARROW 0xDA
#define KEY_DOWN_ARROW 0xD9
#define KEY_LEFT_ARROW 0xD8
#define KEY_RIGHT_ARROW 0xD7
*/

#define REINFORCE "wsdaw"
#define SOS "wsdw"
#define RESUPPLY "sswd"
#define HELLBOMB "swaswdsw"
#define EAGLE_REARM "wwawd"
#define SEAF_ARTILLERY "dwws"

#define JUMP_PACK "swwsw"
#define SUPPLY_PACK "saswws"
#define LAS_GUARD_DOG "swawdd"
#define BALLISTIC_SHIELD "sasswa"
#define SHIELD_PACK "swadad"
#define AR23_GUARD_DOG "swawds"

#define MG43 "saswd"
#define AMR "sadws"
#define STALWART "saswwa"
#define EAT17 "ssawd"
#define RECOILLESS_RIFLE "sadda"
#define FLAMETHROWER "sawsw"
#define AUTOCANNON "saswwd"
#define HMG "sawss"
#define RAILGUN "sdswad"
#define LASER_CANNON "saswa"
#define ARC_THROWER "sdswaa"
#define QUASAR_CANNON "sswad"

#define EXOSUIT "asdwass"

#define HMG_EMPLACEMENT "swadda"
#define SHIELD_RELAY "ssadad"
#define TESLA_TOWER "swdwad"
#define AP_MINEFIELD "sawd"
#define INCENDIARY_MINEFIELD "saas"
#define MG_SENTRY "swddw"
#define GATLING_SENTRY "swda"
#define MORTAR_SENTRY "swdds"
#define AUTOCANNON_SENTRY "swdwaw"
#define ROCKET_SENTRY "swdda"
#define EMS_MORTAR_SENTRY "swdsd"

#define ORBITAL_GATLING_BARRAGE "dsaww"
#define ORBITAL_AIRBURST "ddd"
#define ORBITAL_120MM "ddsads"
#define ORBITAL_380MM "dswwass"
#define ORBITAL_WALKING_BARRAGE "dsdsds"
#define ORBITAL_LASER "dswds"
#define ORBITAL_RAILCANNON "dwssd"
#define ORBITAL_PRECISION_STRIKE "ddw"
#define ORBITAL_GAS "ddsd"
#define ORBITAL_EMS "ddas"
#define ORBITAL_SMOKE "ddsw"

#define STRAFING_RUN "wdd"
#define AIRSTRIKE "wdsd"
#define CLUSTER_BOMB "wdssd"
#define ROCKET_STRIKE "wdwa"
#define NAPALM_STRIKE "wdsw"
#define BOMB "wdsss"
#define SMOKE_STRIKE "wdws"

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
   button_set[1].keypattern = NAPALM_STRIKE;
   button_set[2].keypattern = ROCKET_STRIKE;
   button_set[3].keypattern = BOMB;
   button_set[4].keypattern = CLUSTER_BOMB;
   
   button_set[13].keypattern = SOS;
   button_set[14].keypattern = RESUPPLY;
   button_set[15].keypattern = REINFORCE;

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
        b->cycles = -1000;
      }
    }
    else
    {
      b->cycles = 0;
    }  
  }
}
