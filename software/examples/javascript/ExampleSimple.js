var IPConnection = require('Tinkerforge/IPConnection');
var BrickletIndustrialDigitalOut4 = require('Tinkerforge/BrickletIndustrialDigitalOut4');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'cmN';// Change to your UID

var ipcon = new IPConnection();// Create IP connection
var ido4 = new BrickletIndustrialDigitalOut4(UID, ipcon);// Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        if(error === IPConnection.ERROR_ALREADY_CONNECTED) {
            console.log('Error: Already connected');        
        }
    }
);// Connect to brickd

// Don't use device before ipcon is connected
ipcon.on(IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        //Turn on first two outputs and turn off last two outputs
        ido4.setValue(3);     
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data', function(data) {
	    ipcon.disconnect(
            function(error) {
                if(error === IPConnection.ERROR_NOT_CONNECTED) {
                    console.log('Error: Not connected');        
                }
            }
        );
process.exit(0);
});

