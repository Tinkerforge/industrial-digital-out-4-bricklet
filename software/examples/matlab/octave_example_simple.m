function octave_example_simple
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "fJZ"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    ido4 = java_new("com.tinkerforge.BrickletIndustrialDigitalOut4", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don"t use device before ipcon is connected

    % Turn relays alternating on/off for 10 times with 100ms delay
    for i = 1:10
        pause(0.1);
        ido4.setValue(bitshift(1, 0));
        pause(0.1);
        ido4.setValue(bitshift(1, 1));
        pause(0.1);
        ido4.setValue(bitshift(1, 2));
        pause(0.1);
        ido4.setValue(bitshift(1, 3));
    end
    
    input("\nPress any key to exit...\n", "s");
    ipcon.disconnect();
end
