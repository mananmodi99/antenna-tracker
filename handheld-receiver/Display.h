#ifndef DISPLAY_H
#define DISPLAY_H

class Adafruit_PCD8544;
class Receiver;

class Display {
public:
  Display();
  void status(Receiver *receiver);

private:
  void showWaitingForFix(Receiver *receiver);
  void showCoordinates(Receiver *receiver);
  Adafruit_PCD8544 *lcd;

};

#endif



