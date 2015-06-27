#include "GPS.h"

#include <SoftwareSerial.h>

#define MIN_NUMBER_OF_SATELLITES 7

GPS::GPS(int rxPin, int txPin) {
  serialPort = new SoftwareSerial(rxPin, txPin);
  serialPort->begin(9600);
  connected = false;
}

void GPS::tick() {
  serialPort->listen();
  while (serialPort->available()) {
    connected = true;
    gpsPlus.encode(serialPort->read());
  }
}

boolean GPS::isConnected() {
  return connected;
}

boolean GPS::haveFix() {
  return gpsPlus.location.isValid() && gpsPlus.satellites.value() >= MIN_NUMBER_OF_SATELLITES;
}

byte GPS::numberOfSatellites() {
  return gpsPlus.satellites.value();
}

double GPS::latitude() {
  return gpsPlus.location.lat();
}

double GPS::longitude() {
  return gpsPlus.location.lng();
}

long GPS::altitude() {
  return gpsPlus.altitude.value();
}

