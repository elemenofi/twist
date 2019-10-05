
#include <Arduino.h>
#include "step.h"
#include "note.h"

Note::Note (Step* step) {
  _length = step->length;
  _pitch = step->pitch;
  _velocity = step->velocity;
  _channel = 0;
};

void Note::tick() {
  Serial.println("Note updating");
  _length--;
};
