#ifndef STATE_H
#define STATE_H

enum State {
  NO_GPS,
  INIT_GPS,
  RUNNING
};

extern State state;

#endif



