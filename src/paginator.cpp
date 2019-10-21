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

void Paginator::getNextPage (int direction) {
  if (_createdPages == 0) return;

  if (_currentPlaybackPage < _createdPages && direction == 1) {
    _currentPlaybackPage++;
  } else if (_currentPlaybackPage > 0 && direction == -1) {
    _currentPlaybackPage--;
  } else if (_currentPlaybackPage == 0 && direction == -1) {
    _currentPlaybackPage = _createdPages;
  } else if (_currentPlaybackPage == _createdPages) {
    _currentPlaybackPage = 0;
  }

  Serial.println("Current playback page");
  Serial.println(_currentPlaybackPage);

  for (size_t i = 0; i < 4; i++) {
    _sequencer->_stepsPlayback[i] = _pages[_currentPlaybackPage][i];
  }
};

void Paginator::nextPage () {
  if (_currentEditPage < 3) {
    changePage(1);
    _currentEditPage++;
    _sequencer->_controller->_leds[_currentEditPage]->blink(3);
  }

  debugPages();
};

void Paginator::previousPage () {
  if (_currentEditPage > 0) {
    changePage(-1);
    _currentEditPage--;
    _sequencer->_controller->_leds[_currentEditPage]->blink(3);
  };

  debugPages();
};

void Paginator::changePage (int direction) {
  if (direction == 1 && _createdPages < 3 && _currentEditPage == _createdPages) {
    _createdPages++;
    // //Serial.println("Incrementing created pages to:");
    // //Serial.println(_createdPages);
  }


  // there is a bug when i go backwards from the last page
  for (size_t i = 0; i < 4; i++) {
    // put current page steps in memory
    _pages[_currentEditPage][i] = _sequencer->_stepsEdit[i];

    // if there is not a defined step for the page then create steps
      // if 1+2 is being hold then copy the current ones instead of creating new
    // if there are steps put them into the stepsEdit of the sequencer
    if (_pages[_currentEditPage + direction][i] == 0) {
      _sequencer->_stepsEdit[i] = new Step(_sequencer);
      _pages[_currentEditPage + direction][i] = _sequencer->_stepsEdit[i];
    } else {
      _sequencer->_stepsEdit[i] = _pages[_currentEditPage + direction][i];
    }
    
    setLeds(i);
  }  
};

void Paginator::setLeds (size_t i) {
  // toggle the leds for the loaded steps
  Step * newStep = _sequencer->_stepsEdit[i];
  Led * newStepLed = _sequencer->_controller->_leds[i];

  if (newStep->_state == 0) {
    newStepLed->off();
  } else {
    newStepLed->on();
  }
};

void Paginator::debugPages () {
  for (size_t i = 0; i < 4; i++) {
    for (size_t y = 0; y < 4; y++) {
      Step * step = _pages[i][y];
      Serial.println(step->_state);
    }
  }
};
