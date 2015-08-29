#include "GPS.h"
#include "Transmitter.h"
#include "LED.h"
#include "Configuration.h"
#include "State.h"

#include <Metro.h>

#define GPS_CONNECTION_TIMEOUT 3000

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
  gps = new GPS(GPS_RX, GPS_TX);
  transmitter = new Transmitter(LORA_RX, LORA_TX);
  led = new LED(LED_PIN);
}

void initGPS() { 
  
  if (gps->isConnected()) {
    DEBUG_PRINT("Waiting for GPS fix, satellites: ");
    DEBUG_PRINTLN(gps->numberOfSatellites());
    transmitter->sendMessage(String("WAITGPS:") + gps->numberOfSatellites());
  }
  
  if (!gps->isConnected() && millis() > GPS_CONNECTION_TIMEOUT) {
    state = NO_GPS;
  }
  else if (gps->haveFix()) {
    state = RUNNING;
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

void announceNoGPS() {
  DEBUG_PRINTLN("No GPS connected");
  transmitter->sendMessage("NOGPSCONNECTED");
}

void loop() {
  
  if (gpsLoop.check()) {
    gps->tick();
  }
  
  if (ledLoop.check()) {
    led->tick();
  }
  
  switch (state) {
    case NO_GPS:
      if (announceLoop.check()) {
        announceNoGPS();
      }
    
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
