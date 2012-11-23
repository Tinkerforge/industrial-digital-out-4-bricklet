using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "xyz"; // Change to your UID

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(HOST, PORT); // Create connection to brickd
		BrickletIndustrialDigitalOut4 ido4 = new BrickletIndustrialDigitalOut4(UID); // Create device object
		ipcon.AddDevice(ido4); // Add device to IP connection
		// Don't use device before it is added to a connection

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
		ipcon.Destroy();
	}
}
