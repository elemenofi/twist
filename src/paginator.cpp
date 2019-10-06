#include <Arduino.h>
#include "sequencer.h"
#include "paginator.h"
#include "step.h"

Paginator::Paginator (Sequencer* sequencer) {
  _sequencer = sequencer;
  _page = 0;
  int _pages[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  };
};

int Paginator::getPage () {
  return _page;
}

void Paginator::nextPage () {
  if (_page < 4) {
    _page++;
    createPage();
  }
};

void Paginator::previousPage () {
  if (_page > 1) {
    _page--;
  }
};

void Paginator::createPage () {
  // ask the seq
  for (int i = 0; i < 4; i++) {
    Step * step = _sequencer->_steps[i];
    Serial.println("Step:");
    int stepValues[4] = {step->pitch, step->velocity, step->length, step->_state};
    for (size_t x = 0; x < 4; x++) {
     _pages[_page][x] = stepValues[x];
     Serial.println(_pages[_page][x]);
    }
  }  
};