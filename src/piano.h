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
    int _scale[3][3] = {
      { 36, 41, 43 },
      { 45, 50, 52 },
      { 38, 45, 47 }
    };
    int _currentScale;
    void tick();
    void play(Step* step);
    Note* findNote();
    void transpose(int value);
};

#endif
