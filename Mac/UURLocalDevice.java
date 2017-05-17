/*
@author Dan Fincher

 - JSR-82, the official Java Bluetooth API.




*/



import javax.bluetooth.*;



class UURLocalDevice {

	private boolean isDebugMode; 
	
	UURLocalDevice(boolean isDebugMode) {
		this.isDebugMode = isDebugMode;
	}

	LocalDevice getUURLocalDevice() {
		LocalDevice uurLocalDevice = null;
		try {
			uurLocalDevice = LocalDevice.getLocalDevice();

			if (isDebugMode) {
				print("\nUURLocalDevice Class:");
				print("UUR Local Device is " + uurLocalDevice.getFriendlyName());
			}
		} catch (BluetoothStateException bse) {
			System.out.println(bse.getMessage());
		}
		return uurLocalDevice;
	}



	// DiscoveryAgent getUURDiscoveryAgent(LocalDevice uurLocalDevice) {
	// 	return uurLocalDevice.getDiscoveryAgent();
	// }




	/* ------------------------
			    Methods
	-------------------------- */ 

	private static void print(String message) {
		System.out.println(message);
	}


}