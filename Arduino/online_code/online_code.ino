
/* PoC#1: Week 3 milestone
  Send signals for different Samsung devices. 
*/
const int TVpin = 13;
char byteIn;

//const int power[] = {224, 224, 32, 223};
const int power[] = {224, 224, 64, 191};
const int psize[] = {224, 224, 124, 131};
const int stereoPwr[] = {194, 202, 128, 127};
const int stereoAux[] = {194, 202, 136, 119};


const int LEADER_PULSE=4400;
const int PERIOD=26;
const int WAIT_TIME=11;
const int PULSE_BIT=600;
const int PULSE_ONE=1600;
const int PULSE_ZERO=500;


void blastON(const int time, const int pin) {
 int scratch = time;
 while(scratch > PERIOD)
 {
   digitalWrite(pin, HIGH);
   delayMicroseconds(WAIT_TIME);
   digitalWrite(pin, LOW);
   delayMicroseconds(WAIT_TIME);
   scratch = scratch - PERIOD;
 }
}

void blastOFF(int time) {
 delayMicroseconds(time);
}

void blastByte(const int code, const int pin) {
 int i;
 for(i = 7; i > -1; i--)
 {
   
   if(1 << i & code) //check if the ith significant bit is 1
   {
     blastON(PULSE_BIT, pin);
     //Serial.print("1");
     blastOFF(PULSE_ONE);
   }
   else
   {
     blastON(PULSE_BIT, pin);
     //Serial.print("0");
     blastOFF(PULSE_ZERO);
   }
 }
 //Serial.print("\n");
}

void command(const int irCode[], const int pin)
{
 int i;
 blastON(LEADER_PULSE-200, pin);
 blastOFF(LEADER_PULSE);
 for(i = 0; i < 4; i++)
 {
   blastByte(irCode[i], pin);
 }
 blastON(PULSE_BIT,pin);
 //blastOFF(LEADER_PULSE);
 delay(47);
}

void setup() {
 Serial.begin(9600);
 Serial.print("Welcome to Arduino. Enjoy your stay.\n");
 Serial.print("Poor Man's Remote: Menu\n1) TV Power\n2) TV P. Size\n3) Sound Power\n4) Sound Aux\n");
 pinMode(TVpin, OUTPUT);
}

void loop() {
 while( Serial.available() > 0)
 {
   byteIn = Serial.read();
   switch(byteIn)
   {
     case '1':
       Serial.print("Sending TV Power...\n");
       for(int i = 0; i < 4; i++)
       {
         command(power, TVpin);
       }
       Serial.print("Sent.\n");
       break;
     case '2':
       Serial.print("Sending TV P. Size...\n");
        for(int i = 0; i < 4; i++)
       {
         command(psize, TVpin);
       }
       Serial.print("Sent.\n");
       break;
     case '3':
       Serial.print("Sending Stereo Power...\n");
       command(stereoPwr, TVpin);
       Serial.print("Sent.\n");
       break;
     case '4':
       Serial.print("Sending Stereo Aux...\n");
       command(stereoAux, TVpin);
       Serial.print("Sent.\n");
       break;
     default:
       Serial.print("Hey! Listen to directions, idiot.\n");
   }
     Serial.print("Poor Man's Remote: Menu\n1) TV Power\n2) TV P. Size\n3) Sound Power\n4) Sound Aux\n");
 }
}
   
