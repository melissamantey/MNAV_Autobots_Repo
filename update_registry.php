<?php

#   var_dump($argc);
#	var_dump($argv);

    $name = 'self';
    $lat = $argv[1];
    $long = $argv[2];
    $vel = 200;
    $angle = 0;
    $accel = 123;
    $time = $argv[3];

#    echo "Latitude is: $lat!\n";
#    echo "Longitude is: $long!\n";

    //Connect to database
    $db = mysqli_connect("localhost","root","password","MNAV_Registry");  
                
    if($db === false) {
        //Print an error if the database can't be reached
        echo "Cannot connect to the database!\n";
    }else {
        $sql = "INSERT INTO `Registry` (`user_id`,`latitude`,`longitude`,`velocity`,`steering_angle`,`acceleration`,`time_stamp`,`error_message`) values
            ('self','$lat','$long','$vel','$angle','$accel','$time',0);";
        if ($db->query($sql) === TRUE) {
            echo "Record updated successfully!\n";
        } else {
            echo "Error updating record: " . $db->error;
        }
    }
    
?>



    
