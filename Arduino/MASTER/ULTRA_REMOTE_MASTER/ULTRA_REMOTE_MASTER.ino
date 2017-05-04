

/*
   Dan Fincher

*/

/* Info about IRremote:


   IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
   An IR LED must be connected to Arduino PWM pin 3.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/


#include <IRremote.h>
#include <SoftwareSerial.h>

// PINS
const int LEDPin = 8;
int LED = 13;
int RX = 10;
int TX = 11;

IRsend irsend;
SoftwareSerial mySerial(RX, TX); // (10, 11) The RX and TX on aruidno and HC - 08 are switched



// Data Variables

char userInput;
String device;


String recvDataString = "";
String recvTotalDataString = "";

int commandArrayLen = 0;

String numChunksString = "";
int numChunks = 0;
int numChunksCount = 0;

boolean debugMode = false;



void setup() {
  pinMode(LEDPin, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.print("Ultra Remote Initiated\n");
  
  Serial.print("Enter d for debug mode\n");
  Serial.print("Enter e to exit debug mode\n");
}

void loop() {

  if (Serial.available() > 0) {
    userInput = Serial.read();

    if (userInput == 'd') {
      debugMode = true;
      Serial.println("Debug mode initiated");
    } else if (userInput == 'e') {
      if (debugMode) {
        debugMode = false;
        Serial.println("Debug mode deinitiated");
      } else {
        Serial.println("Debug mode is not initiated");
      }
    }
  }




  
  if (mySerial.available()) {

    digitalWrite(LED, HIGH);

    char recvChar = mySerial.read();
    recvDataString.concat(recvChar);

    if (recvChar == '$') {
      
      // Remove delimiter
      recvDataString.remove(recvDataString.length()-2);
      
      if (recvDataString == "AppleTV") {
        commandArrayLen = 136;
      } else if (recvDataString == "DenTV") {
        
      }
      
      // Clear for next data
      recvDataString = "";

      if (debugMode) {
        Serial.println();
        Serial.println("Command length: ");
        Serial.print(commandArrayLen);
      }
    }

    

    if (recvChar == '/') {

      // Remove delimiter
      recvDataString.remove(recvDataString.length()-2);
      
      numChunksString = recvDataString;
      
      // Clear for next data
      recvDataString = "";

      numChunks = numChunksString.toInt();

      if (debugMode) {
        Serial.println();
        Serial.println("Number of expected chunks: ");
        Serial.print(numChunks);
      }
    }

    
    if (recvChar == '*') {

      lightOn();
      
      numChunksCount++;

      // Remove delimiter
      recvDataString.remove(recvDataString.length()-1);

      if (debugMode) {
        Serial.println();
        Serial.println("Received: ");
        Serial.print(recvDataString);
        Serial.print(" from iPhone");
      }
     
      // Send chunk ACK to iPhone 
      mySerial.write("Received Chunk");
      
      if (debugMode) {
        Serial.println();
        Serial.println("Sending chunk ACK to iPhone...");
      }

      recvTotalDataString.concat(recvDataString);

      // Clear for next data
      recvDataString = "";

      // Done receiving
      if (numChunksCount == numChunks) {
       
        if (debugMode) {
          Serial.println();
          Serial.println("Constructed string from chunks: ");
          Serial.print(recvTotalDataString);
        }

        
        recvTotalDataString += ' ';

        // Send total data ACK to iPhone
        mySerial.write("Received Data");
        
        if (debugMode) {
          Serial.println();
          Serial.println("Sending total data ACK to iPhone...");
        }

        
        int command[commandArrayLen];
  
        String num = "";
        int count = 0;
        for (int i = 0; i < recvTotalDataString.length(); i++) {
          
          if (recvTotalDataString.charAt(i) == ' ') {            
            command[count] = num.toInt();
            count++;
            num = "";
          } else {
            char letter = recvTotalDataString.charAt(i);
            num += letter;
          }
        }

        // Zero out for next time
        recvTotalDataString = "";
        numChunksCount = 0;
          
        // send parsed command

        for (int i = 0; i < commandArrayLen/2; i++) {
          command[commandArrayLen/2 + i] = command[i];
        }

        if (debugMode) {
          for (int i = 0; i < commandArrayLen; i++) {
            Serial.println();
            Serial.print("Sending: ");
            Serial.print(command[i]);
          }
        }


        sendCommand(command, sizeof(command) / sizeof(command[0]));
        
      }
    }
  }
}






/////////////////////////////
//      Custom Methods
/////////////////////////////

// Sends raw data command to device
void sendCommand(int rawData[], int len) {
  Serial.println();
  Serial.println("Sending");
  irsend.sendRaw(rawData, len, 38); // 38kHz
  Serial.println("Sent");
  delay(100);

  lightOff();
}



void lightOn() {
  digitalWrite(LED, HIGH);
}
void lightOff() {
  digitalWrite(LED, LOW);
}

