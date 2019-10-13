#include <Arduino.h>
#include "step.h"

Step::Step(Sequencer* sequencer) {
  _state = false;
  _sequencer = sequencer;
  pitch = 38;
  velocity = 100;
  length = 4;
};

void Step::toggle () {
  _state = !_state;
};

void Step::controlLength (int value) {
  int newValue = map(value, 0, 1000, 16, 0); // <- hack i guess
  length = newValue;
};

void Step::controlPitch (int value) {
  int newValue = map(value, 0, 1023, 51, 36); // <- hack i guess
  pitch = newValue;
};

void Step::controlVelocity (int value) {
  int newValue = map(value, 0, 1023, 127, 62);
  velocity = newValue;
};
