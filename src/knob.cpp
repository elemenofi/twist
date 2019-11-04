#include <Arduino.h>
#include "definitions.h"
#include "knob.h"
#include "controller.h"
#include "step.h"
#include "sequencer.h"
#include "transport.h"
#include "piano.h"

Knob::Knob (uint8_t pin, int id, Controller* controller) {
  _pin = pin;
  _id = id;
  _controller = controller;
  _value = 0;
};

// when editing normally, the knob controls
// the step in the page. so for example, in the main
// pitch mode, knob 1 controls the pitch of step 1.
// when in motion mode, knob 1 controls pitch
// of the current step being played, and knob 2
// controls the velocity and knob 3 the length
// and 4 the chance
void Knob::onChange () {
  if (_controller->getMotionMode()) {
    // right now its only controlling the 4 steps you are editing
    // but i want to edit the steps edit and also the pages in memory
    // of the paginator, so that i can edit stuff that im not currently seeing
    if (_id == 0) {
      _controller->_sequencer->_stepsEdit[_controller->_sequencer->_currentStep]->controlPitch(_value);
    } else if (_id == 1) {
      _controller->_sequencer->_stepsEdit[_controller->_sequencer->_currentStep]->controlVelocity(_value);
    } else if (_id == 2) {
      _controller->_sequencer->_stepsEdit[_controller->_sequencer->_currentStep]->controlLength(_value);
    } else if (_id == 3) {
      _controller->_sequencer->_stepsEdit[_controller->_sequencer->_currentStep]->controlChance(_value);
    }
  } else {
    if (_id == 4) {
      _controller->_sequencer->_piano->transpose(_value);
    } else if (_id == 5) {
      _controller->_sequencer->_transport->controlTempo(_value);
    } else if (_controller->getMode() == VELOCITY) {
      _controller->_sequencer->_stepsEdit[_id]->controlVelocity(_value);
    } else if (_controller->getMode() == PITCH) {
    _controller->_sequencer->_stepsEdit[_id]->controlPitch(_value);
    } else if (_controller->getMode() == NOTELENGTH) {
      _controller->_sequencer->_stepsEdit[_id]->controlLength(_value);
    } else if (_controller->getMode() == CHANCE) {
      _controller->_sequencer->_stepsEdit[_id]->controlChance(_value);
    } else if (_controller->getMode() == SWING) {
      _controller->_sequencer->_stepsEdit[_id]->controlSwing(_value);
    }
  }
}

// todo latch
void Knob::tick () {
  _value = analogRead(_pin);

  int diff = abs(_value - _lastValue);

  // "filter"
  const boolean isChanging = _value != _lastValue && diff > 10;

  if (isChanging) {
    onChange();

    _lastValue = _value;
  }
};
