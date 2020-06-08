/*
 * Loop cycle time: 16 μs (microseconds)
 */

#include "src/REncoder.h"

REncoder myEncoder(6, 7, true);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myEncoder.setRange(0,10);
  myEncoder.setValue(7);
}

void loop() {

  // put your main code here, to run repeatedly:
  myEncoder.loop();

  if ( myEncoder.valueChanged() == true ) {
    //Serial.println( myEncoder.getValue() );
  }

}
