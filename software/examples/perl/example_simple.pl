#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletIndustrialDigitalOut4;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Industrial Digital Out 4 Bricklet

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $ido4 = Tinkerforge::BrickletIndustrialDigitalOut4->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Turn pins alternating high/low 10 times with 100ms delay
for (my $i = 0; $i < 10; $i++)
{
    select(undef, undef, undef, 0.1);
    $ido4->set_value(1 << 0);
    select(undef, undef, undef, 0.1);
    $ido4->set_value(1 << 1);
    select(undef, undef, undef, 0.1);
    $ido4->set_value(1 << 2);
    select(undef, undef, undef, 0.1);
    $ido4->set_value(1 << 3);
}

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
