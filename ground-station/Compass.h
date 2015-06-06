#ifndef COMPASS_H
#define COMPASS_H

#include <HMC5883L.h>

class Compass {
public:
  Compass();
  void tick();

private:
  HMC5883L sensor;
};

#endif



