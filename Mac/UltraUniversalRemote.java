/*
@author Dan Fincher

 - JSR-82, the official Java Bluetooth API.




*/

import javax.bluetooth.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.microedition.io.Connector;
import javax.microedition.io.StreamConnection;

class UltraUniversalRemote {


	private static Frame mainFrame;

	private static boolean isDebugMode;

	private static final String errorRunMsg = "\nTo run, type: \n"
		+ "java -cp bluecove.jar:. UltraUniversalRemote -d \n"
		+ "-d = debug mode (optional) \n";


	static {
		print("\nUltra Universal Remote Initiated");
		print(errorRunMsg);
	}
	







	public static void main(String[] args) {
		
		argsChecker(args);



		// loadGUI();


		

		UURLocalDevice uurLocalDevice = new UURLocalDevice(isDebugMode);
		LocalDevice localDevice = uurLocalDevice.getUURLocalDevice();
		if (localDevice != null) {
			
			UURDiscoveryAgent uurAgent = new UURDiscoveryAgent(isDebugMode, localDevice);
			uurAgent.discoverDevices();

			// thread wait

			RemoteDevice[] devices = uurAgent.getDevices();
			RemoteDevice arduino = null;

			for (int i = 0; i < devices.length; i++) {
				RemoteDevice device = devices[i];

				try {
					String deviceName = device.getFriendlyName(false);

					if (deviceName.equals("HC-06")) {
						print("Arduino found");
						arduino = device;
					}
			
				} catch (IOException e) {
					print("\nError attempting to get UUR Remote Device name");
					print(e.getMessage());
				} 
			}


			if (arduino != null) {
				// connect
		        UUID[] searchUUIDs = new UUID[]{new UUID(0x1105)};
		        int[] attributeIDs = new int[]{0x0100};

				uurAgent.discoverDeviceServices(attributeIDs, searchUUIDs, arduino);

				// thread wait

				connectAndSendData(arduino, uurAgent.getDeviceURL());
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


	private static void connectAndSendData(RemoteDevice device, String deviceURL) {
		try {

			StreamConnection streamConnection = (StreamConnection) Connector.open(deviceURL);
	        OutputStream os = streamConnection.openOutputStream();
	        InputStream is = streamConnection.openInputStream();

	        os.write("1".getBytes());


	        // os.write("HomeTV $".getBytes()); //just send '1' to the device
	        // os.write("1 /".getBytes());
	        // os.write("0x20DF10EF".getBytes());
	        // os.write("*".getBytes());

	        os.close();
	        is.close();
	        streamConnection.close();

	        if (isDebugMode) {
	        	print("Message sent");
	        }
		} catch (IOException e) {
			print("Could not connect and send data to device");
			print(e.getMessage());
		}
	}



	private static void loadGUI() {

		mainFrame = new Frame("Ultra Universal Remote");
		mainFrame.setSize(400, 200); // Width, Height
		// mainFrame.setLayout(new GridLayout(3, 1));
	    mainFrame.addWindowListener(new WindowAdapter() {
	        public void windowClosing(WindowEvent windowEvent) { // override
	        	System.exit(0);
	        }        
	    }); 


		Panel controlPanel = new Panel();
		controlPanel.setLayout(new GridLayout(1, 2));

		Panel leftPanel = new Panel();
		leftPanel.setLayout(new GridLayout(2, 1));

		Panel rightPanel = new Panel();


	    Label buttonLabel = new Label();
		buttonLabel.setAlignment(Label.CENTER);
        buttonLabel.setText("Click to search for devices.");

        Button refreshButton = new Button("Refresh");
		refreshButton.addActionListener(new ActionListener() {
		    public void actionPerformed(ActionEvent e) {
		    	print("button pressed");
		    }
	    });


		leftPanel.add(buttonLabel);
		leftPanel.add(refreshButton);

		controlPanel.add(leftPanel);
		controlPanel.add(rightPanel);

		mainFrame.add(controlPanel);
		mainFrame.setVisible(true);  



	}

}