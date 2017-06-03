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

			if (uurLocalDevice.isPowerOn()) {
				if (isDebugMode) {
					print("\nUURLocalDevice Class:");
					print("Local device is on");
					print("UUR Local Device name: " + uurLocalDevice.getFriendlyName());
					print("UUR Local Device Bluetooth Address: " + uurLocalDevice.getBluetoothAddress());
				}
			} else {
				if (isDebugMode) {
					print("Local device is off");
				}
				uurLocalDevice = null;
			}
		} catch (BluetoothStateException bse) {
			print("\nError attempting to get UUR Local Device name");
			print(bse.getMessage());
		}
		return uurLocalDevice;
	}



	/* ------------------------
			    Methods
	-------------------------- */ 

	private void print(String message) {
		System.out.println(message);
	}




}