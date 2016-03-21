
#define LORA_RX 9
#define LORA_TX 10
#define GPS_RX 11
#define GPS_TX 12
#define LED_PIN 13

#ifndef DEBUG
  #define DEBUG true
#endif

#if DEBUG
  #define DEBUG_PRINT(x)      Serial.print(x)
  #define DEBUG_PRINTF(x, y)  Serial.print(x, y)
  #define DEBUG_PRINTDEC(x)   Serial.print(x, DEC)
  #define DEBUG_PRINTLN(x)    Serial.println(x)
  #define DEBUG_F_PRINT(x)      Serial.print(F(x))
  #define DEBUG_F_PRINTLN(x)    Serial.println(F(x))
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTF(x, y)
  #define DEBUG_PRINTDEC(x)
  #define DEBUG_PRINTLN(x) 
  #define DEBUG_F_PRINT(x)
  #define DEBUG_F_PRINTLN(x)
#endif
