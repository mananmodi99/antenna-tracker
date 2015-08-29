#include "Display.h"
#include "Configuration.h"
#include "Receiver.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Display::Display() {
  lcd = new Adafruit_PCD8544(10, 9, 8, 11, 12);
  
  lcd->setRotation(2);
  lcd->begin();
  lcd->clearDisplay();
  lcd->setCursor(8, 5);
  lcd->println("Waiting for");
  lcd->setCursor(16, 22);
  lcd->println("receiver");
  
  lcd->setCursor(10, 40);
  lcd->println(__DATE__);
  
  lcd->display();
}

void Display::status(Receiver *receiver) {
  if (receiver->haveFix()) {
    showCoordinates(receiver);
  }
  else {
    showWaitingForFix(receiver);
  }
}

void Display::showWaitingForFix(Receiver *receiver) {
  lcd->clearDisplay();
  lcd->setCursor(8, 0);
  lcd->println("Waiting for");
  lcd->setCursor(16, 11);
  lcd->println("GPS fix");
  lcd->setCursor(0, 21);
  lcd->println("Satellites: " + String(receiver->lastSeenSatellites()));
  lcd->setCursor(0, 40);
  lcd->println("Message: " + String(receiver->lastMessageNumber()));
  lcd->display();
}

void Display::showCoordinates(Receiver *receiver) {
  lcd->clearDisplay();
  lcd->println("Lat " + String(receiver->latitude(), 6));
  lcd->setCursor(0, 10);
  lcd->println("Lng " + String(receiver->longitude(), 6));
  lcd->setCursor(0, 20);
  lcd->println("Satellites: " + String(receiver->lastSeenSatellites()));
  lcd->setCursor(0, 30);
  lcd->println("Message: " + String(receiver->lastMessageNumber()));
  lcd->display();
}
