#include <Arduino.h>
#include "step.h"
#include "sequencer.h"
#include "piano.h"

Step::Step(Sequencer* sequencer) {
  _state = false;
  _sequencer = sequencer;
  pitchScale = 0;
  pitchGrade = 0;
  velocity = 100;
  length = 4;
  chance = 100;
  swing = 0;
};

void Step::toggle () {
  _state = !_state;
};

void Step::controlLength (int value) {
  int newValue = map(value, 0, 1000, 16, 0); // <- hack i guess
  length = newValue;
};

void Step::controlPitch (int value) {
  int newValue = value;

  if (value < 330) {
    newValue = 2;
  } else if (value < 660) {
    newValue = 1;
  } else if (value <= 1023) {
    newValue = 0;
  }

  pitchGrade = newValue;
};

void Step::controlVelocity (int value) {
  int newValue = map(value, 0, 1023, 127, 62);
  velocity = newValue;
};

void Step::controlChance (int value) {
  int newValue = map(value, 0, 1023, 100, 0);
  chance = newValue;
  Serial.println(chance);
};
