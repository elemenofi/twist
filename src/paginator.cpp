#include <Arduino.h>
#include "sequencer.h"
#include "paginator.h"
#include "step.h"
#include "controller.h"
#include "led.h"

Paginator::Paginator (Sequencer* sequencer) {
  _sequencer = sequencer;
  _currentPage = 1;
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
  if (_currentPage < 4) {
    savePage();
    loadPage(1);
    logPages();
    _currentPage++;
  }
};

void Paginator::previousPage () {
  if (_currentPage > 1) {
    savePage();
    loadPage(-1);
    logPages();
    _currentPage--;
  };
};

void Paginator::loadPage (int direction) {};

// copy the steps of the current sequence into
// the state of the paginator
void Paginator::savePage () {
  for (size_t i = 0; i < 4; i++) {
    _pages[_currentPage - 1][i] = _sequencer->_steps[i];
    Step * memoryStep = _pages[_currentPage - 1][i];
    Serial.println(memoryStep->pitch); 

    _sequencer->_steps[i] = new Step(_sequencer);
    Step * newStep = _sequencer->_steps[i];
    Serial.println(newStep->pitch);

    if (newStep->_state == 0) {
      Led * newStepLed = _sequencer->_controller->_leds[i];
      newStepLed->off();
    } 
  }  
};

void Paginator::logPages () {};