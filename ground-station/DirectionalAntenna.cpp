#include "DirectionalAntenna.h"
#include "Configuration.h"

#include <Arduino.h>
#include <Servo.h> 

#define TILT_MIN 90
#define TILT_MAX 179

#define PAN_NEUTRAL 1493
#define PAN_MIN 2000
#define PAN_MAX 1050

DirectionalAntenna::DirectionalAntenna() {
  tiltServo = new Servo;
  tiltServo->attach(TILT_SERVO);
  tiltServo->write(TILT_MAX);
  
  panServo = new Servo;
  panServo->attach(PAN_SERVO);
  panServo->writeMicroseconds(1500);
  
  delay(3000);
  
  tiltServo->write(TILT_MIN);
  panServo->writeMicroseconds(PAN_MIN);
  
  delay(3000);
  panServo->writeMicroseconds(PAN_NEUTRAL);
  
  delay(3000);
  tiltServo->write(TILT_MAX);
  panServo->writeMicroseconds(PAN_MAX);
  
  delay(3000);
  panServo->writeMicroseconds(PAN_NEUTRAL);
}

void DirectionalAntenna::tick() {
  tiltServo->write(TILT_MAX);
  panServo->writeMicroseconds(PAN_NEUTRAL);
}
