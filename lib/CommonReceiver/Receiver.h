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
  int lastSeenSatellites();
  String lastMessage();
  long lastMessageNumber();
  bool haveFix();

private:
  BufferedSerial *lora;
  double lastLatitude;
  double lastLongitude;
  int lastAltitude;
  int _lastSeenSatellites;
  String _lastMessage;
  long _lastMessageNumber;
  bool _haveFix;
};

#endif



