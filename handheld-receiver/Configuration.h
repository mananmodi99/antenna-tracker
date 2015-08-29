
#define LORA_RX 6
#define LORA_TX 7


#ifndef DEBUG
  #define DEBUG true
#endif

#if DEBUG
  #define DEBUG_PRINT(x)      Serial.print(x)
  #define DEBUG_PRINTF(x, y)  Serial.print(x, y)
  #define DEBUG_PRINTDEC(x)   Serial.print(x, DEC)
  #define DEBUG_PRINTLN(x)    Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTF(x, y)
  #define DEBUG_PRINTDEC(x)
  #define DEBUG_PRINTLN(x) 
#endif
