#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>

class HardwareSerial;

class GPS {
public:
  GPS();
  void tick();
  boolean haveFix();
  byte numberOfSatellites();
  double distanceTo(double latitude, double longitude);

private:
  HardwareSerial *serialPort;
  TinyGPSPlus gpsPlus;
};

#endif



