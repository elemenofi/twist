#include <Arduino.h>
#include "step.h"

Step::Step(Sequencer* sequencer) {
  _state = false;
  _sequencer = sequencer;
  pitch = 38;
  velocity = 100;
  length = 1;
};

void Step::toggle () {
  _state = !_state;
};

void Step::controlLength (int value) {
  // String controlLog = "Control length raw value: ";
  // Serial.println(controlLog + value);
  int newValue = map(value, 0, 1000, 4, 0); // <- hack i guess
  // String controlLog2 = "Control length: ";
  // Serial.println(controlLog2 + newValue);
  length = newValue;
};

void Step::controlPitch (int value) {
  int newValue = map(value, 0, 1023, 51, 38);
  pitch = newValue;
};

void Step::controlVelocity (int value) {
  int newValue = map(value, 0, 1023, 127, 63);
  velocity = newValue;
};
