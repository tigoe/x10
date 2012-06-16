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

	Sends X10 commands.

*/

// ensure this library description is only included once
#ifndef x10_h
#define x10_h

// include types & constants of core API (for Arduino after 0022)
#include <Arduino.h>
#include "x10constants.h"

// library interface description
class x10Class : public Stream
{
  public:
    // constructors:
    x10Class();
 	void begin(int _rxPin=3,int _txPin=4, int _zcPin=2);


    void beginTransmission(uint8_t data);
    void beginTransmission(int data);
    void endTransmission(void);
   // uint8_t requestFrom(uint8_t, uint8_t);	
   // uint8_t requestFrom(int, int);
    virtual size_t write(uint8_t data);
    virtual size_t write(const char *data);
    virtual size_t write(const uint8_t *, size_t);
    
    // the following are not implemented yet:
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
	virtual void flush(void);
   // void onReceive( void (*)(int) );
   // void onRequest( void (*)(void) );

  private:
  	static uint8_t zeroCrossingPin;	// AC zero crossing pin
  	static uint8_t txPin;			// data out pin
  	static uint8_t rxPin;			// data in pin
  	static uint8_t houseCode;		// house code
  	static uint8_t transmitting;	// whether or not you're transmitting
 
  	// sends the individual bits of the commands:
    void sendBits(byte cmd, byte numBits, byte isStartCode);	// does bit shifting of a command
    void sendCommand(byte houseCode, byte numberCode);			// sends a command
    void waitForZeroCross(int pin, int howManyTimes);		    // checks for AC zero crossing
};

extern x10Class x10;

#endif

