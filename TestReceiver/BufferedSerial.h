#ifndef BUFFERED_SERIAL_H
#define BUFFERED_SERIAL_H

#include <Arduino.h>

class SoftwareSerial;

class BufferedSerial {
public:
  BufferedSerial(SoftwareSerial *serial);
  char* getMessage();
  void sendMessage(char *message);
  void sendMessage(String &message);

private:
  SoftwareSerial *serial;
  char data[30];
  byte index;
};

#endif


