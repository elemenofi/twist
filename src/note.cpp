
#include "step.h"
#include "note.h"

Note::Note (Step* step) {
  _ended = false;
  _length = step->length;
  _pitch = step->pitch;
  _velocity = step->velocity;
  // todo: channel support
  _channel = 0;
};

void Note::tick() {
  // Serial.println("Note updating");
  _length--;
  
  if (_length <= 0) {
    _ended = true;
  }
};
