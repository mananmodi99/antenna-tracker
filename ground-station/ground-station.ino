#include "GPS.h"
#include "Configuration.h"
#include "Compass.h"
#include "Display.h"
#include "Receiver.h"

enum State {
  INIT_GPS,
  RUNNING
};

#include <Metro.h>
#include <SoftwareSerial.h>

GPS *gps;
Compass *compass;
Display *display;
Receiver *receiver;

State state = INIT_GPS;

Metro loop50hz = Metro(20); // 50hz loop

void setup() {
  Serial.begin(9600);
  DEBUG_PRINTLN("Starting Ground Station");
  gps = new GPS();
  compass = new Compass();
  display = new Display();
  receiver = new Receiver();
}

void loop() {
  if (loop50hz.check()) {
    gps->tick();
    //compass->tick();
    
    switch (state) {
      case INIT_GPS:
        display->showWaitingForGPS(gps->numberOfSatellites());
        if (gps->haveFix()) {
          state = RUNNING;
        }
        break;
      case RUNNING:
        double distance = gps->distanceTo(receiver->latitude(), receiver->longitude());
        display->showStatus(gps->numberOfSatellites(), distance);
        break;
    }
  }
}
