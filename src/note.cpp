
#include <Arduino.h>
#include "step.h"
#include "note.h"

Note::Note () {
  _length = 0;
  _pitch = 0;
  _velocity = 0;
  _channel = 0;
  _active = false;
};

void Note::tick() {

};

bool Note::isActive() {
  return _active;
};
