#include "Transmitter.h"
#include "BufferedSerial.h"

#include <SoftwareSerial.h>

Transmitter::Transmitter(int rxPin, int txPin) {
  SoftwareSerial *softwareSerial = new SoftwareSerial(rxPin, txPin);
  softwareSerial->begin(9600);
  serialPort = new BufferedSerial(softwareSerial);
  messageNumber = 1;
}

void Transmitter::sendMessage(char *message) {
  String stringMessage = String(message);
  this->sendMessage(stringMessage);
}

void Transmitter::sendMessage(String &message) {
  serialPort->sendMessage(message + "|" + messageNumber);
  messageNumber++;
}

