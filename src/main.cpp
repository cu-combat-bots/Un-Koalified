#include <Arduino.h>

#include "Receiver.h"

Receiver r(0, 1, Serial1);

void setup() {
  // put your setup code here, to run once:
  r.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  r.loop();
  // print out the data
}