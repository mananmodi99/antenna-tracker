#include "GPS.h"
#include "Configuration.h"
#include "Compass.h"
#include "Display.h"
#include "Receiver.h"
#include "BufferedSerial.h"
#include "DirectionalAntenna.h"
#include "DataLogger.h"

enum State {
  INIT_GPS,
  LOCAL_GPS_FIX, // There is a local GPS fix but no telemetry data
  RUNNING
};

#include <Metro.h>
#include <SoftwareSerial.h>

GPS *gps;
Compass *compass;
Display *display;
Receiver *receiver;
DirectionalAntenna *antenna;
DataLogger *dataLogger;

State state = INIT_GPS;

Metro loop50hz = Metro(20); // 50hz loop
Metro gpsLoop = Metro(250); // 10hz loop
Metro receiverLoop = Metro(200); // 5hz loop
Metro displayLoop = Metro(200); // 5hz loop

void setup() {
  Serial.begin(9600);
  DEBUG_PRINTLN("Starting Ground Station");
  gps = new GPS;
  //compass = new Compass();
  display = new Display;
  //antenna = new DirectionalAntenna;
  dataLogger = new DataLogger;
  
  LORA_SERIAL.begin(9600);
  receiver = new Receiver(new BufferedSerial(&LORA_SERIAL));
}

void loop() {
  
  if (gpsLoop.check()) {
    gps->tick();
  }
  
  if (receiverLoop.check()) {
    receiver->tick();
    dataLogger->logRawTelemetry(receiver->lastMessage(), receiver->lastMessageNumber());
  }
  
  if (loop50hz.check()) {
    //compass->tick();
    //antenna->tick();
    
    switch (state) {
      case INIT_GPS:
        display->showWaitingForGPS(gps->numberOfSatellites());
        if (gps->haveFix()) {
          state = RUNNING;
        }
        break;
      case LOCAL_GPS_FIX:
        display->showLocalFix(gps);
        break;
      case RUNNING:
        double distance = gps->distanceTo(receiver->latitude(), receiver->longitude());
        display->showStatus(gps->numberOfSatellites(), distance);
        break;
    }
  }
  
  if (displayLoop.check()) {
    
    display->showTelemetry(receiver);
    
    //display->showLocation(receiver->latitude(), receiver->longitude());
  }
}
