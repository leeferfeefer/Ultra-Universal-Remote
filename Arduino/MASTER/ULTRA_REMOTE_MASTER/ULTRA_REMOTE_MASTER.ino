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

IRsend irsend;

// PINS
const int LEDPin = 8;
int LED = 13;

// iPhone Connectivity 
int iPhoneRX = 10;
int iPhoneTX = 11;
SoftwareSerial iPhoneSerial(iPhoneRX, iPhoneTX); // (10, 11) The RX and TX on aruidno and HC - 08 are switched

// mac Connectivity
int macRX = 6;
int macTX = 5;
SoftwareSerial macSerial(macRx, macTX);




//Den TV Codes
const long tv_pow = 0x20DF10EF;
const long tv_input = 0x20DFF40B;
const long tv_vol_up = 0x20DF40BF;
const long tv_vol_down = 0x20DFC03F;

//Apple TV Codes

// Home TV Codes
const long home_vol_up = 0xE0E0E01F;





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

int counter = 0;


void setup() {
  pinMode(LEDPin, OUTPUT);

  Serial.begin(9600);
  iPhoneSerial.begin(9600);
  macSerial.begin(9600);

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
    } else if (userInput == 't') {
      // Test

      sendHEXCommand(home_vol_up);
      
    }
  } 



  // Received data available
  if (iPhoneSerial.available()) {

    lightOn();

    char recvChar = mySerial.read();
    recvDataString.concat(recvChar);

    // Device
    if (recvChar == '$') {
      
      // Remove delimiter
      recvDataString.remove(recvDataString.length()-2);
      
      if (recvDataString == "AppleTV") {
        device = recvDataString;
        commandArrayLen = 136;
      } else if (recvDataString == "DenTV") {
        device = recvDataString;
        commandArrayLen = 72;
      } else if (recvDataString == "HomeTV") {
        device = recvDataString;
        
      }
      
      // Clear for next data
      recvDataString = "";
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

        // Send total data ACK to iPhone
        mySerial.write("Received Data");
        
        if (debugMode) {
          Serial.println();
          Serial.println("Sending total data ACK to iPhone...");
        }

        if (device == "AppleTV") {

          recvTotalDataString += ' ';

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
            
          // send parsed command
          if (device == "AppleTV") {
            for (int i = 0; i < commandArrayLen/2; i++) {
              command[commandArrayLen/2 + i] = command[i];
            }
          }
      
          if (debugMode) {
            for (int i = 0; i < commandArrayLen; i++) {
              Serial.println();
              Serial.print("Sending: ");
              Serial.print(command[i]);
            }
          }
  
          sendRawCommand(command, sizeof(command) / sizeof(command[0]));
          
        } else if (device == "DenTV") {

          Serial.print("Received: ");
          Serial.print(recvTotalDataString);


          switch(recvTotalDataString.charAt(0)) {
            case 'i':
              sendHEXCommand(tv_input);
              break;
            case 'u':
              sendHEXCommand(tv_vol_up);
              break;
            case 'd':
              sendHEXCommand(tv_vol_down);
              break;
            case 'p':
              sendHEXCommand(tv_pow);
              break;
            default:          
              break;
              
          }
        } else if (device == "HomeTV") {

            char command[20];
            recvTotalDataString.toCharArray(command, 20);
            
            const char* string = command;
            long unsigned commandHex = strtoul(string, 0, 16);
            
            sendHEXCommand(commandHex);
        }
        
          // Zero out for next time
          recvTotalDataString = "";
          numChunksCount = 0;
        
      }
    }
  }



  if (macSerial.available()) {
    Serial.println("Data received from mac");
  }


  
}






/////////////////////////////
//      Custom Methods
/////////////////////////////

// Sends raw data command to device
void sendRawCommand(int rawData[], int len) {
  Serial.println();
  Serial.println("Sending");
  irsend.sendRaw(rawData, len, 38); // 38kHz
  Serial.println("Sent");
  delay(100);

  mySerial.write("Sent");
  lightOff();
}
void sendHEXCommand(long command) {
    Serial.println();
    Serial.println("Sending");
    irsend.sendNEC(command, 32); // 38kHz
    Serial.println("Sent");
    delay(100);
    
    mySerial.write("Sent");
    lightOff();
}



void lightOn() {
  digitalWrite(LED, HIGH);
}
void lightOff() {
  digitalWrite(LED, LOW);
}

