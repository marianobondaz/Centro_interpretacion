
#include <Arduino.h>

#include <FastLED.h>
#include <SimpleTimer.h>


#define LED_PIN             D3
#define SENSOR_PIN          D4


#define COLOR_ORDER         GRB
#define CHIPSET             WS2812B
#define NUM_LEDS            280
#define TIME_ACT            60000             //tiempo que permanecera activos los led antes de apagarse
#define TIME_READ           2000              //tiempo de lectura del sensor

#define BRIGHTNESS          200
#define FRAMES_PER_SECOND   60 //orig 60

bool gReverseDirection      = false;
bool stateLeds              = true;
//bool stateTimer             = false;

CRGB leds[NUM_LEDS];

void onTimeLeds();
void readSensor();

SimpleTimer timer1;
SimpleTimer timer2;

#define COOLING             55
#define SPARKING            80


#include <Function.cpp>

void setup() {
  delay(3000); // sanity delay  

  Serial.begin(9600);

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );

  pinMode(SENSOR_PIN, INPUT);
  
  timer1.setInterval(TIME_ACT,onTimeLeds);
  timer2.setInterval(TIME_READ,readSensor);
}

void loop()
{
  timer1.run();
  timer2.run(); 

  if (stateLeds)
  {
    Fire2012();             // run simulation frame
  } 
  else
  {
    black();
  }   
  
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
        
}