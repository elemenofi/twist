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
void Button::onPressWhileHolding () {
  Paginator * paginator = _controller->_sequencer->_paginator;

  // todo: implement copy and paste

  if (_state == HIGH && _shiftButton) {
    if (_controller->getShiftMode()) {
      paginator->previousPage();
      //Serial.println("Previous page: ");
      //Serial.println(paginator->getPage());
    }
  } else if (_state == HIGH && _reverseButton) {
    if (_controller->getShiftMode()) {
      paginator->nextPage();
      //Serial.println("Next page: ");
      //Serial.println(paginator->getPage());
    }
  }
}

void Button::onRelease () {
  if (timeSincePress() < _holdThreshold) {
    if (_shiftButton) {
      _controller->toggleMode();
    } else if (_reverseButton) {
      // todo: make reverse wait until current page is done
      _controller->_sequencer->reverse();
      _led->toggle();
    }else {
      _led->toggle();
      _controller->_sequencer->_stepsEdit[_id - 1]->toggle();
    }
  } 
};

void Button::onHold () {
  if (_id == 1) _controller->enterShiftMode();
  if (_id == 2 && _controller->getShiftMode()){
    _controller->enterCopyMode();
  } 
  else if (_id == 5) _controller->enterChanceMode();
  else if (_id == 6 && _controller->getChanceMode()) {
    _controller->enterSwingMode();
  }
}

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
    _controller->exitSwingMode();
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