#include <Arduino.h>
#include <SimpleTimer.h>

#define SENSOR_PIN    D4
#define MOSFET_A_PIN  D3
#define MOSFET_B_PIN  D3
#define BUZZER_PIN    D1
#define LM35_PIN      A0
//hola 
#define TIME_READ     2000
#define TIME_ACT      10000

bool stateRead        = false;
bool stateMotor       = false;
bool stateTimer       = false;
//bool stateAccel       = false;
//bool stateDesAccel    = false;
int speed             = 0; 
int speedMax          = 250;   //300 a 1khz
int fadeAmount        = 1; 


void motorOff();
void readSensor();

SimpleTimer timer1;
SimpleTimer timer2;

void motor(){
  if (stateRead == true && stateMotor == false)
  {
    stateMotor = true;

    //int i;
    for (  speed = 0; speed < speedMax; speed++)
    {
      analogWrite(MOSFET_A_PIN, speed);
      delay(20);
      Serial.print("Motor i= ");Serial.println(speed);
    }
     Serial.println("Motor activado");
     speed = speed - 80;
     analogWrite(MOSFET_A_PIN, speed);        
           
  }
  else if (stateRead == false && stateMotor == true && stateTimer == true ) //no desacelera
  {
    stateMotor = false;
    stateTimer = false;
    
    for (speed = speedMax; speed >= 0; speed--)
    {
      analogWrite(MOSFET_A_PIN, speed);
      delay(20);
      Serial.print("Motor i= ");Serial.println(speed);
    }
   Serial.println("Motor desactivado");   
   
  } 
  
 
}


void motorOff(){
  
  stateTimer = true;
  
}

void readSensor(){

  int lectura = digitalRead(SENSOR_PIN);
  Serial.print("digitalRead = ");Serial.println(lectura);
  Serial.print("stateMotor = ");Serial.println(stateMotor);Serial.println("************************");
  Serial.print("speed = ");Serial.println(speed);Serial.println("************************");

  //Serial.print("stateaccel = ");Serial.println(stateAccel);
  
  if (lectura)
  {
    stateRead = true;   
    timer1.restartTimer(0);    
   
  }
  else
  {
    stateRead = false;
  }
  
  
}



void setup() {
  
  Serial.begin(9600);

  //pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MOSFET_A_PIN, OUTPUT);
  //pinMode(MOSFET_B_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  //pinMode(LM35_PIN, INPUT);

  timer1.setInterval(TIME_ACT,motorOff);
  timer2.setInterval(TIME_READ,readSensor);
 
  analogWriteFreq(290);  //ideal 20khz


}

void loop() {
  
  timer1.run();
  timer2.run(); 

  motor();
  
}