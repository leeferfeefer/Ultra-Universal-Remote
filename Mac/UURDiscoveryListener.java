/*
@author Dan Fincher

 - JSR-82, the official Java Bluetooth API.




*/

import javax.bluetooth.*;
import java.util.Vector;



class UURDiscoveryListener implements DiscoveryListener {

	private boolean isDebugMode; 
	private Object lock;
	private String deviceURL;


	UURDiscoveryListener(Object lock, boolean isDebugMode) {
		this.lock = lock;
		this.isDebugMode = isDebugMode;
	}


	private static Vector deviceList = new Vector();
	
	public void deviceDiscovered(RemoteDevice device, DeviceClass cod) { 

		if (isDebugMode) {
			print("Device discovered: " + device.getBluetoothAddress());
		}

		if (!deviceList.contains(device)){ 
			deviceList.addElement(device); 
		} 
	} 

	public void servicesDiscovered(int transID, ServiceRecord[] servRecord) { 
		if (isDebugMode) {
			print("The transID is: " + transID);
			print("the servRecord is: " + servRecord);
		}
        for (int i = 0; i < servRecord.length; i++) {
	        deviceURL = servRecord[i].getConnectionURL(ServiceRecord.NOAUTHENTICATE_NOENCRYPT, false);
	        if (deviceURL != null) {
	            break; //take the first one
	        }
	    }
        if (isDebugMode) {
        	print("The device URL is: " + deviceURL);
        }
	} 

	public void serviceSearchCompleted(int transID, int respCode) { 

		if (isDebugMode) {
			if (transID != 0 && respCode != 0) {
				print("\n");
				print("Device services discovered");
				print("Trans ID is: " + transID);
				print("Resp Code is: " + respCode);
			}
		}

		synchronized(lock) { 
			lock.notify(); 
		} 
	} 


	public void inquiryCompleted(int discType) { 
		synchronized(lock) { 
			lock.notify(); 
		} 

		if (isDebugMode) {
			print("Inquiry Status: ");
			switch (discType) { 
				case DiscoveryListener.INQUIRY_COMPLETED: 
					print("INQUIRY_COMPLETED"); 
					break; 
				case DiscoveryListener.INQUIRY_TERMINATED: 
					print("INQUIRY_TERMINATED"); 
					break; 
				case DiscoveryListener.INQUIRY_ERROR: 
					print("INQUIRY_ERROR"); 
					break; 
				default: 
					print("Unknown Response Code"); 
					break; 
			}
		}
	}







	/* ------------------------
			    Methods
	-------------------------- */ 

	private void print(String message) {
		System.out.println(message);
	}
	
	Vector getDeviceList() {
		return deviceList;
	}

	String getDeviceURL() {
		return deviceURL;
	}
	
}