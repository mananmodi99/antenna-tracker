#ifndef BUFFERED_SERIAL_H
#define BUFFERED_SERIAL_H

#include <Arduino.h>

class SoftwareSerial;

class BufferedSerial {
public:
  BufferedSerial(SoftwareSerial *serial);
  char* getMessage();
  void sendMessage(const char *message);
  void sendMessage(String &message);

private:
  char checksum(const char *message);

  SoftwareSerial *serial;
  char data[30];
  byte index;
};

#endif


