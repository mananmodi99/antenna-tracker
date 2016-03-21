#include "LED.h"
#include "State.h"

#define WAITING_INTERVAL 50
#define WAITING_HIGH_TIME 50
#define WAITING_LOW_TIME 1000

LED::LED(byte p) {
  pin = p;
  pinMode(pin, OUTPUT);
  high = false;
  changeTime = millis();
}

void LED::tick() {
  
  switch (state) {
    case NO_GPS:
      digitalWrite(pin, HIGH);
      break;
     
     case INIT_GPS:
       if (millis() - changeTime >= WAITING_INTERVAL) {
         high = !high;
         digitalWrite(pin, high);
         changeTime = millis();
       }
       break;
     
     case RUNNING:
       if (high) {
         if (millis() - changeTime >= WAITING_HIGH_TIME) {
           high = false;
           digitalWrite(pin, LOW);
           changeTime = millis();
         }
       }
       else {
         if (millis() - changeTime >= WAITING_LOW_TIME) {
           high = true;
           digitalWrite(pin, HIGH);
           changeTime = millis();
         }
       }
  };
}

