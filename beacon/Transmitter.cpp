#include "Transmitter.h"
#include "BufferedSerial.h"

#include <SoftwareSerial.h>

Transmitter::Transmitter(int rxPin, int txPin) {
  SoftwareSerial *softwareSerial = new SoftwareSerial(rxPin, txPin);
  softwareSerial->begin(9600);
  serialPort = new BufferedSerial(softwareSerial);
}

void Transmitter::sendMessage(char *message) {
  serialPort->sendMessage(message);
}

void Transmitter::sendMessage(String &message) {
  serialPort->sendMessage(message);
}

