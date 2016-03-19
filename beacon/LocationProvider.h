#ifndef LOCATION_PROVIDER_H
#define LOCATION_PROVIDER_H

class LocationProvider {
public:
  virtual void tick();
  virtual boolean isConnected();
  virtual boolean haveFix();
  virtual byte numberOfSatellites();
  virtual double latitude();
  virtual double longitude();
  virtual long altitude();
};

#endif



