#include <Arduino.h>
#include "sequencer.h"
#include "paginator.h"
#include "step.h"
#include "controller.h"
#include "led.h"

Paginator::Paginator (Sequencer* sequencer) {
  _sequencer = sequencer;
  _currentEditPage = 0;
  _createdPages = 0;
  _currentPlaybackPage = 0;
};

int Paginator::getPage () {
  return _currentEditPage;
};

void Paginator::getNextPage () {
  if (_createdPages == 0) return;
  
  if (_currentPlaybackPage < _createdPages) {
    _currentPlaybackPage++;
  } else if (_currentPlaybackPage == _createdPages) {
    _currentPlaybackPage = 0;
  }

  Serial.println("Current playback page");
  Serial.println(_currentPlaybackPage);

  for (size_t i = 0; i < 4; i++) {
    _sequencer->_steps[i] = _pages[_currentPlaybackPage][i];
  }
};

void Paginator::nextPage () {
  if (_currentEditPage < 3) {
    changePage(1);
    _currentEditPage++;
  }

  debugPages();
};

void Paginator::previousPage () {
  if (_currentEditPage > 0) {
    changePage(-1);
    _currentEditPage--;
  };
};

void Paginator::changePage (int direction) {
  if (direction == 1 && _createdPages < 3) {
    _createdPages++;
  }

  for (size_t i = 0; i < 4; i++) {
    // put current page steps in memory
    _pages[_currentEditPage][i] = _sequencer->_steps[i];

    if (_pages[_currentEditPage + direction][i] == 0) {
      _sequencer->_steps[i] = new Step(_sequencer);
      _pages[_currentEditPage + direction][i] = _sequencer->_steps[i];
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

void Paginator::debugPages () {
  for (size_t i = 0; i < 4; i++) {
    for (size_t y = 0; y < 4; y++) {
      Step * step = _pages[i][y];
      Serial.println(step->pitch);
    }
  }
};
