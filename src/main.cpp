#include <Arduino.h>
#include "sequencer.h"

Sequencer* sequencer = new Sequencer();

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  sequencer->tick();
}