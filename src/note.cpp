
#include <Arduino.h>
#include "step.h"
#include "note.h"

Note::Note () {
  reset();
};

void Note::tick() {
  if (!_active) return;
  _length--;

  if (_length <= 0) {
    // String noteLog = "Note off, pitch: ";
    // //Serial.println(noteLog + _pitch);    
    noteOff(_channel, _pitch, _velocity);
    reset();
  }
};

bool Note::isActive() {
  return _active;
};

void Note::reset() {
  _length = 0;
  _pitch = 0;
  _velocity = 0;
  _channel = 9;
  _active = false;
};

void Note::play(Step* step, int scale[3]) {
  _active = true;
  _length = step->length;
  _pitch = scale[step->pitchGrade];
  _velocity = step->velocity;
  noteOn(_channel, _pitch, _velocity);
};

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).
void Note::noteOn(byte channel, byte pitch, byte velocity) {
  usbMIDI.sendNoteOn(pitch, velocity, channel);
  usbMIDI.send_now();
};

void Note::noteOff(byte channel, byte pitch, byte velocity) {
  usbMIDI.sendNoteOff(pitch, velocity, channel);
  usbMIDI.send_now();
};

// todo: move control change to controller

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).
void Note::controlChange (byte channel, byte control, byte value) {
  usbMIDI.sendControlChange(control, value, channel);
};
