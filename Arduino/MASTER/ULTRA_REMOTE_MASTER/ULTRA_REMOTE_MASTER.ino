

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


const int LEDPin = 8;

char userInput;

String device;



String recvDataString = "";
String recvTotalDataString = "";

int commandArrayLen = 0;

String iterationsString = "";
int iterationsNum = 0;
int iterationsCount = 0;

////////////////////////
//    Device Codes
////////////////////////

/*
  // Apple TV
  const unsigned int apple_play_pause[136] = {
  13232, 9420,
  4540, 640,
  520, 640,
  1640, 640,
  1640, 640,
  1660, 640,
  500, 620,
  1680, 620,
  1660, 620,
  1660, 620,
  1660, 620,
  1680, 620,
  1660, 620,
  540, 600,
  540, 620,
  540, 620,
  540, 600,
  1680, 620,
  1660, 620,
  1660, 620,
  1680, 600,
  1680, 620,
  1680, 600,
  540, 620,
  1660, 620,
  540, 620,
  520, 620,
  1680, 600,
  1680, 620,
  540, 620,
  1660, 620,
  540, 620,
  1660, 620,
  1680, 620,
  34860, 9340,
  4560, 620,
  540, 600,
  1680, 600,
  1680, 620,
  1680, 600,
  540, 620,
  1660, 620,
  1680, 620,
  1660, 620,
  1660, 620,
  1680, 600,
  1680, 620,
  520, 620,
  540, 620,
  540, 620,
  520, 620,
  1680, 600,
  1680, 620,
  540, 600,
  1680, 620,
  520, 620,
  540, 620,
  540, 620,
  520, 620,
  540, 620,
  540, 600,
  1680,620,
  1660, 620,
  540, 620,
  1660, 620,
  540, 620,
  1660, 620,
  1680, 620
                                           };



  const unsigned int apple_menu[136] = {
  11372, 9420,
  4520, 640,
  520, 640,
  1640, 620,
  1660, 620,
  1680, 600,
  540, 620,
  1660, 620,
  1680, 620,
  1660, 620,
  1660, 620,
  1680, 600,
  1680, 620,
  520, 620,
  540, 620,
  540, 620,
  520, 620,
  1680, 600,
  1680, 620,
  1660, 620,
  540, 620,
  520, 640,
  520, 640,
  500, 660,
  500, 640,
  520, 600,
  540, 620,
  1680, 640,
  1640, 640,
  520, 640,
  1640, 640,
  500, 660,
  1640, 640,
  1660, 640,
  11372, 9420,
  4520, 640,
  520, 640,
  1640, 620,
  1660, 620,
  1680, 600,
  540, 620,
  1660, 620,
  1680, 620,
  1660, 620,
  1660, 620,
  1680, 600,
  1680, 620,
  520, 620,
  540, 620,
  540, 620,
  520, 620,
  1680, 600,
  1680, 620,
  1660, 620,
  540, 620,
  520, 640,
  520, 640,
  500, 660,
  500, 640,
  520, 600,
  540, 620,
  1680, 640,
  1640, 640,
  520, 640,
  1640, 640,
  500, 660,
  1640, 640,
  1660, 640};


  const unsigned int apple_select[136] = {24532, 9420,
  4540, 640,
  500, 640,
  1660, 620,
  1660, 640,
  1640, 640,
  500, 660,
  1640, 640,
  1640, 640,
  1640, 640,
  1640, 640,
  1660, 640,
  1640, 640,
  520, 600,
  540, 620,
  540, 600,
  540, 620,
  1680, 600,
  540, 620,
  540, 620,
  1660, 620,
  1660, 620,
  1680, 600,
  540, 620,
  1680, 600,
  540, 620,
  520, 620,
  1680, 620,
  1660, 620,
  540, 600,
  1680, 620,
  540, 600,
  1680, 620,
  1680, 620,
  37160, 9360,
  4520, 660,
  500, 640,
  1640, 640,
  1660, 620,
  1660, 640,
  520, 620,
  1660, 640,
  1640, 640,
  1640, 640,
  1660, 620,
  1660, 640,
  1640, 640,
  500, 660,
  500, 640,
  520, 640,
  500, 660,
  1640, 640,
  1640, 640,
  520, 640,
  1640, 640,
  500, 640,
  520, 640,
  500, 660,
  500, 640,
  520, 640,
  500, 640,
  1660, 640,
  1640, 640,
  500, 640,
  1640, 660,
  500, 640,
  1640, 660,
  1660, 620
                                       };

  const unsigned int apple_up[136] = {
  12828, 9420,
  4540, 640,
  500, 640,
  1660, 640,
  1640, 640,
  1640, 640,
  520, 640,
  1640, 640,
  1640, 640,
  1660, 640,
  1640, 640,
  1640, 640,
  1640, 660,
  500, 640,
  520, 620,
  520, 640,
  520, 640,
  1640, 640,
  500, 660,
  1640, 640,
  500, 660,
  1640, 640,
  500, 640,
  520, 640,
  520, 640,
  500, 640,
  520, 640,
  1640, 640,
  1640, 640,
  520, 640,
  1640, 640,
  520, 640,
  1640, 640,
  1660, 640,
  12828, 9420,
  4540, 640,
  500, 640,
  1660, 640,
  1640, 640,
  1640, 640,
  520, 640,
  1640, 640,
  1640, 640,
  1660, 640,
  1640, 640,
  1640, 640,
  1640, 660,
  500, 640,
  520, 620,
  520, 640,
  520, 640,
  1640, 640,
  500, 660,
  1640, 640,
  500, 660,
  1640, 640,
  500, 640,
  520, 640,
  520, 640,
  500, 640,
  520, 640,
  1640, 640,
  1640, 640,
  520, 640,
  1640, 640,
  520, 640,
  1640, 640,
  1660, 640};

  const unsigned int apple_down[136] = {
  12252, 9420,
  4520, 640,
  520, 640,
  1640, 640,
  1640, 640,
  1660, 620,
  520, 620,
  1680, 620,
  1660, 620,
  1660, 620,
  1660, 620,
  1680, 600,
  1680, 600,
  560, 600,
  540, 620,
  520, 620,
  540, 620,
  1660, 620,
  540, 620,
  540, 600,
  1680, 620,
  1660, 620,
  540, 620,
  520, 620,
  540, 620,
  540, 600,
  540, 620,
  1680, 600,
  1680, 600,
  540, 620,
  1680, 600,
  540, 620,
  1660, 620,
  1700, 600,
  12252, 9420,
  4520, 640,
  520, 640,
  1640, 640,
  1640, 640,
  1660, 620,
  520, 620,
  1680, 620,
  1660, 620,
  1660, 620,
  1660, 620,
  1680, 600,
  1680, 600,
  560, 600,
  540, 620,
  520, 620,
  540, 620,
  1660, 620,
  540, 620,
  540, 600,
  1680, 620,
  1660, 620,
  540, 620,
  520, 620,
  540, 620,
  540, 600,
  540, 620,
  1680, 600,
  1680, 600,
  540, 620,
  1680, 600,
  540, 620,
  1660, 620,
  1700, 600};

  const unsigned int apple_left[136] = {
  14104, 9420,
  4520, 660,
  500, 640,
  1640, 640,
  1660, 600,
  1680, 620,
  540, 600,
  1680, 620,
  1660, 620,
  1660, 620,
  1680, 600,
  1680, 620,
  1660, 620,
  540, 620,
  520, 620,
  540, 620,
  540, 620,
  1660, 620,
  1660, 620,
  540, 600,
  540, 620,
  1680, 600,
  540, 620,
  540, 620,
  520, 620,
  540, 620,
  540, 620,
  1660, 620,
  1660, 620,
  540, 600,
  1680, 620,
  540, 600,
  1680, 620,
  1680, 620,
  50100, 9340,
  4560, 620,
  540, 600,
  1680, 600,
  1680, 620,
  1660, 620,
  540, 600,
  1680, 620,
  1660, 620,
  1680, 600,
  1680, 620,
  1660, 620,
  1660, 620,
  540, 620,
  540, 600,
  540, 620,
  540, 600,
  1680, 620,
  1660, 620,
  540, 620,
  520, 620,
  1680, 600,
  540, 620,
  540, 620,
  540, 600,
  540, 620,
  520, 620,
  1680, 620,
  1660, 620,
  540, 600,
  1680, 620,
  540, 600,
  1680, 600,
  1700, 620};

  const unsigned int apple_right[136] = {
  30696, 9300,
  4620, 560,
  580, 560,
  1700, 600,
  1680, 600,
  1720, 540,
  600, 540,
  1720, 580,
  1740, 540,
  1740, 580,
  1680, 580,
  1740, 540,
  1740, 560,
  600, 560,
  580, 540,
  640, 520,
  600, 580,
  1720, 540,
  600, 560,
  1740, 540,
  1740, 540,
  600, 580,
  560, 560,
  620, 540,
  600, 540,
  620, 540,
  600, 580,
  1700, 580,
  1720, 560,
  580, 580,
  1720, 560,
  580, 540,
  1740, 560,
  1760, 540,
  30696, 9300,
  4620, 560,
  580, 560,
  1700, 600,
  1680, 600,
  1720, 540,
  600, 540,
  1720, 580,
  1740, 540,
  1740, 580,
  1680, 580,
  1740, 540,
  1740, 560,
  600, 560,
  580, 540,
  640, 520,
  600, 580,
  1720, 540,
  600, 560,
  1740, 540,
  1740, 540,
  600, 580,
  560, 560,
  620, 540,
  600, 540,
  620, 540,
  600, 580,
  1700, 580,
  1720, 560,
  580, 580,
  1720, 560,
  580, 540,
  1740, 560,
  1760, 540};

*/


