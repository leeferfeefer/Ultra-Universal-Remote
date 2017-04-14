/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println("The value is " );
       Serial.println( results.value);
    Serial.println(    "The hex value is ");

    Serial.println(results.value, HEX);
    Serial.println("The decode type is " );
        Serial.println( results.decode_type);
    Serial.println("The number of bits is ");
        Serial.println(results.bits);

    
    for(int i = 0; i < sizeof(results.rawbuf); i++)
{
  Serial.println(results.rawbuf[i]);
}
    
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
