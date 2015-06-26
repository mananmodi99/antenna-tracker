#include "GPS.h"
#include "Transmitter.h"
#include "LED.h"
#include "Configuration.h"

#include <Metro.h>

enum State {
  INIT_GPS,
  RUNNING
};

GPS *gps;
Transmitter * transmitter;
LED *led;
State state = INIT_GPS;

Metro loop1hz = Metro(1000); // 1hz loop
Metro announceLoop = Metro(500); // 2hz loop
Metro gpsLoop = Metro(20); // 50hz loop
Metro ledLoop = Metro(50); // 20hz loop

void setup() {
  Serial.begin(9600);
  gps = new GPS();
  transmitter = new Transmitter();
  led = new LED(LED_PIN);
  led->statusWaiting();
}

void initGPS() { 
  DEBUG_PRINT("Waiting for GPS fix, satellites: ");
  DEBUG_PRINTLN(gps->numberOfSatellites());
  transmitter->sendMessage("WAITGPS");
  
  if (gps->haveFix()) {
    state = RUNNING;
    led->statusRunning();
  }
}

void announceLocation() {
  DEBUG_PRINT("Location: ");
  DEBUG_PRINTF(gps->latitude(), 6);
  DEBUG_PRINT(", ");
  DEBUG_PRINTF(gps->longitude(), 6);
  DEBUG_PRINTLN("");
  
  String message = "L:";
  message += String(gps->latitude(), 6);
  message += ":";
  message += String(gps->longitude(), 6);
  message += ":";
  message += gps->altitude();
  message += ":";
  message += gps->numberOfSatellites();
  
  transmitter->sendMessage(message);
}

void loop() {
  
  if (gpsLoop.check()) {
    gps->tick();
  }
  
  if (ledLoop.check()) {
    led->tick();
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
