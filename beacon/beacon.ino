#include <Metro.h>

#include "LocationProvider.h"
#include "GPSLocationProvider.h"
#include "MavlinkLocationProvider.h"
#include "Transmitter.h"
#include "LED.h"
#include "Configuration.h"
#include "State.h"

#define GPS_CONNECTION_TIMEOUT 3000

#if DEBUG
  SoftwareSerial *debugSerial = new SoftwareSerial(DEBUG_RX, DEBUG_TX);
#endif

LocationProvider *locationProvider;
Transmitter * transmitter;
LED *led;
State state = INIT_GPS;

Metro loop1hz = Metro(1000); // 1hz loop
Metro announceLoop = Metro(500); // 2hz loop
Metro gpsLoop = Metro(100); // 1000hz loop
Metro ledLoop = Metro(50); // 20hz loop

void setup() {
  DEBUG_PRINTLN("Antenna Tracker Beacon");
  //locationProvider = new GPSLocationProvider(GPS_RX, GPS_TX);
  
  locationProvider = new MavlinkLocationProvider(&Serial);
  transmitter = new Transmitter(LORA_RX, LORA_TX);
  led = new LED(LED_PIN);
}

void initGPS() { 
  
  if (locationProvider->isConnected()) {
    DEBUG_PRINT("Waiting for GPS fix, satellites: ");
    DEBUG_PRINTLN(locationProvider->numberOfSatellites());
    transmitter->sendMessage(String("WAITGPS:") + locationProvider->numberOfSatellites());
  }
  
  if (!locationProvider->isConnected() && millis() > GPS_CONNECTION_TIMEOUT) {
    state = NO_GPS;
  }
  else if (locationProvider->haveFix()) {
    state = RUNNING;
  }
}

void announceLocation() {
  DEBUG_PRINT("Location: ");
  DEBUG_PRINTF(locationProvider->latitude(), 6);
  DEBUG_PRINT(", ");
  DEBUG_PRINTF(locationProvider->longitude(), 6);
  DEBUG_PRINTLN("");
  
  String message = "L:";
  message += String(locationProvider->latitude(), 6);
  message += ":";
  message += String(locationProvider->longitude(), 6);
  message += ":";
  message += locationProvider->altitude();
  message += ":";
  message += locationProvider->numberOfSatellites();
  
  transmitter->sendMessage(message);
}

void announceNoGPS() {
  DEBUG_PRINTLN("No GPS connected");
  transmitter->sendMessage("NOGPSCONNECTED");
}

void loop() {
  
  if (gpsLoop.check()) {
    locationProvider->tick();
  }
  
  if (ledLoop.check()) {
    led->tick();
  }
  
  switch (state) {
    case NO_GPS:
      if (announceLoop.check()) {
        announceNoGPS();
        delay(5000);
        
        if (locationProvider->isConnected()) {
          state = INIT_GPS;
        }
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
