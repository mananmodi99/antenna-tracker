#include "Receiver.h"
#include "BufferedSerial.h"
#include "Configuration.h"

#include <SoftwareSerial.h>

Receiver::Receiver() {
  LORA_SERIAL.begin(9600);
  lora = new BufferedSerial(&LORA_SERIAL);
}

void Receiver::tick() {
  char* message = lora->getMessage();
  if (message == NULL) {
    return;
  }
  
  DEBUG_PRINTLN(message);
  String rawMessage = String(message);
  int pos = rawMessage.indexOf(':');
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
