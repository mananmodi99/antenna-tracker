#include "BufferedSerial.h"

#include <SoftwareSerial.h>
#include <HardwareSerial.h>

#define MESSAGE_END '\n'

#include <Arduino.h>

BufferedSerial::BufferedSerial(SoftwareSerial *serial) {
  softwareSerial = serial;
  hardwareSerial = NULL;
}

BufferedSerial::BufferedSerial(HardwareSerial *serial) {
    hardwareSerial = serial;
    softwareSerial = NULL;
}

char* BufferedSerial::getMessage() {
  
  if (hardwareSerial != NULL) {
    readHardwareSerial();
  }
  else {
    readSoftwareSerial();
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
  if (softwareSerial != NULL) {
    softwareSerial->print(message);
    softwareSerial->print(checksum(message));
    softwareSerial->print(MESSAGE_END);
  }
  else {
    hardwareSerial->print(message);
    hardwareSerial->print(checksum(message));
    hardwareSerial->print(MESSAGE_END);
  }
}

void BufferedSerial::sendMessage(String &message) {
  sendMessage(message.c_str());
}

void BufferedSerial::readSoftwareSerial() {

  index = 0;
  boolean expecting = false;
    
  softwareSerial->listen();
  while (softwareSerial->available() || expecting) {
    if (!softwareSerial->available()) {
      continue;
    }
        
    char c = softwareSerial->read();
    if (c == MESSAGE_END) {
      break;
    }
      
    if (index > BUFFER_SIZE-2) {
      break;
    }
        
    data[index] = c;
    index++;
    expecting = true;
  }
}

void BufferedSerial::readHardwareSerial() {

  index = 0;
  boolean expecting = false;

  while (hardwareSerial->available() || expecting) {
    if (!hardwareSerial->available()) {
      continue;
    }
        
    char c = hardwareSerial->read();
    if (c == MESSAGE_END) {
      break;
    }
      
    if (index > BUFFER_SIZE-2) {
      break;
    }
        
    data[index] = c;
    index++;
    expecting = true;
  }
}

char BufferedSerial::checksum(const char *message) {
  int length = strlen(message);
  char checksum = 0;
  for (int i=0; i<length; i++) {
    checksum ^= message[i];
  }
  return checksum;
}

