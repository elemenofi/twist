#include <Arduino.h>
#include "sequencer.h"

// cf5b2c0a7d3ab0ee0162b40c2856b1fc17f00658

Sequencer* sequencer = new Sequencer();

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  sequencer->tick();
}