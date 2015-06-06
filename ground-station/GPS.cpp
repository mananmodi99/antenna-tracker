#include "GPS.h"
#include "Configuration.h"

#include <SoftwareSerial.h>

GPS::GPS() {
  serialPort = new SoftwareSerial(GPS_RX, GPS_TX);
  //serialPort->begin(38400);
  serialPort->begin(9600);
  step = 0;
}

void GPS::read() { 
  int bytesAvailable = serialPort->available();
  for (int i=0; i<bytesAvailable; i++) {
    byte data = serialPort->read();
    
    switch (step) {
      case 0:
        DEBUG_PRINTLN(data);
        if (data == 0xB5) {
          step++;
          DEBUG_PRINTLN("JEIII");
        }
        break;
       case 1:
         if (data == 0x62) {
           step++;
         }
         else {
           step = 0;
         }
         break;
       case 2:
         ubxClass = data;
         step++;
    }
  }
}
