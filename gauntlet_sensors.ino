//www.elegoo.com
//2016.12.08
#include "SR04.h"
#define TRIG_PIN1 3
#define ECHO_PIN1 4
#define TRIG_PIN2 23
#define ECHO_PIN2 22
#define period 100

SR04 left = SR04(ECHO_PIN1,TRIG_PIN1);
SR04 right = SR04(ECHO_PIN2,TRIG_PIN2);
//long a;

int US[2] = {100,100};
int buzzers[2] = {5, 6};
boolean states[2] = {false, false};
unsigned long times[2] = {0,0};


void buzzer_control(int index);

void setup() {
   Serial.begin(9600);
   delay(1000);
}

void loop() {
   //a = left.Distance();
   //Serial.print(a);
   //Serial.println("cm");
   //delay(500);

   US[0] = left.Distance();
   US[1] = right.Distance();
   Serial.print(US[0]);
   Serial.print(", ");
   //Serial.println(US[2]);
   Serial.println(US[1]);
   for (int x = 0; x < 2; x++){
    buzzer_control(x);
   }
   
   delay(50);
}

void buzzer_control(int index) {
  //Serial.println(int(US[index]) < 10);
  if (US[index] < 10){
    analogWrite(buzzers[index], 200);
    states[index] = 1;
  }
  else if (US[index] < 30){
    if (millis() - times[index] > period){
      if (states[index] == 0){
        analogWrite(buzzers[index], 200);
        states[index] = 1;
      }
      else{
        analogWrite(buzzers[index], 0);
        states[index] = 0;
      }
      times[index] = millis();     
    }
  }
  else{
    analogWrite(buzzers[index], 0);
    states[index] = 0;
  }


  
  }
