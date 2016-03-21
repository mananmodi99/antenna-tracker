#ifndef MAVLINK_LOCATION_PROVIDER_H
#define MAVLINK_LOCATION_PROVIDER_H

#include <Arduino.h>

// https://groups.google.com/forum/embed/#!topic/mavlink/i7tXh9LbtlQ
#define MAVLINK_COMM_NUM_BUFFERS 1
#define MAVLINK_MAX_PAYLOAD_LEN 104

#include <common/mavlink.h>

#include "LocationProvider.h"

class SoftwareSerial;

class MavlinkLocationProvider: public LocationProvider {
public:
  MavlinkLocationProvider(int rxPin, int txPin);
  void tick();
  boolean isConnected();
  boolean haveFix();
  byte numberOfSatellites();
  double latitude();
  double longitude();
  long altitude();

private:
  SoftwareSerial *serial;
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



