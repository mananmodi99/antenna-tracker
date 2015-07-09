#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

class LiquidCrystal;

enum Mode {
  WAITING_GPS,
  STATUS
};

class Display {
public:
  Display();
  void showWaitingForGPS(byte satellites);
  void showStatus(byte satellites, double dist);
  void showLocation(double latitude, double longitude);

private:
  Mode mode;
  byte numberOfSatellites;
  double distance;
  LiquidCrystal *lcd;
};

#endif



