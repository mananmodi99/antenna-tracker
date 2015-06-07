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
  void showStatus(byte satellites, double dist);

private:
  Mode mode;
  byte numberOfSatellites;
  double distance;
};

#endif



