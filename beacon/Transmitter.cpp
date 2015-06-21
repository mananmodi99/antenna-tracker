#include "Transmitter.h"
#include "BufferedSerial.h"
#include "Configuration.h"

#include <SoftwareSerial.h>

Transmitter::Transmitter() {
  SoftwareSerial *softwareSerial = new SoftwareSerial(LORA_RX, LORA_TX);
  softwareSerial->begin(9600);
  serialPort = new BufferedSerial(softwareSerial);
}

void Transmitter::sendMessage(char *message) {
  serialPort->sendMessage(message);
}

void Transmitter::sendMessage(String &message) {
  serialPort->sendMessage(message);
}

