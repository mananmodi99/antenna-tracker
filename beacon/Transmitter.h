#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <Arduino.h>

class BufferedSerial;

class Transmitter {
public:
  Transmitter();
  void sendMessage(char *message);
  void sendMessage(String &message);

private:
  BufferedSerial *serialPort;
};

#endif



