/*
  X10 blink
 
 Blinks an lamp on an X10 lamp module.  
 Example was built using a PL513
 X10 One-Way Interface Module from http://www.smarthome.com 
 as the modem, and a Powerhouse X10 Lamp Module from Smarthome
 to plug the lamp in.
 
 created 15 June 2007
 modified 6 May 2011
 by Tom Igoe
 
 */
#include <x10.h>

const int rxPin = 3;    // data receive pin
const int txPin = 4;    // data transmit pin
const int zcPin = 2;    // zero crossing pin


void setup() {
  // initialize serial and X10:
  Serial.begin(9600);
  x10.begin(rxPin, txPin, zcPin);
}

void loop() {
  // open transmission to house code A:
  x10.beginTransmission(A);
  Serial.println("Lights on:");
  // send a "lights on" command:
  x10.write(ON);

  delay(500);
  Serial.println("Lights off:");
  // send a "lights off" command:
  x10.write(OFF);
  x10.endTransmission();
  delay(500);
}


