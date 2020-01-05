#include <Arduino.h>
#include "definitions.h"
#include "knob.h"
#include "controller.h"
#include "step.h"
#include "sequencer.h"
#include "transport.h"
#include "paginator.h"
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
  if(_controller->getCCMode()) {
    int _channel = 9;
    int newValue = map(_value, 0, 1023,  127, 0);
    int _cc = _id + 1;

    usbMIDI.sendControlChange(_cc, newValue, _channel); // calculate CC for analog 1 and send
  }// !swing mode?
  if (_controller->getMotionMode() && !_controller->getSwingMode()) {
    Serial.println("motion");
    Paginator * paginator = _controller->_sequencer->_paginator;
    Sequencer * sequencer = _controller->_sequencer;

    // todo: there is a bug when you only have 1 page,
    // the sequencer crashes when you use motion record
    if (_id == 0) {
      sequencer->_stepsEdit[sequencer->_currentStep]->controlPitch(_value);
      paginator->_pages[paginator->_currentPlaybackPage][sequencer->_currentStep]->controlPitch(_value);
    } else if (_id == 1) {
      sequencer->_stepsEdit[sequencer->_currentStep]->controlVelocity(_value);
      paginator->_pages[paginator->_currentPlaybackPage][sequencer->_currentStep]->controlVelocity(_value);
    } else if (_id == 2) {
      sequencer->_stepsEdit[sequencer->_currentStep]->controlLength(_value);
      paginator->_pages[paginator->_currentPlaybackPage][sequencer->_currentStep]->controlLength(_value);
    } else if (_id == 3) {
      sequencer->_stepsEdit[_controller->_sequencer->_currentStep]->controlChance(_value);
      paginator->_pages[paginator->_currentPlaybackPage][sequencer->_currentStep]->controlChance(_value);
    } else if (_id == 4) {
      sequencer->_stepsEdit[_controller->_sequencer->_currentStep]->controlSwing(_value);
      paginator->_pages[paginator->_currentPlaybackPage][sequencer->_currentStep]->controlSwing(_value);
    }
  } else {
    if (_id == 4) {
      _controller->_sequencer->_piano->transpose(_value);
    } else if (_id == 5) {
      _controller->_sequencer->_transport->controlTempo(_value);
    } else if (_controller->getSwingMode()) {
      _controller->_sequencer->_stepsEdit[_id]->controlSwing(_value);
    } else if (_controller->getChanceMode()) {
      _controller->_sequencer->_stepsEdit[_id]->controlChance(_value);
    } else if (_controller->getMode() == VELOCITY && !_controller->getChanceMode() && !_controller->getSwingMode()) {
      _controller->_sequencer->_stepsEdit[_id]->controlVelocity(_value);
    } else if (_controller->getMode() == PITCH && !_controller->getChanceMode() && !_controller->getSwingMode()) {
    _controller->_sequencer->_stepsEdit[_id]->controlPitch(_value);
    } else if (_controller->getMode() == NOTELENGTH && !_controller->getChanceMode() && !_controller->getSwingMode()) {
      _controller->_sequencer->_stepsEdit[_id]->controlLength(_value);
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
