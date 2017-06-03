/*
@author Dan Fincher

 - JSR-82, the official Java Bluetooth API.




*/

import javax.bluetooth.*;


class UltraUniversalRemote {


	private static boolean isDebugMode;

	private static final String errorRunMsg = "\nTo run, type: \n"
		+ "java -cp bluecove.jar:. UltraUniversalRemote.java -d \n"
		+ "-d = debug mode (optional) \n";


	static {
		print("\nUltra Universal Remote Initiated");
		print(errorRunMsg);
	}
	







	public static void main(String[] args) {
		
		argsChecker(args);



		loadGUI();



		UURLocalDevice uurLocalDevice = new UURLocalDevice(isDebugMode);
		LocalDevice localDevice = uurLocalDevice.getUURLocalDevice();
		if (localDevice != null) {
			
			UURDiscoveryAgent uurAgent = new UURDiscoveryAgent(isDebugMode, localDevice);
			uurAgent.discoverDevices();

			RemoteDevice[] devices = uurAgent.getDevices();
			RemoteDevice arduino;

			if (isDebugMode) {
				print("\nUltra Universal Remote: ");
				for (int i = 0; i < devices.length; i++) {
					RemoteDevice device = devices[i];

					try {
						String deviceName = device.getFriendlyName(false);

						print("The device name is: " + deviceName);

						if (deviceName.equals("HC-06")) {
							print("Arduino found");
						}

						
					} catch (Exception e) {
						print("\nError attempting to get UUR Remote Device name");
						print(e.getMessage());
					} 
					
				}
			}
		}
	}

















	/* ------------------------
			    Methods
	-------------------------- */ 

	private static void print(String message) {
		System.out.println(message);
	}
	private static void argsChecker(String[] args) {
		int argsLength = args.length;
		if (argsLength == 1) {
			debugMode();
		}
	}
	private static void debugMode() {
		print("\nDebug Mode Initiated\n");
		isDebugMode = true;
	}



	private static void loadGUI() {
		
	}

}