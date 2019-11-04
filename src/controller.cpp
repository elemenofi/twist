#include <Arduino.h>
#include "controller.h"
#include "led.h"
#include "button.h"
#include "knob.h"
#include "definitions.h"
#include "sequencer.h"
#include "paginator.h"

Controller::Controller (Sequencer* sequencer) {
  _sequencer = sequencer;
  _modeBeforeChance = PITCH;
  _modeBeforeMotion = PITCH;
  _currentMode = PITCH;
  _shiftMode = false;
  _copyMode = false;
  
  _leds[0] = new Led(3, LOW);
  _leds[1] = new Led(5, LOW);
  _leds[2] = new Led(7, LOW);
  _leds[3] = new Led(9, LOW);
  _leds[4] = new Led(11, LOW);
  _leds[5] = new Led(24, LOW);

  _leds[4]->toggle();
  _leds[5]->toggle();

  _buttons[0] = new Button(1, step1pin, _leds[0], false, false, this);
  _buttons[1] = new Button(2, step2pin, _leds[1], false, false, this);
  _buttons[2] = new Button(3, step3pin, _leds[2], false, false, this);
  _buttons[3] = new Button(4, step4pin, _leds[3], false, false, this);
  _buttons[4] = new Button(5, shiftPin, _leds[4], true, false, this);
  _buttons[5] = new Button(6, playPin, _leds[5], false, true, this);

  _knobs[0] = new Knob(A0, 0, this);
  _knobs[1] = new Knob(A1, 1, this);
  _knobs[2] = new Knob(A2, 2, this);
  _knobs[3] = new Knob(A3, 3, this);
  _knobs[4] = new Knob(A4, 4, this);
  _knobs[5] = new Knob(A5, 5, this);
};

void Controller::tick() {
  for (size_t i = 0; i < 6; i++) {
    _buttons[i]->tick();
    _leds[i]->tick();
    _knobs[i]->tick();
  }
}

void Controller::toggleMode () {
  if (_currentMode == PITCH) {
    _currentMode = VELOCITY;
    Serial.println("VELOCITY");
    _leds[4]->blink(999);
  } else if (_currentMode == VELOCITY) {
    _currentMode = NOTELENGTH;
    Serial.println("NOTELENGTH");
    _leds[4]->blink();
    _leds[4]->off();
  } else if (_currentMode == NOTELENGTH) {
    _currentMode = PITCH;
    Serial.println("PITCH");
    _leds[4]->blink(); // shut the 999 blinks off
    _leds[4]->on();
  }
};

void Controller::enterShiftMode () {
  // todo: maybe shift mode should be a mode like the others duh
  _shiftMode = true;

  for (int i = 0; i < 4; i++) {
    if (_sequencer->_paginator->_currentEditPage != i) _leds[i]->off();
  }

  _leds[_sequencer->_paginator->_currentEditPage]->on();
};

void Controller::exitShiftMode () {
  _shiftMode = false;

  for (size_t i = 0; i < 4; i++) {
    _leds[i]->off();
    _sequencer->_paginator->setLeds(i);
  }
};

void Controller::enterCopyMode () {
  _copyMode = true;
}

void Controller::exitCopyMode () {
  _copyMode = false;
}

void Controller::enterChanceMode () {
  // this if is so that it happens only the first
  // clock cycle in which the user enters the chance mode
  // so it checks that the chance mode is not already true
  if (_currentMode != CHANCE && _currentMode != SWING) {
    _modeBeforeChance = _currentMode;
    Serial.println("CHANCE");
    _currentMode = CHANCE;
  }
};

void Controller::exitChanceMode () {
  _currentMode = _modeBeforeChance;
  if (_currentMode == PITCH) {
    Serial.println("PITCH");
  } else if (_currentMode == VELOCITY) {
    Serial.println("VELOCITY");
  }
};

void Controller::enterSwingMode () {
  if (_currentMode != SWING) {
    Serial.println("SWING");
  }

  _currentMode = SWING;
};

void Controller::exitSwingMode () {
  _currentMode = _modeBeforeChance;
  if (_currentMode == PITCH) {
    Serial.println("PITCH");
  } else if (_currentMode == VELOCITY) {
    Serial.println("VELOCITY");
  }
};

void Controller::enterMotionMode () {
  if (_currentMode != MOTION) {
    _modeBeforeMotion = _currentMode;
    Serial.println("MOTION");
    _currentMode = MOTION;
  }
};

void Controller::exitMotionMode () {
  _currentMode = _modeBeforeMotion;
  if (_currentMode == PITCH) {
    Serial.println("PITCH");
  } else if (_currentMode == VELOCITY) {
    Serial.println("VELOCITY");
  }
};

bool Controller::getChanceMode () {
  return _currentMode == CHANCE;
};

bool Controller::getSwingMode () {
  return _currentMode == SWING;
}

bool Controller::getMotionMode () {
  return _currentMode == MOTION;
}

bool Controller::getCopyMode () {
  return _copyMode;
}

bool Controller::getShiftMode () {
  return _shiftMode;
};

Modes Controller::getMode() {
  return _currentMode;
};

