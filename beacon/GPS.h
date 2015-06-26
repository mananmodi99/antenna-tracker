#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>

class SoftwareSerial;

class GPS {
public:
  GPS(int rxPin, int txPin);
  void tick();
  boolean haveFix();
  byte numberOfSatellites();
  double latitude();
  double longitude();
  long altitude();

private:
  SoftwareSerial *serialPort;
  TinyGPSPlus gpsPlus;
};

#endif



