#include <Arduino.h>
#include "sequencer.h"

Sequencer* sequencer = new Sequencer();

void setup() {
  Serial.begin(9600);
}

void loop() {
  sequencer->tick();
}