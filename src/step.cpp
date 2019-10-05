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
  int newValue = map(value, 0, 1023, 24, 1);
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
