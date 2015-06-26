#include "LED.h"

#define WAITING_INTERVAL 50
#define WAITING_HIGH_TIME 50
#define WAITING_LOW_TIME 1000

LED::LED(int p) {
  pin = p;
  pinMode(pin, OUTPUT);
  high = false;
  running = false;
  changeTime = millis();
}

void LED::tick() {
  if (running) {
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
  }
  else {
    if (millis() - changeTime >= WAITING_INTERVAL) {
      high = !high;
      digitalWrite(pin, high);
      changeTime = millis();
    }
  }
}

void LED::statusWaiting() {
  running = false;
}

void LED::statusRunning() {
  running = true;
}
