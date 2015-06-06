#include "GPS.h"
#include "Configuration.h"

#include <SoftwareSerial.h>

GPS *gps;

void setup() {
  Serial.begin(9600);
  DEBUG_PRINTLN("Starting Ground Station");
  gps = new GPS();
}

void loop() {
  gps->read();
}
