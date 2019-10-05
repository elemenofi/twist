#include "paginator.h"

Paginator::Paginator (Sequencer* sequencer) {
  _sequencer = sequencer;
  _page = 1;
};

int Paginator::getPage () {
  return _page;
}

void Paginator::nextPage () {
  if (_page < 4) _page++;
};

void Paginator::previousPage () {
  if (_page > 1) _page--;
};