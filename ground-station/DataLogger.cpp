#include "DataLogger.h"
#include "Configuration.h"

#include <SPI.h>
#include <SD.h>

#define SEQ_FILE "seq.txt"
#define TELEMETRY_FILE "tel.txt"

const int chipSelect = 53;

DataLogger::DataLogger() {

  lastMessageNumber = 0;

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }

  int seqNumber;
  if (SD.exists(SEQ_FILE)) {
    seqNumber = 99;
    
    File seqFile = SD.open(SEQ_FILE, FILE_READ);
    
    String fileContent;
    while (seqFile.available()) {
      fileContent += (char)seqFile.read();
    }
    seqFile.close();
    SD.remove(SEQ_FILE);

    seqNumber = atoi(fileContent.c_str()) + 1;
  }
  else {
    seqNumber = 1;
  }
  
  File seqFile = SD.open(SEQ_FILE, FILE_WRITE);
  seqFile.print(seqNumber);
  seqFile.close();

  String dirName = String(seqNumber);
  char dir[dirName.length()+1];
  dirName.toCharArray(dir, sizeof(dir));
  
  SD.mkdir(dir);

  String fileName;
  fileName += seqNumber;
  fileName += "/";
  fileName += TELEMETRY_FILE;
  rawTelemetryInfoFile = SD.open(fileName.c_str(), FILE_WRITE);

}

void DataLogger::logRawTelemetry(String message, long number) {
  if (number == lastMessageNumber) {
    return;
  }
  lastMessageNumber = number;

  rawTelemetryInfoFile.println(message + " - NR " + lastMessageNumber);
  rawTelemetryInfoFile.flush();
}

