#include "DirectionalAntenna.h"
#include "Configuration.h"

#include <Arduino.h>
#include <Servo.h> 

DirectionalAntenna::DirectionalAntenna() {
  horizontalServo = new Servo;
  horizontalServo->attach(HORIZONTAL_SERVO);
  
  verticalServo = new Servo;
  verticalServo->attach(VERTICAL_SERVO);
  
  horizontalServo->write(100);
  verticalServo->write(100);
  
  horizontalServo->write(0);
  verticalServo->write(0);
  delay(500);
  
  horizontalServo->write(180);
  verticalServo->write(180);
}

void DirectionalAntenna::tick() {
}
