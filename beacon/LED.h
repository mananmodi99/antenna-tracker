#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED {
public:
  LED(int p);
  void tick();

private:
  int pin;
  boolean high;
  unsigned long changeTime;
};

#endif



