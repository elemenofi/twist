#include <Arduino.h>
#include "definitions.h"
#include "knob.h"
#include "controller.h"

Knob::Knob (uint8_t pin, int id, Controller* controller) {
  _pin = pin;
  _id = id;
  _controller = controller;
};

void Knob::onChange () {
  if (_controller->getMode() == VELOCITY) {
    Serial.println("Velocity");
    // m_sequence.m_steps[m_id]->controlVelocity(_value);
  } else if (_controller->getMode() == PITCH) {
    Serial.println("Pitch");
    // m_sequence.m_steps[m_id]->controlPitch(_value);
  } else if (_controller->getMode() == NOTELENGTH) {
    Serial.println("Note length");
    // m_sequence.m_steps[m_id]->controlLength(_value);
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
