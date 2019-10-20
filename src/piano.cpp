#include <Arduino.h>
#include "note.h"
#include "piano.h"
#include "step.h"
#include "sequencer.h"

Piano::Piano (Sequencer* sequencer) {
  _sequencer = sequencer;

  _currentScale = 0;

  for (int i = 0; i < 4; i++) {
    _notes[i] = new Note();
  } 
};

void Piano::tick () {
  for (int i = 0; i < 4; i++) {
    _notes[i]->tick();
  } 
};

Note* Piano::findNote() {
  for (int i = 0; i < 4; i++) {
    if (!_notes[i]->_active) {
      return _notes[i];
    }
  }

  return 0; // <-- hack to get rid of a warning, hate my life
};

void Piano::play (Step* step) {
  Note* note = findNote();
  auto& scale = _scale[step->pitchScale];
  note->play(step, scale);
};

void Piano::transpose (int value) {
  int newValue = value;

  if (value < 330) {
    newValue = 2;
  } else if (value < 660) {
    newValue = 1;
  } else if (value <= 1023) {
    newValue = 0;
  }

  if (_currentScale != newValue) {
    for (size_t i = 0; i < 4; i++) {
      _sequencer->_stepsEdit[i]->pitchScale = newValue;
    }
  }

  _currentScale = newValue;
};




