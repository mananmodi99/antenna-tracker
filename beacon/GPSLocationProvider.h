#ifndef GPS_LOCATION_PROVIDER_H
#define GPS_LOCATION_PROVIDER_H

#include <Arduino.h>
#include <TinyGPS++.h>

#include "LocationProvider.h"

class HardwareSerial;

class GPSLocationProvider: public LocationProvider {
public:
  GPSLocationProvider(HardwareSerial*);
  void tick();
  boolean isConnected();
  boolean haveFix();
  byte numberOfSatellites();
  double latitude();
  double longitude();
  long altitude();

private:
  HardwareSerial *serialPort;
  TinyGPSPlus gpsPlus;
  boolean connected;
};

#endif



