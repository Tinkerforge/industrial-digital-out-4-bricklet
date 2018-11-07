use std::{error::Error, io, thread, time::Duration};
use tinkerforge::{industrial_digital_out_4_bricklet::*, ip_connection::IpConnection};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Industrial Digital Out 4 Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let ido4 = IndustrialDigitalOut4Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    // Set pins alternating high/low 10 times with 100ms delay
    for i in 0..10 {
        thread::sleep(Duration::from_millis(100));
        ido4.set_value(1 << 0);
        thread::sleep(Duration::from_millis(100));
        ido4.set_value(1 << 1);
        thread::sleep(Duration::from_millis(100));
        ido4.set_value(1 << 2);
        thread::sleep(Duration::from_millis(100));
        ido4.set_value(1 << 3);
    }

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
