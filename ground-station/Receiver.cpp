#include "Receiver.h"
#include "BufferedSerial.h"
#include "Configuration.h"

#include <SoftwareSerial.h>

Receiver::Receiver() {
  SoftwareSerial *serialPort = new SoftwareSerial(LORA_RX, LORA_TX);
  lora = new BufferedSerial(serialPort);
  serialPort->begin(9600);
}

void Receiver::tick() {
  char* message = lora->getMessage();
  if (message != NULL) {
    Serial.println(message);
  }
}

double Receiver::latitude() {
  //return 59.437222;
  return 58.383333;
}

double Receiver::longitude() {
  //return 24.745278;
  return 26.716667;
}
