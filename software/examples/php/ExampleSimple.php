<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletIndustrialDigitalOut4.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletIndustrialDigitalOut4;

$host = 'localhost';
$port = 4223;
$uid = 'xyz'; // Change to your UID

$ipcon = new IPConnection($host, $port); // Create IP connection to brickd
$ido4 = new BrickletIndustrialDigitalOut4($uid); // Create device object

$ipcon->addDevice($ido4); // Add device to IP connection
// Don't use device before it is added to a connection

// Turn pins alternating high/low for 10 times with 100 ms delay
for($i = 0; $i < 10; $i++)
{
    usleep(1000*100);
    $ido4->setValue(1 << 0);
    usleep(1000*100);
    $ido4->setValue(1 << 1);
    usleep(1000*100);
    $ido4->setValue(1 << 2);
    usleep(1000*100);
    $ido4->setValue(1 << 3);
}

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->destroy();

?>
