#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_industrial_digital_out_4'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Industrial Digital Out 4 Bricklet

ipcon = IPConnection.new # Create IP connection
ido4 = BrickletIndustrialDigitalOut4.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Turn pins alternating high/low 10 times with 100ms delay
for _ in 0..9
  sleep 0.1
  ido4.set_value 1 << 0
  sleep 0.1
  ido4.set_value 1 << 1
  sleep 0.1
  ido4.set_value 1 << 2
  sleep 0.1
  ido4.set_value 1 << 3
end

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
