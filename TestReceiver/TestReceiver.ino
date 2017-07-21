#include <SoftwareSerial.h>
#include "BufferedSerial.h"

SoftwareSerial *serialPort = new SoftwareSerial(11, 12);
//BufferedSerial *lora = new BufferedSerial(Serial1);

int incomingByte = 0;

void setup() {
  Serial.begin(9600);
  serialPort->begin(9600);
  //Serial1.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  
  while (serialPort->available()) {
    Serial.println("Wii");
    Serial.write(serialPort->read());
    //gpsPlus.encode(serialPort->read());
  }
  
  /*char* message = lora->getMessage();
  if (message != NULL) {
    Serial.println(message);
  }*/
}
