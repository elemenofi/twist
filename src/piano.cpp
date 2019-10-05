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
  
};

void Piano::play (Step* step) {
  Serial.println("Play");
};

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


