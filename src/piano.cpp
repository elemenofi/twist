#include <Arduino.h>
#include "note.h"
#include "piano.h"
#include "step.h"

Piano::Piano (Sequencer* sequencer) {
  _sequencer = sequencer;
  _notes[0] = new Note();
  _notes[1] = new Note();
  _notes[2] = new Note();
  _notes[3] = new Note();
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
};

void Piano::play (Step* step) {
  Note* note = findNote();
  note->play(step);
};




