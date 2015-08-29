#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>

class BufferedSerial;

class Receiver {
public:
  Receiver(BufferedSerial*);
  void tick();
  double latitude();
  double longitude();
  String lastMessage();
  long lastMessageNumber();

private:
  BufferedSerial *lora;
  double lastLatitude;
  double lastLongitude;
  int lastAltitude;
  int lastSeenSatellites;
  String _lastMessage;
  long _lastMessageNumber;
};

#endif



