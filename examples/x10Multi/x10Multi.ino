/*
  RFID-to-X10 reader
 
 Turns on and off AC appliances. Example was built using a PL513
 X10 One-Way Interface Module from http://www.smarthome.com 
 as the modem, and two Powerhouse X10 Lamp Module from Smarthome
 to plug the lamps in.
 
 Set module 1 to house code unit code 1, and module 2
 to house code unit code 2.
 
 created 17 June 2007
 modified 6 May 2011
 by Tom Igoe
 */

// include the X10 library files:
#include <x10.h>

const int rxPin = 3;    // data receive pin
const int txPin = 4;    // data transmit pin
const int zcPin = 2;    // zero crossing pin


void setup() {
  // begin serial:
  Serial.begin(9600);
  x10.begin(rxPin, txPin, zcPin);
  // Turn off all lights:
  x10.beginTransmission(A);
  x10.write(ALL_UNITS_OFF);
  x10.endTransmission();
}

void loop() {
  x10.beginTransmission(A);
  // Turn on first module:
  x10.write(UNIT_1);               
  x10.write(ON);  
  // Turn off second module:   
  x10.write(UNIT_2);            
  x10.write(OFF);
  delay(500);
  // Turn off first module: 
  x10.write(UNIT_1);
  x10.write(OFF);
  // turn on second module:
  x10.write(UNIT_2);              
  x10.write(ON);
  delay(500);
  x10.endTransmission();
}

