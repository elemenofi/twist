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
  _holdThreshold = 300;
  _led = led;
  _controller = controller;

  pinMode(pin, INPUT);
};

// this is actually on press while hold
// and maybe i dont need this function, there is
// also a redundancy with _state == HIGH 
// in the tick function, i have to take a look at refactoring this
// im handling only shift and reverse
void Button::onPressWhileHolding () {
  Paginator * paginator = _controller->_sequencer->_paginator;

  if (_state == HIGH && _shiftButton) {
    if (_controller->getShiftMode()) {
      paginator->previousPage();
    }
  } else if (_state == HIGH && _reverseButton) {
    if (_controller->getShiftMode()) {
      paginator->nextPage();
    }
  }
}

void Button::onRelease () {
  if (timeSincePress() < _holdThreshold) {
    if (_shiftButton && !_controller->getShiftMode()) {
      _controller->toggleMode();
    } else if (_reverseButton && !_controller->getShiftMode()) {
      // todo: make reverse wait until current page is done
      _controller->_sequencer->reverse();
      _led->toggle();
    } else if (!_reverseButton && !_shiftButton) {
      _led->toggle();
      _controller->_sequencer->_stepsEdit[_id - 1]->toggle();
    }
  } 
};

// there two ifs and then two else ifs and that is a bit strange
// i have to check if shift mode is true when holding _id 2 after
// changing it all to be ifs or a switch maybe is even better
// the problem is that copy mode is accessed through shift mode
// and swing mode is accessed through chance mode, which is also strange
void Button::onHold () {
  if (_id == 1) {
    _controller->enterShiftMode();
  } else if (_id == 2 && _controller->getShiftMode()) {
    _controller->enterCopyMode();
  } else if (_id == 3) {
    _controller->_sequencer->reset(); 
  } else if (_id == 5) {
    _controller->enterChanceMode();
  } else if (_id == 6 && _controller->getChanceMode()) {
    _controller->enterSwingMode();
  } else if (_id == 6 && !_controller->getSwingMode()) {
    _controller->enterMotionMode();
  }
}

// for key combinations like 1 + 2 for copy mode,
// its important that when you release 1 or 2 you check for
// both shift and copy. if user releases 1 but not 2 
// we still want to quit both modes, but if the user
// releases 2 but still holds 1, we want to stay in shift mode
// == behavior for chance mode and swing mode, maybe they
// could be refactored into 1
void Button::onHoldRelease () {
  if (_id == 1) {
    _controller->exitShiftMode();

    if (_controller->getCopyMode()) {
      _controller->exitCopyMode();
    }
  } else if (_id == 2) {
    _controller->exitCopyMode();
  } else if (_id == 5) {
    _controller->exitChanceMode();

    if (_controller->getSwingMode()) {
      _controller->exitSwingMode();
    }
  } else if (_id == 6) {
    _controller->exitMotionMode();
  }
};

void Button::tick () {
  _current = digitalRead(_pin);

  if (currentWentUp()) {
    _firstTime = millis();
  }

  if (currentIsUp() && timeSincePress() > _holdThreshold) {
    _firstHoldTime = millis();
    if (!_controller->getShiftMode()) {
      //Serial.println("shiftMode")
    };
    //Serial.println("onHold");
    onHold();
  }

  if (timeSincePress() > 10) {    
    if (_state != _current) {
      _state = _current;

      if (_state == HIGH) {
        //Serial.println("onPressWhileHolding");      
        onPressWhileHolding();
      } else {
        
        if (timeSincePress() >= _holdThreshold) {
          //Serial.println("onHoldRelease");
          onHoldRelease();
        } else {
          onRelease();
          //Serial.println("onRelease");
        }
      }
    }
  }

  _previous = _current;
};

bool Button::currentIsUp() {
  return _current == HIGH && _previous == HIGH;
};

bool Button::currentWentUp() {
  return _current == HIGH && _previous == LOW;
};

bool Button::currentWentDown () {
  return _current == LOW && _previous == HIGH;
};

bool Button::currentChanged () {
  return _current != _previous;
};

unsigned long Button::timeSincePress () {
  return (millis() - _firstTime);
};