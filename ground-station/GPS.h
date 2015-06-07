#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>

class SoftwareSerial;

class GPS {
public:
  GPS();
  void tick();
  boolean haveFix();
  byte numberOfSatellites();
  double distanceTo(double latitude, double longitude);

private:
  SoftwareSerial *serialPort;
  TinyGPSPlus gpsPlus;
};

#endif



