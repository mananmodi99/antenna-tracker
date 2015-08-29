#include "Receiver.h"
#include "BufferedSerial.h"

#include <SoftwareSerial.h>

Receiver::Receiver(BufferedSerial* serial) {
  lora = serial;
  lastLatitude = -1;
  lastLongitude = -1;
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
  
  if (token != "L") {
    return;
  }
  
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
  lastSeenSatellites = atoi(token.c_str());
}

double Receiver::latitude() {
  return lastLatitude;
}

double Receiver::longitude() {
  return lastLongitude;
}

String Receiver::lastMessage() {
  return _lastMessage;
}

long Receiver::lastMessageNumber() {
  return _lastMessageNumber;
}
