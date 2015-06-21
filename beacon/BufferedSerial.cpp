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
  
  data[index] = '\0';
  
  return data;
}

void BufferedSerial::sendMessage(char *message) {
  serial->print(message);
  serial->print(MESSAGE_END);
}

void BufferedSerial::sendMessage(String &message) {
  serial->print(message);
  serial->print(MESSAGE_END);
}

