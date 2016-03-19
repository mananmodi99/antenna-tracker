#ifndef LOCATION_PROVIDER_H
#define LOCATION_PROVIDER_H

class LocationProvider {
public:
  virtual void tick() = 0;
  virtual boolean isConnected() = 0;
  virtual boolean haveFix() = 0;
  virtual byte numberOfSatellites() = 0;
  virtual double latitude() = 0;
  virtual double longitude() = 0;
  virtual long altitude() = 0;
};

#endif



