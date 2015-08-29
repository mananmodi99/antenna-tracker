#include "Configuration.h"
#include "Receiver.h"
#include "BufferedSerial.h"
#include "Display.h"

#include <Metro.h>
#include <SoftwareSerial.h>

Receiver *receiver;
Display *display;
Metro receiverLoop = Metro(200); // 5hz loop

void setup() {
  Serial.begin(9600);
  
  SoftwareSerial *softwareSerial = new SoftwareSerial(LORA_RX, LORA_TX);
  softwareSerial->begin(9600);
  receiver = new Receiver(new BufferedSerial(softwareSerial));
  
  display = new Display();
}

void loop() {
  if (receiverLoop.check()) {
    receiver->tick();
    if (receiver->lastMessageNumber() > 0) {
      DEBUG_PRINTLN(receiver->lastMessage());
      display->status(receiver);
    }
  }
}
