#include "GPSLocationProvider.h"

#include <SoftwareSerial.h>

#define MIN_NUMBER_OF_SATELLITES 7

GPSLocationProvider::GPSLocationProvider(int rxPin, int txPin) {
  serialPort = new SoftwareSerial(rxPin, txPin);
  serialPort->begin(9600);
  connected = false;
}

void GPSLocationProvider::tick() {
  serialPort->listen();
  while (serialPort->available()) {
    connected = true;
    gpsPlus.encode(serialPort->read());
  }
}

boolean GPSLocationProvider::isConnected() {
  return connected;
}

boolean GPSLocationProvider::haveFix() {
  return gpsPlus.location.isValid() && gpsPlus.satellites.value() >= MIN_NUMBER_OF_SATELLITES;
}

byte GPSLocationProvider::numberOfSatellites() {
  return gpsPlus.satellites.value();
}

double GPSLocationProvider::latitude() {
  return gpsPlus.location.lat();
}

double GPSLocationProvider::longitude() {
  return gpsPlus.location.lng();
}

long GPSLocationProvider::altitude() {
  return gpsPlus.altitude.value();
}

