#!/bin/bash

str=$(head -20 /dev/ttyACM0 | grep GPGGA)

gps_valid=$(echo $str | cut -f7 -d,)

if [ "$gps_valid" = "0" ]
then
  gps_time="0"
  gps_lat="0"
  gps_lon="0"
else
  gps_time=$(echo $str | cut -f2 -d,)
  gps_lat=$(echo $str | cut -f3 -d,)
  gps_lat="${gps_lat}"$(echo $str | cut -f4 -d,)
  gps_lon=$(echo $str | cut -f5 -d,)
  gps_lon="${gps_lon}"$(echo $str | cut -f6 -d,)
fi

echo "$gps_lat,$gps_lon,$gps_time" > test.txt
