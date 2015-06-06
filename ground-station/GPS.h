#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>

class SoftwareSerial;

class GPS {
public:
  GPS();
  void tick();

private:
  SoftwareSerial *serialPort;
  TinyGPSPlus gpsPlus;
};

#endif



