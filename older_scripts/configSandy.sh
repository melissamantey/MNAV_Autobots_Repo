#!/bin/bash

ifconfig wlan0 down
iw dev wlan0 set type ibss
ifconfig wlan0 up

iw wlan0 ibss join odroid_test 2412

ip link set wlan0 up
ip addr add 192.168.1.4/24 broadcast 192.168.1.255 dev wlan0
ip route add default via 192.168.1.1

