#ifndef controller_h
#define controller_h

#include "note.h"

class Controller {
  Note* m_notes[4];

  public:
    Controller () {};

    void tick () {
      Serial.println("Tick in controller");
      if (m_notes[0]) m_notes[0]->update();

      // i have to figure out how to destroy the objects because
      // this length check is a hack. length would go infinite negative
      // calling note off all the time
      if (m_notes[0]->m_ended && m_notes[0]->m_length == 0) {
        noteOff(m_notes[0]->m_channel, m_notes[0]->m_pitch, m_notes[0]->m_velocity);
      }
    }

    void play (int pitch, int velocity, int length) {
      // create new note pass self as reference
      noteOn(0, pitch, velocity);
      Note* note = new Note(pitch, velocity, length, 0);
      m_notes[0] = note;
    }

    // First parameter is the event type (0x09 = note on, 0x08 = note off).
    // Second parameter is note-on/note-off, combined with the channel.
    // Channel can be anything between 0-15. Typically reported to the user as 1-16.
    // Third parameter is the note number (48 = middle C).
    // Fourth parameter is the velocity (64 = normal, 127 = fastest).
    void noteOn(byte channel, byte pitch, byte velocity) {
      usbMIDI.sendNoteOn(pitch, velocity, channel);
      usbMIDI.send_now();
    };

    void noteOff(byte channel, byte pitch, byte velocity) {
      usbMIDI.sendNoteOff(pitch, velocity, channel);
      usbMIDI.send_now();
    };

    // First parameter is the event type (0x0B = control change).
    // Second parameter is the event type, combined with the channel.
    // Third parameter is the control number number (0-119).
    // Fourth parameter is the control value (0-127).
    void controlChange (byte channel, byte control, byte value) {
      usbMIDI.sendControlChange(control, value, channel);
    };
};

#endif