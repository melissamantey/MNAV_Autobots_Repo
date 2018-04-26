#!/bin/bash

#echo $1 > /dev/ttySAC0 & read X < /dev/ttySAC0
#echo $X >> results.txt

stty -F /dev/ttySAC0 57600

echo " " >> gps.txt

cat >> gps.txt < /dev/ttySAC0
