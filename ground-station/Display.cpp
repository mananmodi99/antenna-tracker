#include "Display.h"
#include "Configuration.h"

#include <LiquidCrystal.h>

Display::Display() {
  numberOfSatellites = 0;
  distance = 0;
  lcd = new LiquidCrystal(12, 11, 5, 4, 3, 2);
  lcd->begin(20, 4);
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

void Display::showLocation(double latitude, double longitude) {
  DEBUG_PRINT("Lat:");
  DEBUG_PRINT(latitude);
  DEBUG_PRINT(", lng:");
  DEBUG_PRINTLN(longitude);
  
  lcd->setCursor(0, 0);
  
  lcd->print("Lat: ");
  lcd->print(String(latitude, 6));
  
  lcd->setCursor(0, 1);
  lcd->print("Lng: ");
  lcd->print(String(longitude, 6));
}
