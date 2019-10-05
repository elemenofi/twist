#include <Arduino.h>
#include "note.h"
#include "piano.h"
#include "step.h"


Piano::Piano (Sequencer* sequencer) {
  _sequencer = sequencer;
};

void Piano::tick () {
  if (_notes[0]) _notes[0]->tick();

  // i have to figure out how to destroy the objects because
  // this length check is a hack. length would go infinite negative
  // calling note off all the time
  if (_notes[0]->_length == 0) {
    noteOff(_notes[0]->_channel, _notes[0]->_pitch, _notes[0]->_velocity);
    delete _notes[0];
  }
}

void Piano::play (Step* step) {
  // create new note pass self as reference
  noteOn(0, step->pitch, step->velocity);
  Note* note = new Note(step);
  _notes[0] = note;
}

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).
void Piano::noteOn(byte channel, byte pitch, byte velocity) {
  usbMIDI.sendNoteOn(pitch, velocity, channel);
  usbMIDI.send_now();
};

void Piano::noteOff(byte channel, byte pitch, byte velocity) {
  usbMIDI.sendNoteOff(pitch, velocity, channel);
  usbMIDI.send_now();
};

// todo: move control change to controller

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).
void Piano::controlChange (byte channel, byte control, byte value) {
  usbMIDI.sendControlChange(control, value, channel);
};


