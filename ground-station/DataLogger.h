#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include <SD.h>

class DataLogger {
public:
  DataLogger();
  void logRawTelemetry(String message, long number);

private:
  File rawTelemetryInfoFile;
  long lastMessageNumber;
};

#endif



