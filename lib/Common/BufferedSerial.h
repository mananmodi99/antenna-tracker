#ifndef BUFFERED_SERIAL_H
#define BUFFERED_SERIAL_H

#include <Arduino.h>

class SoftwareSerial;
class HardwareSerial;

class BufferedSerial {
public:
  BufferedSerial(SoftwareSerial *serial);
  BufferedSerial(HardwareSerial *serial);
  char* getMessage();
  void sendMessage(const char *message);
  void sendMessage(String &message);

private:
  char checksum(const char *message);
  void readSoftwareSerial();
  void readHardwareSerial();

  SoftwareSerial *softwareSerial;
  HardwareSerial *hardwareSerial;
  char data[30];
  byte index;
};

#endif


