#include <Arduino.h>
#include "button.h"
#include "led.h"
#include "controller.h"
#include "sequencer.h"
#include "paginator.h"
#include "step.h"

Button::Button (
  int id,
  const int pin,
  Led* led,
  bool shiftButton,
  bool reverseButton,
  Controller* controller
) {
  _id = id;
  _pin = pin;
  _shiftButton = shiftButton;
  _reverseButton = reverseButton;
  _holdThreshold = 1000;
  _led = led;
  _controller = controller;

  pinMode(pin, INPUT);
};

void Button::onPress () {
  // Serial.println(_id);
  // Serial.println(_controller.getShiftMode());
  // Serial.println("currentPage");
  // Serial.println(_controller._paginator->getPage());
  Paginator * paginator = _controller->_sequencer->_paginator;

  if (_state == HIGH && _shiftButton) {
    if (_controller->getShiftMode()) {
      paginator->previousPage();
      Serial.println(paginator->getPage());
    } else {
      _controller->toggleMode();
    }
  } else if (_state == HIGH && _reverseButton) {
    if (_controller->getShiftMode()) {
      paginator->nextPage();
      Serial.println(paginator->getPage());
    } else {
      _controller->_sequencer->reverse();
      _led->toggle();
    }
  } else if (_state == HIGH) {
    _led->toggle();
    _controller->_sequencer->_steps[_id - 1]->toggle();
  } 
}

bool Button::currentIsUp() {
  return _current == HIGH && _previous == HIGH;
};

bool Button::currentWentUp() {
  return _current == HIGH && _previous == LOW;
};

bool Button::currentWentDown () {
  return _current == LOW && _previous == HIGH;
}

bool Button::currentChanged () {
  return _current != _previous;
}

unsigned long Button::timeSincePress () {
  return (millis() - _firstTime);
}

void Button::tick () {
  _current = digitalRead(_pin);

  if (currentWentUp()) {
    _firstTime = millis();
  }

  if (currentIsUp() && timeSincePress() > _holdThreshold) {
    _firstHoldTime = millis();
    if (!_controller->getShiftMode()) Serial.println("onHold");
    _controller->enterShiftMode();
  }

  if (timeSincePress() > 10) {    
    if (_state != _current) {
      _state = _current;

      if (_state == HIGH) {
        Serial.println("onPress");      
        onPress();
      } else {
        
        if (timeSincePress() >= _holdThreshold) {
          Serial.println("onHoldRelease");
          _controller->exitShiftMode();
        } else {
          Serial.println("onRelease");
        }
      }
    }
  }

  _previous = _current;
};