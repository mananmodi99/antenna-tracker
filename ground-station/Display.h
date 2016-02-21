#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

class LiquidCrystal;
class GPS;
class Receiver;

enum Mode {
  WAITING_GPS,
  STATUS
};

class Display {
public:
  Display();
  void showWaitingForGPS(byte satellites);
  void showTelemetry(Receiver *);
  void showStatus(byte satellites, double dist);
  void showLocation(double latitude, double longitude);
  void showLocalFix(GPS *gps);

private:
  Mode mode;
  byte numberOfSatellites;
  double distance;
  LiquidCrystal *lcd;
  
  boolean telemetryFix;
  byte telemetrySattelites;
};

#endif



