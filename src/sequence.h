#ifndef sequence_h
#define sequence_h

#include "led.h"

class Step {
  public:
    boolean m_state;

    Step (boolean state = false) {
      m_state = state;
    };
};

class Sequence {
  private:
    Led* m_leds[5];
    Step m_steps[4];
    boolean m_state;
    int m_currentStep;
    int tempo = 120;
    double millisTempo = 60000 / tempo;
    unsigned long lastMillis = 0;
    int ppqn = 0;
    int max_ppqn = 24;
    int activeNote = 0;
    int notes[4] = {38, 41, 45, 51};
    int notesVelocities[4] = {100, 100, 100, 100};
    int notesLengths[4] = {1, 1, 1, 1};
  
  public:
    Sequence (Led* leds[5], boolean state) {
      m_leds[0] = leds[0];
      m_leds[1] = leds[1];
      m_leds[2] = leds[2];
      m_leds[3] = leds[3];
      m_leds[4] = leds[4];
      m_state = state;
      m_currentStep = 0;
    };

    void controlLength (int value, int id) {
      int newValue = map(value, 0, 1023, 4, 1);
      notesLengths[id] = newValue;
    };

    void controlPitch (int value, int id) {
      int newValue = map(value, 0, 1023, 51, 38);
      notes[id] = newValue;
    };

    void controlVelocity (int value, int id) {
      int newValue = map(value, 0, 1023, 127, 63);
      notesVelocities[id] = newValue;
    };

    void controlTempo (int value) {
      if (value < 400) {
        max_ppqn = 6;

        if (ppqn >= 6) {
          ppqn = 0;
        }
      } else if (value >= 400 && value < 800) {
        max_ppqn = 8;

        if (ppqn >= 8) {
          ppqn = 0;
        }
      } else if (value >= 800 && value <= 1023) {
        max_ppqn = 12;
      }
    };

    int randValue (int min, int max) {
      int range = max - min + 1;
      int num = rand() % range + min;
      return num;
    };

    void doStep () {  
      if (m_state) {
        m_leds[m_currentStep]->blink();

        if (m_steps[m_currentStep].m_state) {
          playStep(m_currentStep);
        }

        m_currentStep++;

        if (m_currentStep > 3) {
          m_currentStep = 0;
        }
      }
    };

    void toggle () {
      m_state = !m_state;
    };

    void toggleStep (int id) {
      m_steps[id].m_state = !m_steps[id].m_state;
    };

    void advancePPQN () {
      ++ppqn;
      if (ppqn) {
        // here i have to check the note length
        // of the active note to see if i do the stop step
        stopStep();
      }


      if (ppqn == max_ppqn) {
        doStep(); 
        ppqn = 0;
      }
    };

    void startPPQN () {
      m_state = true;
      ppqn = 0;
      doStep();
      digitalWrite(13, HIGH);
    };

    void stopPPQN () {
      m_state = false;
      ppqn = 0;
      m_currentStep = 0;
      digitalWrite(13, LOW);
    };

    void processMidi () {
      byte type, channel, data1, data2, cable;
 
      type = usbMIDI.getType();       // which MIDI message, 128-255
      channel = usbMIDI.getChannel(); // which MIDI channel, 1-16
      data1 = usbMIDI.getData1();     // first data byte of message, 0-127
      data2 = usbMIDI.getData2();     // second data byte of message, 0-127
      cable = usbMIDI.getCable();     // which virtual cable with MIDIx8, 0-7

      switch (type) {
        case usbMIDI.Clock: // 0xF8 
          advancePPQN();
          break;

        case usbMIDI.Start: // 0xFA
          startPPQN();
          break;

        case usbMIDI.Stop: // 0xFC
          stopPPQN();
          break;

        default:
          Serial.println("Opps, an unknown MIDI message type!");
      }
    }

    void printBytes(const byte *data, unsigned int size) {
      while (size > 0) {
        byte b = *data++;
        if (b < 16) Serial.print('0');
        Serial.print(b, HEX);
        if (size > 1) Serial.print(' ');
        size = size - 1;
      }
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

    void stopStep () {
      noteOff(0, activeNote, 127);
    };

    void playStep (int step) {
      noteOn(0, notes[step], notesVelocities[step]);
      activeNote = notes[step];
    };
};

#endif