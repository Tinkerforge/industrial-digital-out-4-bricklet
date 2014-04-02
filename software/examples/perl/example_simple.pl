#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletIndustrialDigitalOut4;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'cmN'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $ido4 = Tinkerforge::BrickletIndustrialDigitalOut4->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Turn relays alternating on/off for 10 times with 1s delay
foreach(1 .. 10)
{
	sleep(1);
    $ido4->set_value(1 << 0);
    sleep(1);
    $ido4->set_value(1 << 1);
    sleep(1);
    $ido4->set_value(1 << 2);
    sleep(1);
    $ido4->set_value(1 << 3);
}

print "Press any key to exit...\n";
<STDIN>;
$ipcon->disconnect();
