#include <Arduino.h>
#include "led.h"

Led::Led (int pin = 0, int state = LOW) {
  _pin = pin;
  _state = state;
  _blinkLength = 75;
  _blinking = false;
  _blinkingCounter = 0;

  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _state);
};

void Led::blink (int times) {
  digitalWrite(_pin, !digitalRead(_pin));
  _blinking = true;
  _blinkingCounter = times;
  _lastBlink = millis();  
};

void Led::toggle () {
  _state = !_state;

  digitalWrite(_pin, _state);

  if (_blinking) {
    digitalWrite(_pin, !_state);
  }
};

void Led::off () {
  _blinking = false;
  _state = 0;
  digitalWrite(_pin, _state);
}

void Led::on () {
  _blinking = false;
  _state = 1;
  digitalWrite(_pin, _state);
}

bool Led::blinkTimePassed () {
  return millis() - _lastBlink > _blinkLength;
};

void Led::tick () {
  // hack
  if (millis() < 3000) return; 

  if (_blinking && blinkTimePassed()) {
    digitalWrite(_pin, !digitalRead(_pin));
    _blinking = false;
    _lastBlink = millis();        
  }

  if (!_blinking && _blinkingCounter > 0 && blinkTimePassed()) {
    blink(_blinkingCounter - 1);
    _blinkingCounter--;
  }
};
