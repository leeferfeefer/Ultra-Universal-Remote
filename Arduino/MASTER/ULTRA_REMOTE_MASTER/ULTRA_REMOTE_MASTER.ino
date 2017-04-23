

/*
 * Dan Fincher
 * 
 */

/* Info about IRremote:
 *  
 *  
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>


const int buttonPin = 7;
const int LEDPin = 8;

char userInput;

String device;

enum Command { UNDEF, RED, ORANGE, YELLOW, GREEN,  BLUE, PURPLE };




// DEN TV

unsigned int den_tv_volume_down[68] = {0xB3,0x58,0xC,0xA,0xC,0xA,0xC,0x21,0xB,0xB,0xB,0xB,0xC,0xA,0xC,0xA,0xC,0xA,0xC,0x21,0xB,0x21,0xC,0xA,0xC,0x21,0xB,0x21,0xC,0x20,0xC,0x21,0xB,0x21,0xC,0x20,0xC,0x21,0xC,0xA,0xC,0xA,0xC,0xA,0xC,0xA,0xC,0xB,0xB,0xB,0xB,0xB,0xC,0xA,0xC,0x20,0xC,0x21,0xC,0x20,0xC,0x21,0xB,0x21,0xC,0x20,0xC,};



// Apple TV
const unsigned int apple_play_pause[136] = {13232,9420,4540,640,520,640,1640,640,1640,640,1660,640,
500,620,1680,620,1660,620,1660,620,1660,620,1680,620,1660,620,540,600,540,620,540,620,540,600
,1680,620,1660,620,1660,620,1680,600,1680,620,1680,600,540,620,1660,620,540,620,520,620,1680,600,1680,620,540,620
,1660,620,540,620,1660,620,1680,620,34860,9340,4560,620,540,600,1680,600,1680,620,1680,600,540,620
,1660,620,1680,620,1660,620,1660,620,1680,600,1680,620,520,620,540,620,540,620,520,620,1680,600
,1680,620,540,600,1680,620,520,620,540,620,540,620,520,620,540,620,540,600,1680,620,1660,620
,540,620,1660,620,540,620,1660,620,1680,620};

// new code

const unsigned int apple_menu[68] = {0xB5,0x58,0xC,0xA,0xC,0x20,0xC,0x20,0xC,0x20,0xC,0xA,0xC,0x20,0xC,0x21,0xB,0x20,0xC,0x20,0xC,0x20,0xC,0x20,0xC,0xB,0xC,0xA,0xC,0xA,0xC,0xA,0xC,0x20,0xC,0x20,0xC,0x20,0xC,0xB,0xC,0xA,0xC,0xA,0xC,0xA,0xC,0xB,0xC,0xA,0xC,0xA,0xC,0x20,0xC,0x20,0xC,0xA,0xC,0x20,0xC,0xB,0xC,0x20,0xC,0x20,0xC,};


/* Codes:
 *  
 *  0x20DF10EF - ON/OFF
 *  
 */

IRsend irsend;

void setup() {
  
    pinMode(buttonPin, INPUT);
    pinMode(LEDPin, OUTPUT);


    Serial.begin(9600);
    Serial.print("Ultra Remote Initiated\n");
    Serial.print("Enter Command:");  // Format: Device Name / Command
}

void loop() {
  if (Serial.available() > 0) {
    
    userInput = Serial.read();
    
    switch(userInput) {
      case 'A':
        sendCommand(apple_play_pause, 136, 38);
        break;

      case 'D':

        for (int i = 0; i < 10; i++) {
           Serial.print("Sending");
           irsend.sendRaw(den_tv_volume_down, 68, 38);
           Serial.print("Sent");
           delay(100);     
        }
       
        break;
      default:
        Serial.print("Command unknown");
    }
  }
}




/////////////////////////////
//      Custom Methods
/////////////////////////////



// Sends raw data command to device
void sendCommand(int rawData[]) {
  
  Serial.print("Sending");
  irsend.sendRaw(rawData, sizeof(rawData) / sizeof(rawData[0]), 38); // 38kHz
  Serial.print("Sent");
  
  /*
  
  Serial.print("Sending");
  irsend.sendRaw(apple_menu,68,38);
  Serial.print("Sent");
  
  */
        
  delay(100);     
}


  
    /*
     *  FOR VIZIO
     
  
    int buttonState = digitalRead(buttonPin);
  
    if (buttonState == LOW) { // Pressed
  
      digitalWrite(LEDPin, HIGH);
  
  
    
      //for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0x20DF10EF, 32);
        //delay(100);
      //}
      //delay(5000); //5 second delay between each signal burst
    
      //delay(150);
    } else {
      digitalWrite(LEDPin, LOW);
    }
  
  
  */
  
  
    // FOR SANYO
  
    /*
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(, 32);
        delay(100);
      }
      delay(5000); //5 second delay between each signal burst
    
      //delay(150);

*/
  

