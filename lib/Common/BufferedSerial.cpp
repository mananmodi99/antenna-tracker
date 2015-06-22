#include "BufferedSerial.h"

#include <SoftwareSerial.h>

#define MESSAGE_END '\n'

#include <Arduino.h>

BufferedSerial::BufferedSerial(SoftwareSerial *s) {
  serial = s;
}

char* BufferedSerial::getMessage() {
  
  index = 0;
  boolean expecting = false;
  
  serial->listen();
  while (serial->available() || expecting) {
    if (!serial->available()) {
      continue;
    }
    
    char c = serial->read();
    if (c == MESSAGE_END) {
      break;
    }

    data[index] = c;
    index++;
    expecting = true;
  }
  
  if (index == 0) {
    return NULL;
  }
  
  char receivedChecksum = data[index-1];
  data[index-1] = '\0';

  char calculatedChecksum = checksum(data);

  if (receivedChecksum != calculatedChecksum) {
    return NULL;
  }
  
  return data;
}

void BufferedSerial::sendMessage(const char *message) {
  serial->print(message);
  serial->print(checksum(message));
  serial->print(MESSAGE_END);
}

void BufferedSerial::sendMessage(String &message) {
  sendMessage(message.c_str());
}

char BufferedSerial::checksum(const char *message) {
  int length = strlen(message);
  char checksum = 0;
  for (int i=0; i<length; i++) {
    checksum ^= message[i];
  }
  return checksum;
}

