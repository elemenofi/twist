#include <Arduino.h>
#include "paginator.h"
#include "step.h"

Paginator::Paginator (Sequencer* sequencer) {
  _sequencer = sequencer;
  _page = 1;

  Step * page[4] = {
    new Step(_sequencer), 
    new Step(_sequencer), 
    new Step(_sequencer), 
    new Step(_sequencer),
  };
};

int Paginator::getPage () {
  return _page;
}

void Paginator::nextPage () {
  if (_page < 4) _page++;
  createPage();
};

void Paginator::previousPage () {
  if (_page > 1) _page--;
};

void Paginator::createPage () {
  // ask the seq
  Serial.println("a");
};