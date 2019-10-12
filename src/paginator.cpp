#include <Arduino.h>
#include "sequencer.h"
#include "paginator.h"
#include "step.h"
#include "controller.h"
#include "led.h"

Paginator::Paginator (Sequencer* sequencer) {
  _sequencer = sequencer;
  _currentPage = 0;
  Step * _pages[4][4] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
  };
};

int Paginator::getPage () {
  return _currentPage;
};

void Paginator::nextPage () {
  if (_currentPage < 3) {
    changePage(1);
    _currentPage++;
  }
};

void Paginator::previousPage () {
  if (_currentPage > 0) {
    changePage(-1);
    _currentPage--;
  };
};

void Paginator::changePage (int direction) {
  for (size_t i = 0; i < 4; i++) {
    // put current page steps in memory
    _pages[_currentPage][i] = _sequencer->_steps[i];
    Step * memoryStep = _pages[_currentPage][i];
    Serial.println(memoryStep->pitch); 

    // create new 4 steps or load them from memory
    if (_pages[_currentPage + direction][i] == 0) {
      _sequencer->_steps[i] = new Step(_sequencer);
    } else {
      _sequencer->_steps[i] = _pages[_currentPage + direction][i];
    }

    // toggle the leds for the loaded steps
    Step * newStep = _sequencer->_steps[i];
    Led * newStepLed = _sequencer->_controller->_leds[i];

    if (newStep->_state == 0) {
      newStepLed->off();
    } else {
      newStepLed->on();
    }
  }  
};
