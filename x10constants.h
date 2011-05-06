/*
  x10.cpp - X10 transmission library for Arduino version 0.4
  
 Copyright (c) 2007 by Tom Igoe (tom.igoe@gmail.com)

This file is free software; you can redistribute it and/or modify
it under the terms of either the GNU General Public License version 2
or the GNU Lesser General Public License version 2.1, both as
published by the Free Software Foundation.

*/


#define HIGH 0x1
#define LOW  0x0
#define BIT_DELAY 1778    	// 1778 us between bit repeats in a half-cycle
#define BIT_LENGTH 800		// each bit is slightly less than 1ms long

#define	A	0b0110
#define	B	0b1110	
#define	C	0b0010
#define	D	0b1010
#define	E	0b0001
#define	F	0b1001
#define	G	0b0101
#define	H	0b1101
#define	I	0b0111
#define	J	0b1111
#define	K	0b0011
#define	L	0b1011
#define	M	0b0000
#define	N	0b1000
#define O	0b0100
#define P	0b1100

#define UNIT_1	0b01100
#define UNIT_2	0b11100
#define UNIT_3	0b00100
#define UNIT_4	0b10100
#define UNIT_5	0b00010
#define UNIT_6	0b10010
#define UNIT_7	0b01010
#define UNIT_8	0b11010
#define UNIT_9	0b01110
#define UNIT_10	0b11110
#define UNIT_11	0b00110
#define UNIT_12	0b10110
#define UNIT_13	0b00000
#define UNIT_14	0b10000
#define UNIT_15	0b01000
#define UNIT_16	0b11000

#define ALL_UNITS_OFF	0b00001
#define ALL_LIGHTS_ON	0b00011
#define ON				0b00101
#define OFF				0b00111
#define DIM				0b01001
#define BRIGHT			0b01011
#define ALL_LIGHTS_OFF	0b01101
#define EXTENDED_CODE	0b01111
#define HAIL_REQUEST	0b10001
#define HAIL_ACKNOWLEDGE	0b10011
#define PRE_SET_DIM			0b10101
#define EXTENDED_DATA		0b11001
#define STATUS_ON			0b11011
#define STATUS_OFF			0b11101
#define STATUS_REQUEST		0b11111
