#include "Display.h"
#include "Configuration.h"

Display::Display() {
  numberOfSatellites = 0;
  distance = 0;
}

void Display::showWaitingForGPS(byte satellites) {
  if (mode == WAITING_GPS && satellites == numberOfSatellites) {
    return;
  }
  
  mode = WAITING_GPS;
  numberOfSatellites = satellites;
  
  DEBUG_PRINT("Waiting for local GPS fix, satellites: ");
  DEBUG_PRINTLN(numberOfSatellites);
}

void Display::showStatus(byte satellites, double dist) {
  if (mode == STATUS && satellites == numberOfSatellites && dist == distance) {
    return;
  }
  
  mode = STATUS;
  numberOfSatellites = satellites;
  distance = dist;
  
  DEBUG_PRINT("Satellites: ");
  DEBUG_PRINT(numberOfSatellites);
  DEBUG_PRINT(", distance: ");
  
  if (distance > 1000) {
    double km = distance / 1000;
    DEBUG_PRINT(km);
    DEBUG_PRINTLN(" km");
  }
  else {
    DEBUG_PRINT((int)distance);
    DEBUG_PRINTLN(" m");
  }
}
