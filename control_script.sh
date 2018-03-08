#!/bin/bash
for filename in odroid_packages/*.txt; do
#        ./MyProgram.exe "$filename" "Logs/$(basename "$filename" .txt)_Log$i.txt"
    ./scripts/bash_script.sh $filename
done
