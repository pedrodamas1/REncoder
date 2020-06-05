
/*
	REncoder.h
	
	Library for interfacing with KY-040 rotary encoder.
	The library detects changes to the encoder, returns
	its value and allows to set a min/max range.

	The circuit:
	* KY-040 GND pin to ground
	* KY-040 + pin to 5V
	* KY-040 DT pin to digital pin 6
	* KY-040 DT pin to digital pin 7

	Created June 5, 2020
	By Pedro M. Damas
	Modified June 5, 2020
	By Pedro M. Damas

	Released into the public domain.

	https://github.com/pedrodamas1
*/


#include <Arduino.h>
#include "REncoder.h"


// Basic constructor for creating class instance.
REncoder::REncoder() 
{

}


// Constructor that creates instance and defines encoder pins.
REncoder::REncoder(uint8_t DT, uint8_t CLK) : dataPin(DT), clockPin(CLK)
{
	pinMode( dataPin, INPUT );
	pinMode( clockPin, INPUT );
}


// Destructor, to wrap up at the end.
REncoder::~REncoder()
{

}


// This method defines the encoder pins if they haven't 
// been defined before in the constructor.
void REncoder::setup(uint8_t DT, uint8_t CLK)
{
	dataPin = DT;
	clockPin = CLK;

	pinMode( dataPin, INPUT );
	pinMode( clockPin, INPUT );
}


// Main loop for the encoder
void REncoder::loop()
{

	if ( stateChanged_() ) {

		switch ( direction_() ) {

			case 0:
				// cw
				value++;
				break;
			case 1:
				// ccw
				value--;
				break;
		}

		normalize_();
	}
}


// Returns the current value
int REncoder::getValue()
{
	return value;
}


// Sets the value on the encoder
void REncoder::setValue(int value) 
{
	this -> value = value;
}


// Sets the min/max range for the values
void REncoder::setRange(int min, int max)
{
	this -> min = min;
	this -> max = max;
}


// Checks if the value has changed
bool REncoder::valueChanged()
{
	if ( value == previousValue ) {
		return false;
	}
	else {
		previousValue = value;
		return true;
	}
}


// This method check whether two arrays of length 4 are equal or not.
bool REncoder::equal_(bool A[4], bool B[4])
{
	for ( int i = 0; i < 4; i++ ) {
		if ( A[i] != B[i] ) {
			return false;
		}
	}
	return true;
}


// This method shifts the values in an array one place to the left,
// and then adds a new value to the right.
void REncoder::append_(bool A[4], bool value)
{
	for ( int i = 0; i < 3; i++ ) {
		A[i] = A[i+1];
	}
	A[3] = value;
}


// Check if the pin state has changed
bool REncoder::stateChanged_()
{
	bool readA = digitalRead(dataPin);
	bool readB = digitalRead(clockPin);

	if ( readA!=stateA[3] || readB!=stateB[3] ) {
		
		append_( stateA, readA );
		append_( stateB, readB );

		stateA[3] = readA;
		stateB[3] = readB;

		return true;
	}
	else {
		return false;
	}
}


char REncoder::direction_()
{
	if ( equal_(stateA, cwA) && equal_(stateB, cwB) ) {
		return 0;
	}
	else if ( equal_(stateA, ccwA) && equal_(stateB, ccwB) ) {
		return 1;	
	}
	else {
		return 2;
	}
}


//
void REncoder::normalize_()
{
	if (value < min) {
		value = min;
	}
	else if (value > max) {
		value = max;
	}
}