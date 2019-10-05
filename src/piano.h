#ifndef piano_h
#define piano_h

#include <Arduino.h>

class Step;
class Note;
class Sequencer;

class Piano {
  Note* _notes[4];
  Sequencer* _sequencer;

  public:
    Piano(Sequencer* sequencer);
    void tick();
    void play(Step* step);
    Note* findNote();
};

#endif
