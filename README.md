# MNAV Autobots Repository
This is a repository for the code that updates the Registry used in the MNAV Project. 

# Files
1. gps_data.txt
2. gps_registry_script.sh
3. update_registry.php
4. test_data.txt

# The gps_data.txt File
This file is generated by a python script that pulls data from the gps. It is updated with lines of comma separated data. Each line contains: 
1. Latitude
2. Longitude
3. Time

# gps_registry_script
This file should be called like so: 
	./gps_registry_script.sh gps_data.txt
The file runs the gps python file that generates latitude, longitude, and time. It takes the data generated by the gps and stores in in the registry using the update_registry.php file.

 
