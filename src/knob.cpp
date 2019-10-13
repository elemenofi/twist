#include <Arduino.h>
#include "definitions.h"
#include "knob.h"
#include "controller.h"
#include "step.h"
#include "sequencer.h"
#include "transport.h"

Knob::Knob (uint8_t pin, int id, Controller* controller) {
  _pin = pin;
  _id = id;
  _controller = controller;
  _value = 0;
};

void Knob::onChange () {
  if (_id == 4) {
    //Serial.println("Knob number 5 still does not have a function");
  } else if (_id == 5) {
    _controller->_sequencer->_transport->controlTempo(_value);
  } else if (_controller->getMode() == VELOCITY) {
    _controller->_sequencer->_stepsEdit[_id]->controlVelocity(_value);
  } else if (_controller->getMode() == PITCH) {
   _controller->_sequencer->_stepsEdit[_id]->controlPitch(_value);
  } else if (_controller->getMode() == NOTELENGTH) {
    _controller->_sequencer->_stepsEdit[_id]->controlLength(_value);
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
