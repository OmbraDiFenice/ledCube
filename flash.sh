#!/bin/bash

COMPILE=0
UPLOAD=0
SCREEN=0

function usage() {
    echo "usage:"
    echo "  $0 [-c] [-u] [-s] [-h]"
    echo "    -h show this help and exit"
    echo "    -c compile"
    echo "    -u upload"
    echo "    -s run screen"
    echo "witho no parameters defaults to -c -u -s"
}

while getopts 'cush' flag
do
    case "${flag}" in
        c) COMPILE=1
           shift 1;;
        u) UPLOAD=1
           shift 1;;
        s) SCREEN=1
           shift 1;;
        h) usage
           exit 0 ;;
        *) usage
           exit 1 ;;
    esac
done

if (( $COMPILE == 0 && $UPLOAD == 0 && $SCREEN == 0 ))
then
    COMPILE=1
    UPLOAD=1
    SCREEN=1
fi

if (( $COMPILE == 1 ))
then
    arduino-cli compile -v -b arduino:avr:nano "$1" || exit 1
fi

if (( $UPLOAD == 1 ))
then
    arduino-cli upload -v -p /dev/ttyUSB0 -b arduino:avr:nano:cpu=atmega328old -t "$1" || exit 2
fi

if (( $SCREEN == 1 ))
then
    screen /dev/ttyUSB0 9600
fi
