function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Industrial Digital Out 4 Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    ido4 = javaObject("com.tinkerforge.BrickletIndustrialDigitalOut4", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Turn pins alternating high/low 10 times with 100ms delay
    for i = 0:9
        pause(0.1);
        ido4.setValue(bitshift(1, 0));
        pause(0.1);
        ido4.setValue(bitshift(1, 1));
        pause(0.1);
        ido4.setValue(bitshift(1, 2));
        pause(0.1);
        ido4.setValue(bitshift(1, 3));
    end

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