int LED = 13;

int RX = 10;
int TX = 11;


IRsend irsend;
SoftwareSerial mySerial(RX, TX); // (10, 11) The RX and TX on aruidno and HC - 08 are switched

void setup() {


  pinMode(LEDPin, OUTPUT);


  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.print("Ultra Remote Initiated\n");
}

void loop() {


  /*
    if (Serial.available() > 0) {

      userInput = Serial.read();

      switch (userInput) {

        case 'A':
          sendCommand(apple_play_pause, sizeof(apple_play_pause) / sizeof(apple_play_pause[0]));
          break;

        case 'B':
          sendCommand(apple_menu, sizeof(apple_menu) / sizeof(apple_menu[0]));
          break;

        case 'C':
          sendCommand(apple_select, sizeof(apple_select) / sizeof(apple_select[0]));
          break;

        case 'D':
          sendCommand(apple_up, sizeof(apple_up) / sizeof(apple_up[0]));
          break;

        case 'E':
          sendCommand(apple_down, sizeof(apple_down) / sizeof(apple_down[0]));
          break;

        case 'F':
          sendCommand(apple_left, sizeof(apple_left) / sizeof(apple_left[0]));
          break;

        case 'G':
          sendCommand(apple_right, sizeof(apple_right) / sizeof(apple_right[0]));
          break;


        default:
          Serial.print("Command unknown");
      }
    }

  */


  if (mySerial.available()) {

    char recvChar = mySerial.read();
    recvDataString.concat(recvChar);

    if (recvChar == '$') {
      recvDataString.remove(recvDataString.length()-2);
      
      if (recvDataString == "AppleTV") {
        commandArrayLen = 136;
      } else if (recvDataString == "DenTV") {
        
      }
      
      recvDataString = "";

      Serial.println(commandArrayLen);
    }

    

    if (recvChar == '/') {
      
      recvDataString.remove(recvDataString.length()-2);
      
      iterationsString = recvDataString;
      recvDataString = "";

      iterationsNum = iterationsString.toInt();

      Serial.println(iterationsString);
    }

    
    if (recvChar == '*') {
      
      iterationsCount++;
      
      recvDataString.remove(recvDataString.length()-1);
      
      Serial.print("Received: ");
      Serial.println(recvDataString);

      mySerial.write("Received Chunk");

      recvTotalDataString.concat(recvDataString);
      recvDataString = "";

      // Done receiving
      if (iterationsCount == iterationsNum) {
        
        //Serial.println(recvTotalDataString);

        recvTotalDataString += ' ';

        mySerial.write("Received Data");

        int command[commandArrayLen];
  
        String num = "";
        int count = 0;
        for (int i = 0; i < recvTotalDataString.length(); i++) {
          
          if (recvTotalDataString.charAt(i) == ' ') {
            
            int commandInt = num.toInt();
            Serial.println(commandInt);
            
            command[count] = commandInt;
            count++;
            num = "";
          } else {
            char letter = recvTotalDataString.charAt(i);
            num += letter;
          }
        }

        recvTotalDataString = "";

          
//        // send parsed command
//        for (int i = 0; i < commandArrayLen; i++) {
//          Serial.println(command[i]);
//        }
      }

    }
    

    //    digitalWrite(LED, HIGH);

  } else {
    //digitalWrite(LED, LOW);

  }





}






/////////////////////////////
//      Custom Methods
/////////////////////////////

// Sends raw data command to device
void sendCommand(int rawData[], int len) {
  Serial.print("Sending");
  irsend.sendRaw(rawData, len, 38); // 38kHz
  Serial.print("Sent");
  delay(100);
}



