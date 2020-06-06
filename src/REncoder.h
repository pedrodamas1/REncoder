
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
	Modified June 6, 2020
	By Pedro M. Damas

	Released into the public domain.

	https://github.com/pedrodamas1
*/


// Include guard
#ifndef REncoder_h
#define REncoder_h


// Class definition
class REncoder {

	// Pins on the encoder
	uint8_t dataPin, clockPin;

	// Current and previous value on the encoder
	int value = 0;
	int previousValue = 0;

	// Sequence of states that indicate whether a step was taken and in which direction
	const bool cwA[4] = {0,0,1,1};
	const bool cwB[4] = {1,0,0,1};
	const bool ccwA[4] = {1,0,0,1};
	const bool ccwB[4] = {0,0,1,1};

	// Keeps a record of the last 4 states of the pins
	bool stateA[4] = {0,0,0,0};
	bool stateB[4] = {0,0,0,0};

	// Min and max values for the encoder
	int min = -32000;
	int max = +32000;

	// Logic variable for looping or not
	bool looping = false;


public:
	
	// Overloaded constructor
	REncoder();
	REncoder(uint8_t DT, uint8_t CLK, bool looping = false);

	// Destructor
	~REncoder();

	// Alternative to the constructor for setting up the pins.
	void setup(uint8_t DT, uint8_t CLK, bool looping = false);
	// Main loop for the encoder.
	void loop();
	// Returns the current value.
	int getValue();
	// Sets the value on the encoder.
	void setValue(int value);
	// Sets the min/max range for the values.
	void setRange(int min, int max);
	// Checks if the value has changed.
	bool valueChanged();


private:

	// Check whether two arrays of length 4 are equal or not.
	bool equal_(bool A[4], bool B[4]);
	// Shift values in array one place to the left and add a new value to the right.
	void append_(bool A[4], bool value);
	// Check if the pin state has changed.
	bool stateChanged_();
	// Check direction of rotation.
	char direction_();
	// Adjust "value" according to min/max and "looping".
	void normalize_();

};

#endif