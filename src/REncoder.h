
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


#ifndef REncoder_h
#define REncoder_h
#endif


class REncoder {

	// Pins on the encoder
	uint8_t dataPin, clockPin;

	int value = 0;
	int previousValue = 0;

	// These are the patterns that identify whether we're going CW or CCW
	const bool cwA[4] = {0,0,1,1};
	const bool cwB[4] = {1,0,0,1};
	const bool ccwA[4] = {1,0,0,1};
	const bool ccwB[4] = {0,0,1,1};

	bool stateA[4] = {0,0,0,0};
	bool stateB[4] = {0,0,0,0};

	int min = -32000;
	int max = +32000;
	bool looping = false;


public:
	
	// Overloaded constructor
	REncoder();
	REncoder(uint8_t DT, uint8_t CLK, bool looping = false);

	// Destructor
	~REncoder();

	// Useful public methods
	void setup(uint8_t DT, uint8_t CLK, bool looping = false);
	void loop();
	int getValue();
	void setValue(int value);
	void setRange(int min, int max);
	bool valueChanged();


private:

	bool equal_(bool A[4], bool B[4]);
	void append_(bool A[4], bool value);
	bool stateChanged_();
	char direction_();
	void normalize_();

};