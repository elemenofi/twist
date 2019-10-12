#include <Arduino.h>
#include "sequencer.h"
#include "paginator.h"
#include "step.h"

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
  
};

void Paginator::logPages () {};