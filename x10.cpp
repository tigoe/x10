/*
  x10.cpp - X10 transmission library for Arduino version 0.4
  
 Copyright (c) 2007 by Tom Igoe (tom.igoe@gmail.com)

This file is free software; you can redistribute it and/or modify
it under the terms of either the GNU General Public License version 2
or the GNU Lesser General Public License version 2.1, both as
published by the Free Software Foundation.

  
  Original library								(0.1) 
  Timing bug fixes								(0.2)
  #include bug fixes for 0012					(0.3)
  Refactored version following Wire lib API		(0.4)
    
  Zero crossing algorithms borrowed from David Mellis' shiftOut command
  for Arduino.
  
  The circuits can be found at 
 
http://www.arduino.cc/en/Tutorial/x10
 
 
 */

#include <Arduino.h>
#include "x10.h"
#include "x10constants.h"

uint8_t x10Class::zeroCrossingPin = 2;	// AC zero crossing pin
uint8_t x10Class::rxPin = 3;			// data in pin
uint8_t x10Class::txPin = 4;			// data out pin

uint8_t x10Class::houseCode = 0;		// house code
uint8_t x10Class::transmitting = 0;		// whether you're transmitting or not


/*
 Constructor.
 
 Sets the pins and sets their I/O modes.
 
 */
 
x10Class::x10Class() {}


void x10Class::begin(int _rxPin, int _txPin, int _zcPin)
{
  // initialize pin numbers:
  txPin = _txPin;        		
  rxPin = _rxPin;        	
  zeroCrossingPin = _zcPin;			
  houseCode = 0;				  
  transmitting = 0;			

  // Set I/O modes:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode (zeroCrossingPin, INPUT);
}

void x10Class::beginTransmission(uint8_t data)
{
	houseCode = data;
	transmitting = 1;
}

void x10Class::beginTransmission(int data)
{
	 beginTransmission((uint8_t)data);

}

void x10Class::endTransmission(void)
{
   // indicate that we are done transmitting
  transmitting = 0;
}

    
size_t x10Class::write(uint8_t data)
{
	if (transmitting) {
		sendCommand(houseCode, data);
	}
}
size_t x10Class::write(const char * data)
{
 write((uint8_t*)data, strlen(data));
}

size_t x10Class::write(const uint8_t *data, size_t quantity)
{
    for(size_t i = 0; i < quantity; ++i){
      write(data[i]);
    }
}

/*
	methods inherited from Stream but not implemented yet.
*/

int x10Class::available(void)
{
}

int x10Class::read(void)
{
}

int x10Class::peek(void)
{
}

void x10Class::flush(void)
{
}

/*
	Writes an X10 command out to the X10 modem
*/
void x10Class::sendCommand(byte houseCode, byte numberCode) {
 
   byte startCode = 0b1110; 		// every X10 command starts with this
   
	// send the three parts of the command:
	sendBits(startCode, 4, true);	
	sendBits(houseCode, 4, false);
	sendBits(numberCode, 5, false);

  	// if this isn't a bright or dim command, it should be followed by
  	// a delay of 3 power cycles (or 6 zero crossings):
  	if ((numberCode != BRIGHT) && (numberCode != DIM)) {
  		waitForZeroCross(zeroCrossingPin, 6);
   	}
}


/*
	Writes a sequence of bits out.  If the sequence is not a start code,
	it repeats the bits, inverting them.
*/

void x10Class::sendBits(byte cmd, byte numBits, byte isStartCode) {
  	byte thisBit;	// byte for shifting bits
  
	// iterate the number of bits to be shifted:
	for(int i=1; i<=numBits; i++) {
		// wait for a zero crossing change
		waitForZeroCross(zeroCrossingPin, 1);
		// shift off the last bit of the command:
		thisBit = cmd & (1 << (numBits - i));
		
		// repeat once for each phase:
		for (int phase = 0; phase < 3; phase++) {
			// set the data Pin:
			digitalWrite(txPin, thisBit);
			delayMicroseconds(BIT_LENGTH);
			// clear the data pin:
			digitalWrite(txPin, LOW);
			delayMicroseconds(BIT_DELAY);
		}
		
		// if this command is a start code, don't
		// send its complement.  Otherwise do:
		if(!isStartCode) {
			// wait for zero crossing:
			waitForZeroCross(zeroCrossingPin, 1);
			for (int phase = 0; phase < 3; phase++) {
				// set the data pin:
				digitalWrite(txPin, !thisBit);
				delayMicroseconds(BIT_LENGTH);
				// clear the data pin:
				digitalWrite(txPin, LOW);
				delayMicroseconds(BIT_DELAY);
			}
		}
	}
}

/*
	TO DO: receiveBits and receiveCommand to parallel the above
*/

/*
  waits for a the zero crossing pin to cross zero

*/
void x10Class::waitForZeroCross(int pin, int howManyTimes) {
	unsigned long cycleTime = 0;
	
  	// cache the port and bit of the pin in order to speed up the
  	// pulse width measuring loop and achieve finer resolution.  calling
  	// digitalRead() instead yields much coarser resolution.
  	uint8_t bit = digitalPinToBitMask(pin);
  	uint8_t port = digitalPinToPort(pin);

  	for (int i = 0; i < howManyTimes; i++) {
		// wait for pin to change:
    	if((*portInputRegister(port) & bit))
    	 	while((*portInputRegister(port) & bit)) 
        		cycleTime++;
    	else
      		while(!(*portInputRegister(port) & bit)) 
        		cycleTime++;
  		}
}

// pre-instantiate class:
x10Class x10 = x10Class();