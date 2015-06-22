#include "GPS.h"
#include "Configuration.h"

#include <SoftwareSerial.h>

#define MIN_NUMBER_OF_SATELLITES 4

GPS::GPS() {
  serialPort = new SoftwareSerial(GPS_RX, GPS_TX);
  serialPort->begin(9600);
}

void GPS::tick() {
  serialPort->listen();
  while (serialPort->available()) {
    gpsPlus.encode(serialPort->read());
  }
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

