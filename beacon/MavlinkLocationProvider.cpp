#include "MavlinkLocationProvider.h"
#include "Configuration.h"

#define MIN_NUMBER_OF_SATELLITES 7

MavlinkLocationProvider::MavlinkLocationProvider(HardwareSerial *s) {
  serial = s;
  serial->begin(57600);
  connected = false;
  lastHeartbeatTime = 0;
  lastDataReceiveTime = 0;
  lastRequestedData = 0;
  mavlinkNumberOfSatellites = 0;
}

void MavlinkLocationProvider::tick() {
  
  readMessages();
  
  unsigned long currentTime = millis();
  
  if (
    (currentTime - lastDataReceiveTime > 3000 || lastDataReceiveTime == 0)
    && currentTime - lastHeartbeatTime < 1000
    && currentTime - lastRequestedData > 10000
  ) {
    requestData(); 
  }
}

void MavlinkLocationProvider::readMessages() {

  mavlink_message_t msg; 
  mavlink_status_t status;
  
  while(serial->available() > 0) {
    uint8_t c = serial->read();
    if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
      
      switch(msg.msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:
          handleHeartbeat(&msg);
          break;
 
        case MAVLINK_MSG_ID_GPS_RAW_INT:
          handleGPSInfo(&msg);
          break;
          
        case MAVLINK_MSG_ID_STATUSTEXT:
          handleStatusMessage(&msg);
          break;
          
        case MAVLINK_MSG_ID_REQUEST_DATA_STREAM:
          break;
      }
    }
  }
}

boolean MavlinkLocationProvider::isConnected() {
  return connected;
}

boolean MavlinkLocationProvider::haveFix() {
  return fixType == 3 && mavlinkNumberOfSatellites >= MIN_NUMBER_OF_SATELLITES;
}

byte MavlinkLocationProvider::numberOfSatellites() {
  return mavlinkNumberOfSatellites;
}

double MavlinkLocationProvider::latitude() {
  return mavlinkLatitude;
}

double MavlinkLocationProvider::longitude() {
  return mavlinkLongitude;
}

long MavlinkLocationProvider::altitude() {
  return 0;
}

void MavlinkLocationProvider::handleHeartbeat(mavlink_message_t *msg) {
  mavlink_heartbeat_t packet;
  mavlink_msg_heartbeat_decode(msg, &packet);
  
  if ((*msg).sysid == 0xff) {
    return;
  }
        
  if (!connected) {
    connected = true;
  }
  DEBUG_PRINTLN("MAVLINK: Heartbeat");
  systemId    = (*msg).sysid;
  componentId = (*msg).compid;
  lastHeartbeatTime = millis();
}

void MavlinkLocationProvider::handleGPSInfo(mavlink_message_t *msg) {
  DEBUG_PRINTLN("MAVLINK: GPS Info");
  mavlinkLatitude =  mavlink_msg_gps_raw_int_get_lat(msg) / 10000000.0f;
  mavlinkLongitude =  mavlink_msg_gps_raw_int_get_lon(msg) / 10000000.0f;
  mavlinkNumberOfSatellites = (uint8_t) mavlink_msg_gps_raw_int_get_satellites_visible(msg);
  fixType = (uint8_t) mavlink_msg_gps_raw_int_get_fix_type(msg);
  
  lastDataReceiveTime = millis();
}

void MavlinkLocationProvider::handleStatusMessage(mavlink_message_t *msg) {
  mavlink_statustext_t statustext;
  mavlink_msg_statustext_decode(msg, &statustext);
  DEBUG_PRINTLN("MAVLINK: STATUS: " + String(statustext.text));
}

void MavlinkLocationProvider::sendMessage(mavlink_message_t* msg) {
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  uint16_t len = mavlink_msg_to_send_buffer(buf, msg);
  
  serial->write(buf, len);
}

void MavlinkLocationProvider::requestData() {
  
  //DEBUG_PRINTLN("MAVLINK: Requesting for data");
  
  mavlink_message_t msg;
  // first disable all
  mavlink_msg_request_data_stream_pack(127, 0, &msg, systemId, componentId, MAV_DATA_STREAM_ALL, 0, 0);
  sendMessage(&msg);
  delay(10);
  
  mavlink_msg_request_data_stream_pack(127, 0, &msg, systemId, componentId, MAV_DATA_STREAM_ALL, 1, 1);
  sendMessage(&msg);
  delay(10);
  
  lastRequestedData = millis();
}
