<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletIndustrialDigitalOut4.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletIndustrialDigitalOut4;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Industrial Digital Out 4 Bricklet

$ipcon = new IPConnection(); // Create IP connection
$ido4 = new BrickletIndustrialDigitalOut4(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Turn pins alternating high/low 10 times with 100ms delay
for($i = 0; $i < 10; $i++) {
    usleep(100*1000);
    $ido4->setValue(1 << 0);
    usleep(100*1000);
    $ido4->setValue(1 << 1);
    usleep(100*1000);
    $ido4->setValue(1 << 2);
    usleep(100*1000);
    $ido4->setValue(1 << 3);
}

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
