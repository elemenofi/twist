#ifndef transport_h
#define transport_h

#include "sequence.h"
#include "definitions.h"

class Transport {
  private:
    boolean m_state;
    int max_ppqn = 24;
    int ppqn = 0;
    Sequence &m_sequence;
    
  public:
    Transport (Sequence& sequence): m_sequence(sequence) {
      m_state = false;
    };

    int getPPQN () {
      return max_ppqn;
    }

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

     // move midi to midi class
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

    void advancePPQN () {
      ++ppqn;

      if (ppqn >= m_sequence.m_steps[m_sequence.m_currentStep]->m_length) {
        // here i have to check the note length
        // of the active note to see if i do the stop step
        m_sequence.m_steps[m_sequence.m_currentStep]->stop();
      }


      if (ppqn == max_ppqn) {
        m_sequence.doStep(); 
        ppqn = 0;
      }
    };

    void startPPQN () {
      m_state = true;
      ppqn = 0;
      m_sequence.doStep(); 
      m_sequence.m_leds[5]->toggle();
    };

    void stopPPQN () {
      m_state = false;
      ppqn = 0;
      m_sequence.m_currentStep = 0;
      m_sequence.m_leds[5]->toggle();
    };

    void printBytes(const byte *data, unsigned int size) {
      while (size > 0) {
        byte b = *data++;
        if (b < 16) Serial.print('0');
        Serial.print(b, HEX);
        if (size > 1) Serial.print(' ');
        size = size - 1;
      }
    }
};

#endif