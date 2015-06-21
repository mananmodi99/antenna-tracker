#!/bin/bash

ARDUINO_IDE_VERSION=1.6.4
MAKEFILE_VERSION=1.5

if [ $(uname) == 'Darwin' ]
then
    PLATFORM='macosx'
    FILE_EXT='zip'
    ARDUINO_DIR='Arduino.app/Contents/Java'
else
    PLATFORM='linux64'
    FILE_EXT='tar.xz'
    ARDUINO_DIR="arduino-$ARDUINO_IDE_VERSION"
fi

if [ ! -e "$ARDUINO_DIR" ]
then
    ARDUINO_FILE=arduino-${ARDUINO_IDE_VERSION}-$PLATFORM.$FILE_EXT
    wget -O $ARDUINO_FILE http://arduino.cc/download.php?f=/$ARDUINO_FILE

    if [ $FILE_EXT == 'zip' ]
    then
        unzip $ARDUINO_FILE
    else
        tar xf $ARDUINO_FILE
    fi

rm -f $ARDUINO_FILE
fi

ARDMK_DIR=Arduino-Makefile-$MAKEFILE_VERSION

if [ ! -e $ARDMK_DIR ]
then
    FILE=$MAKEFILE_VERSION.tar.gz
    wget https://github.com/sudar/Arduino-Makefile/archive/$FILE
    tar xzf $FILE
    rm -f $FILE
fi

if [ ! -e "Makefile" ]
then
    echo 'PROJECT_DIR = $(shell pwd)' >> Makefile
    echo "ARDUINO_DIR = $ARDUINO_DIR" >> Makefile
    echo 'BOARD_TAG = nano' >> Makefile
    echo 'BOARD_SUB = atmega328' >> Makefile
    echo "CPPFLAGS = -DDEBUG=$DEBUG" >> Makefile
    echo 'USER_LIB_PATH := $(realpath $(PROJECT_DIR)/../lib)' >> Makefile
    echo 'ARDUINO_LIBS = SoftwareSerial Metro TinyGPSPlus' >> Makefile
    echo 'MONITOR_PORT = /dev/cu.wc*' >> Makefile
    echo "include $ARDMK_DIR/Arduino.mk" >> Makefile
fi

make DEBUG=$DEBUG
