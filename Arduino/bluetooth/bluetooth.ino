#include <SoftwareSerial.h>

int LED = 13;

int RX = 10;
int TX = 11;

char data = 0;
SoftwareSerial mySerial(RX,TX); // (10, 11)


void setup() {
 
  pinMode(LED, OUTPUT);  // Sets digital pin 13 as output for LED

  Serial.begin(9600);   // Sets baud for serial data transmission
  mySerial.begin(9600); // A different serial that allows for different pins assignment

  Serial.println("Ready!");
}

/*
 * Serial uses communication on pins Tx/Rx
 */
 
void loop() {

/*

  if (Serial.available()) {     // Send data only when you receive data
   
      data = Serial.read();         // Read the incoming data & store into data
      
      Serial.print(data);           // Print Value inside data in Serial monitor
      Serial.print("\n");  


      
      if (data == '1')              
         digitalWrite(13, HIGH);    
      else if (data == '0')          
         digitalWrite(13, LOW); 

   
   }
   */
     

   if (mySerial.available()) {    // Check if any bytes are available - received

      Serial.print("Data from iphone received");
      
      data = mySerial.read();  // my serial reads in data from port 
      Serial.println(data);  

      

      if (data == '1')              
         digitalWrite(LED, HIGH);    
      else if(data == '0')          
         digitalWrite(LED, LOW); 

       
   } 
}
