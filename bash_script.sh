#!/bin/bash

gps_time=0
gps_lat=0
gps_lon=0

#str=$(head -20 /dev/ttyACM0 | grep GPGGA)
#
#gps_valid=$(echo $str | cut -f7 -d,)
#
#if [ "$gps_valid" = "0" ]
#then
#  gps_time="0"
#  gps_lat="0"
#  gps_lon="0"
#else
#  gps_time=$(echo $str | cut -f2 -d,)
#  gps_lat=$(echo $str | cut -f3 -d,)
#  gps_lat="${gps_lat}"$(echo $str | cut -f4 -d,)
#  gps_lon=$(echo $str | cut -f5 -d,)
#  gps_lon="${gps_lon}"$(echo $str | cut -f6 -d,)
#fi
#
#echo "$gps_lat,$gps_lon,$gps_time" > test.txt

counter=0
name=0
velocity=0
steering_angle=0
accel=0
time_stamp=0
error_message=0
while IFS='' read -r line || [[ -n "$line" ]]; do
    counter=0
    for datanugget in $(echo $line | sed "s/,/ /g")
    do
        if [ $counter -eq 0 ];
        then
            name=$datanugget;
            echo $name;
        elif [ $counter -eq 1 ];
        then
            velocity=$datanugget;
            echo $velocity;
        elif [ $counter -eq 2 ];
        then
            steering_angle=$datanugget;
            echo $steering_angle;
        elif [ $counter -eq 3 ];
        then
            accel=$datanugget;     
            echo $accel;
        else
            error_message=$datanugget;
            echo $error_message;
        fi
        counter=$((counter+1))
    done
    echo "passing to php file: $gps_lat $gps_lon $gps_time"
    php -f update_registry.php $name  $gps_lat $gps_lon $velocity $steering_angle $accel $gps_time > all_data.txt
done < "$1"
echo "Registry Updated."
