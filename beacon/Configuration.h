
#define LORA_RX 9
#define LORA_TX 10
#define GPS_RX 11
#define GPS_TX 12
#define LED_PIN 13

#define DEBUG_TX 11
#define DEBUG_RX 12

#ifndef DEBUG
  #define DEBUG true
#endif

#if DEBUG
  #include <SoftwareSerial.h>
  extern SoftwareSerial *debugSerial;

  #define DEBUG_PRINT(x)      debugSerial->print(x)
  #define DEBUG_PRINTF(x, y)  debugSerial->print(x, y)
  #define DEBUG_PRINTDEC(x)   debugSerial->print(x, DEC)
  #define DEBUG_PRINTLN(x)    debugSerial->println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTF(x, y)
  #define DEBUG_PRINTDEC(x)
  #define DEBUG_PRINTLN(x) 
#endif
