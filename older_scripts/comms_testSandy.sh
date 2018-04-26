#!/bin/bash

rm received.csv
./comm_server 5555

./compareString val.csv received.csv >> comparison_output.txt
 
