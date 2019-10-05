#include <Arduino.h>
#include "sequencer.h"

Sequencer* sequencer = new Sequencer();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  sequencer->tick();
}