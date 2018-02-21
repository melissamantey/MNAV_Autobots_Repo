#!/bin/bash
#python3 atest.py
#php -f load_db.php > mytest.txt
#value=`cat data.txt`
#echo "$value"
#value=`cat config.txt`
#echo "$value"
counter=0
latitude=0
longitude=0
time=0
while IFS='' read -r line || [[ -n "$line" ]]; do
    counter=0
    for datanugget in $(echo $line | sed "s/,/ /g")
    do
#        echo "$counter "
#        echo "$datanugget"
        if [ $counter -eq 0 ];
        then
            latitude=$datanugget
        elif [ $counter -eq 1 ];
        then
            longitude=$datanugget;
        else
            time=$datanugget;
        fi
        counter=$((counter+1))
    done
#    echo "passing to php file: $latitude $longitude $time"
    php -f update_registry.php $latitude $longitude $time > test_data.txt
done < "$1"
echo "Registry Updated."
