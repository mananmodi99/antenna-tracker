#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

enum Mode {
  WAITING_GPS,
  STATUS
};

class Display {
public:
  Display();
  void showWaitingForGPS(byte satellites);
  void showStatus(byte satellites);

private:
  Mode mode;
  byte numberOfSatellites;
};

#endif



