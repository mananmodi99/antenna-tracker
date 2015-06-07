#include "Display.h"
#include "Configuration.h"

Display::Display() {
  numberOfSatellites = 0;
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

void Display::showStatus(byte satellites) {
  if (mode == STATUS && satellites == numberOfSatellites) {
    return;
  }
  
  mode = STATUS;
  numberOfSatellites = satellites;
  
  DEBUG_PRINT("Satellites: ");
  DEBUG_PRINTLN(numberOfSatellites);
}
