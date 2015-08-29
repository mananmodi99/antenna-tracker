#include "Receiver.h"
#include "BufferedSerial.h"

#include <SoftwareSerial.h>

Receiver::Receiver(BufferedSerial* serial) {
  lora = serial;
  lastLatitude = -1;
  lastLongitude = -1;
  _lastSeenSatellites = 0;
  _lastMessageNumber = 0;
  _haveFix = false;
}

void Receiver::tick() {
  char* message = lora->getMessage();
  if (message == NULL) {
    return;
  }
  
  String rawMessage = String(message);
  int pos = rawMessage.indexOf('|');
  String number = rawMessage.substring(pos+1);
  _lastMessageNumber = atol(number.c_str());

  rawMessage = rawMessage.substring(0, pos);
    
  _lastMessage = rawMessage;
  pos = rawMessage.indexOf(':');
  String token = rawMessage.substring(0, pos);
  
  if (token == "L") {
    _haveFix = true;
    pos++;
    int pos2 = rawMessage.indexOf(':', pos);
    token = rawMessage.substring(pos, pos2);
    lastLatitude = atof(token.c_str());
      
    pos = pos2 + 1;
    pos2 = rawMessage.indexOf(':', pos);
    token = rawMessage.substring(pos, pos2);
    lastLongitude = atof(token.c_str());
      
    pos = pos2 + 1;
    pos2 = rawMessage.indexOf(':', pos);
    token = rawMessage.substring(pos, pos2);
    lastAltitude = atoi(token.c_str());
      
    pos = pos2 + 1;
    pos2 = rawMessage.indexOf(':', pos);
    token = rawMessage.substring(pos, pos2);
    _lastSeenSatellites = atoi(token.c_str());
  }
  else if (token == "WAITGPS") {
    _haveFix = false;
      
    pos++;
    int pos2 = rawMessage.indexOf(':', pos);
    token = rawMessage.substring(pos, pos2);
    _lastSeenSatellites = atof(token.c_str());
  }
}

double Receiver::latitude() {
  return lastLatitude;
}

double Receiver::longitude() {
  return lastLongitude;
}

int Receiver::lastSeenSatellites() {
  return _lastSeenSatellites;
}

String Receiver::lastMessage() {
  return _lastMessage;
}

long Receiver::lastMessageNumber() {
  return _lastMessageNumber;
}

bool Receiver::haveFix() {
  return _haveFix;
}
