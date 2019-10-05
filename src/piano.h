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
    void noteOn(byte channel, byte pitch, byte velocity);
    void noteOff(byte channel, byte pitch, byte velocity);
    // First parameter is the event type (0x0B = control change).
    // Second parameter is the event type, combined with the channel.
    // Third parameter is the control number number (0-119).
    // Fourth parameter is the control value (0-127).
    void controlChange (byte channel, byte control, byte value);
};

#endif