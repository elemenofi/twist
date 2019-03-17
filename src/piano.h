#ifndef piano_h
#define piano_h

#include <usb_midi.h>

class Piano {
  private:
    int notes[4] = {38, 41, 45, 51};
    int activeNote = 38;
  public:
    Piano () {};
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

    void stopStep (int step) {
      noteOff(0, activeNote, 127);
    }

    void playStep (int step) {
      noteOn(0, notes[step], 127);
      activeNote = notes[step];
      Serial.println(activeNote);
    };
};

#endif