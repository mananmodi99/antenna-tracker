#include "GPS.h"
#include "Configuration.h"
#include "Compass.h"

#include <Metro.h>
#include <SoftwareSerial.h>

GPS *gps;
Compass *compass;

Metro loop50hz = Metro(20); // 50hz loop

void setup() {
  Serial.begin(9600);
  DEBUG_PRINTLN("Starting Ground Station");
  gps = new GPS();
  compass = new Compass();
}

void loop() {
  if (loop50hz.check()) {
    //gps->tick();
    compass->tick();
  }
}
