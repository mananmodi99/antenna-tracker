#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED {
public:
  LED(byte p);
  void tick();

private:
  byte pin;
  boolean high;
  unsigned long changeTime;
};

#endif



