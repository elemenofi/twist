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

void Step::reset () {
  _state = false;
  pitchScale = 0;
  pitchGrade = 0;
  velocity = 100;
  length = 4;
  chance = 100;
  swing = 0;
}

void Step::setStep (Step* step) {
  _state = step->_state;
};

void Step::toggle () {
  _state = !_state;
};

void Step::controlLength (int value) {
  int newValue = map(value, 0, 1000, 16, 0); // <- hack i guess
  length = newValue;
  Serial.println("length");
  Serial.println(length);
};

void Step::controlPitch (int value) {
  int newValue = map(value, 0, 1023, 6, -2);
  pitchGrade = newValue;
  Serial.println("pitchGrade");
  Serial.println(pitchGrade);
};

void Step::controlVelocity (int value) {
  int newValue = map(value, 0, 1023, 127, 0);
  velocity = newValue;
  Serial.println("velocity");
  Serial.println(velocity);
};

void Step::controlChance (int value) {
  int newValue = map(value, 0, 1023, 100, 0);
  chance = newValue;
  Serial.println("chance");
  Serial.println(chance);
};

void Step::controlSwing (int value) {
  int newValue = map(value, 0, 1023,  4, -4);
  swing = newValue;
  Serial.println("swing");
  Serial.println(swing);
};
