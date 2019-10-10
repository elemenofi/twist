#include <Arduino.h>
#include "sequencer.h"
#include "paginator.h"
#include "step.h"

Paginator::Paginator (Sequencer* sequencer) {
  _sequencer = sequencer;
  _currentPage = 1;
  int _pages[4][4][4];
  //  int _pages[4][4][4] = {
  //   {
  //     {38, 100, 1, 0},
  //     {38, 100, 1, 0},
  //     {38, 100, 1, 0},
  //     {38, 100, 1, 0}
  //   },
  //   {
  //     {40, 100, 1, 0},
  //     {40, 100, 1, 0},
  //     {40, 100, 1, 0},
  //     {40, 100, 1, 0}
  //   },
  //   {
  //     {43, 100, 1, 0},
  //     {43, 100, 1, 0},
  //     {43, 100, 1, 0},
  //     {43, 100, 1, 0}
  //   },
  //   {
  //     {45, 100, 1, 0},
  //     {45, 100, 1, 0},
  //     {45, 100, 1, 0},
  //     {45, 100, 1, 0}
  //   }
  // };
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
  }
};

void Paginator::loadPage (int direction) {
   
};

// copy the steps of the current sequence into
// the state of the paginator
void Paginator::savePage () {
  Serial.println(_pages[0][0][0]);
  
  for (int i = 0; i < 4; i++) {
    Step * step = _sequencer->_steps[i];
    int stepValues[4] = {step->pitch, step->velocity, step->length, step->_state};

    
    for (int x = 0; x < 4; x++) {
      _pages[_currentPage - 1][_sequencer->_currentStep][x] = stepValues[x];
      Serial.println(_pages[0][0][0]);  
    }  
  }

  Serial.println(_pages[0][0][0]);
};

void Paginator::logPages () {
}