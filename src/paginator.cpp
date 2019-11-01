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

void Paginator::getNextPlaybackPage (int direction) {
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
    // this is a nasty flag i should get rid of
    _createdPages++;
    // //Serial.println("Incrementing created pages to:");
    // //Serial.println(_createdPages);
  }

  for (size_t i = 0; i < 4; i++) {
    // put current page steps in memory
    _pages[_currentEditPage][i] = _sequencer->_stepsEdit[i];

    // if there is not a defined step for the page then create steps
    // if there are steps put them into the stepsEdit of the sequencer
    if (_pages[_currentEditPage + direction][i] == 0) {
      Step * step = new Step(_sequencer);

      if (_sequencer->_controller->getCopyMode()) {
        step->pitchScale = _sequencer->_stepsEdit[i]->pitchScale;
        step->pitchGrade = _sequencer->_stepsEdit[i]->pitchGrade;
        step->velocity = _sequencer->_stepsEdit[i]->velocity;
        step->length = _sequencer->_stepsEdit[i]->length;
        step->_state = _sequencer->_stepsEdit[i]->_state;
        step->chance = _sequencer->_stepsEdit[i]->chance;
        step->swing = _sequencer->_stepsEdit[i]->swing;
      }

      _sequencer->_stepsEdit[i] = step;
      _pages[_currentEditPage + direction][i] = step;
    } else {
      Step * step = new Step(_sequencer);
      // 
      if (_sequencer->_controller->getCopyMode()) {
        step->pitchScale = _sequencer->_stepsEdit[i]->pitchScale;
        step->pitchGrade = _sequencer->_stepsEdit[i]->pitchGrade;
        step->velocity = _sequencer->_stepsEdit[i]->velocity;
        step->length = _sequencer->_stepsEdit[i]->length;
        step->_state = _sequencer->_stepsEdit[i]->_state;
        step->chance = _sequencer->_stepsEdit[i]->chance;
        step->swing = _sequencer->_stepsEdit[i]->swing;
      } else {
        step->pitchScale = _pages[_currentEditPage + direction][i]->pitchScale;
        step->pitchGrade = _pages[_currentEditPage + direction][i]->pitchGrade;
        step->velocity = _pages[_currentEditPage + direction][i]->velocity;
        step->length = _pages[_currentEditPage + direction][i]->length;
        step->_state = _pages[_currentEditPage + direction][i]->_state;
        step->chance = _pages[_currentEditPage + direction][i]->chance;
        step->swing = _pages[_currentEditPage + direction][i]->swing;
      }

      _sequencer->_stepsEdit[i] = step;
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
