#include "GPS.h"
#include "Configuration.h"

#include <Metro.h>
#include <SoftwareSerial.h>

GPS *gps;

Metro loop50hz = Metro(20); // 50hz loop

void setup() {
  Serial.begin(9600);
  DEBUG_PRINTLN("Starting Ground Station");
  gps = new GPS();
}

void loop() {
  if (loop50hz.check()) {
    gps->tick();
  }
}
