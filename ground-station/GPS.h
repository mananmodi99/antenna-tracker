#ifndef GPS_H
#define GPS_H

#include <Arduino.h>

class SoftwareSerial;

class GPS {
public:
  GPS();
  void read();

private:
  SoftwareSerial *serialPort;
  byte step;
  uint8_t ubxClass;
};

#endif



