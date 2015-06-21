#include "GPS.h"
#include "Configuration.h"

#include <Metro.h>

enum State {
  INIT_GPS,
  RUNNING
};

GPS *gps;
State state = INIT_GPS;

Metro loop1hz = Metro(1000); // 1hz loop
Metro announceLoop = Metro(500); // 2hz loop
Metro loop50hz = Metro(20); // 50hz loop

void setup() {
  Serial.begin(9600);
  gps = new GPS();
}

void initGPS() { 
  DEBUG_PRINT("Waiting for GPS fix, satellites: ");
  DEBUG_PRINTLN(gps->numberOfSatellites());
  
  if (gps->haveFix()) {
    state = RUNNING;
  }
}

void announceLocation() {
  DEBUG_PRINT("Location: ");
  DEBUG_PRINT(gps->latitude());
  DEBUG_PRINT(", ");
  DEBUG_PRINTLN(gps->longitude());
}

void loop() {
  
  if (loop50hz.check()) {
    gps->tick();
  }
  
  switch (state) {
    case INIT_GPS:
      if (loop1hz.check()) {
        initGPS();
      }
    break;
    
    case RUNNING:
      if (announceLoop.check()) {
        announceLocation();
      }
    break;
  }
}