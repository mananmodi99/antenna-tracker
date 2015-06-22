#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>

class BufferedSerial;

class Receiver {
public:
  Receiver();
  void tick();
  double latitude();
  double longitude();

private:
  BufferedSerial *lora;
  double lastLatitude;
  double lastLongitude;
  int lastAltitude;
  int lastSeenSatellites;
};

#endif



