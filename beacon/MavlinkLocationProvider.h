#ifndef MAVLINK_LOCATION_PROVIDER_H
#define MAVLINK_LOCATION_PROVIDER_H

#include <Arduino.h>
#include <mavlink.h>

#include "LocationProvider.h"

class MavlinkLocationProvider: public LocationProvider {
public:
  MavlinkLocationProvider(HardwareSerial*);
  void tick();
  boolean isConnected();
  boolean haveFix();
  byte numberOfSatellites();
  double latitude();
  double longitude();
  long altitude();

private:
  HardwareSerial *serial;
  bool connected;
  unsigned long lastHeartbeatTime;
  unsigned long lastDataReceiveTime;
  unsigned long lastRequestedData;
  
  double mavlinkLatitude;
  double mavlinkLongitude;
  uint8_t mavlinkNumberOfSatellites;
  uint8_t fixType; // GPS lock 0-1=no fix, 2=2D, 3=3D
  
  unsigned int	systemId;
  unsigned int	componentId;
  void readMessages();
  void handleHeartbeat(mavlink_message_t *msg);
  void handleGPSInfo(mavlink_message_t *msg);
  void handleStatusMessage(mavlink_message_t *msg);
  void sendMessage(mavlink_message_t* msg);
  void requestData();
};

#endif



