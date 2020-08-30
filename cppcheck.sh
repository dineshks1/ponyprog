#!/bin/bash

CPPCHCK=`type -p cppcheck`

if [ ! -f "$CPPCHCK" ]; then
   # not found exit
   echo "please install cppcheck and restart this script"
   exit 0
fi

COUNT=$(nproc)
echo "number of detected CPUs =" $COUNT

#cppcheck -j $COUNT --force --inline-suppr --enable=warning . 2>errors.txt
cppcheck -j $COUNT --force --enable=warning . 2>cppreport.txt
