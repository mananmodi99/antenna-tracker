#ifndef DIRECTIONAL_ANTENNA_H
#define DIRECTIONAL_ANTENNA_H

class Servo;

class DirectionalAntenna {
public:
  DirectionalAntenna();
  void tick();

private:
  Servo *tiltServo;
  Servo *panServo;
};

#endif



