using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "xyz"; // Change to your UID

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletIndustrialDigitalOut4 ido4 =
		  new BrickletIndustrialDigitalOut4(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Turn pins alternating high/low for 10 times with 100 ms delay
		for(int i = 0; i < 10; i++)
		{
			System.Threading.Thread.Sleep(100);
			ido4.SetValue(1 << 0);
			System.Threading.Thread.Sleep(100);
			ido4.SetValue(1 << 1);
			System.Threading.Thread.Sleep(100);
			ido4.SetValue(1 << 2);
			System.Threading.Thread.Sleep(100);
			ido4.SetValue(1 << 3);
		}

		System.Console.WriteLine("Press key to exit");
		System.Console.ReadKey();
		ipcon.Disconnect();
	}
}
