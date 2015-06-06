#!/bin/bash

ARDUINO_FILE=arduino-${ARDUINO_IDE_VERSION}-linux64.$FILE_EXT
wget -O $ARDUINO_FILE http://arduino.cc/download.php?f=/$ARDUINO_FILE
tar xf $ARDUINO_FILE
rm -f $ARDUINO_FILE
echo "ARDUINO_DIR = arduino-${ARDUINO_IDE_VERSION}" >> Makefile


FILE=$MAKEFILE_VERSION.tar.gz

wget https://github.com/sudar/Arduino-Makefile/archive/$FILE
tar xzf $FILE
rm -f $FILE

ARDMK_DIR=Arduino-Makefile-$MAKEFILE_VERSION

echo "CPPFLAGS = -DDEBUG=$DEBUG" >> Makefile
echo "include $ARDMK_DIR/Arduino.mk" >> Makefile

make DEBUG=$DEBUG
