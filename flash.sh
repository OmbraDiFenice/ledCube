#!/bin/bash

arduino-cli compile -v -b arduino:avr:nano "$1" || exit 1
arduino-cli upload -v -p /dev/ttyUSB0 -b arduino:avr:nano:cpu=atmega328old -t "$1" || exit 2
