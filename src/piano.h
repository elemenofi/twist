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
    int _scale[3][8] = {
      { 60, 62, 63, 65, 67, 69, 70, 72 },
      { 62, 64, 65, 67, 69, 71, 72, 74 },
      { 64, 66, 67, 69, 71, 73, 74, 76 }
    };
    int _currentScale;
    void tick();
    void play(Step* step);
    Note* findNote();
    void transpose(int value);
};

#endif
