#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED {
public:
  LED(int p);
  void tick();
  void statusWaiting();
  void statusRunning();

private:
  int pin;
  boolean high;
  boolean running;
  unsigned long changeTime;
};

#endif



