#include <Arduino.h>
#include "note.h"
#include "piano.h"
#include "step.h"

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
  note->play(step);
};




