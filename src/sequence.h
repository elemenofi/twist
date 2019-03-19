#ifndef sequence_h
#define sequence_h

#include "piano.h"
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
    Piano* m_piano;
    boolean m_state;
    int m_currentStep;
    int tempo = 120;
    double millisTempo = 60000 / tempo;
    unsigned long lastMillis = 0;
    int ppqn = 0;
    int max_ppqn = 24;
  
  public:
    Sequence (Led* leds[5], boolean state, Piano *piano) {
      m_leds[0] = leds[0];
      m_leds[1] = leds[1];
      m_leds[2] = leds[2];
      m_leds[3] = leds[3];
      m_leds[4] = leds[4];
      m_state = state;
      m_currentStep = 0;
      m_piano = piano;
    };

    void controlPitch (int value, int id) {
      int newValue = map(value, 0, 1023, 51, 38);
      m_piano->notes[id] = newValue;
    };

    void controlVelocity (int value, int id) {
      int newValue = map(value, 0, 1023, 127, 63);
      Serial.println(newValue);
      m_piano->notesVelocities[id] = newValue;
    };

    void controlTempo (int value) {
      // implement internal clock
      // int tempo = map(value, 0, 1023, 60, 280);
      // Serial.println(tempo);
      // millisTempo = 60000 / tempo;
      // 96

      if (value < 400) {
        max_ppqn = 6;

        // ...
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
      m_piano->stopStep();
      
      if (m_state) {
        m_leds[m_currentStep]->blink();


        if (m_steps[m_currentStep].m_state) {
          m_piano->playStep(m_currentStep);
        }

        m_currentStep++;

        if (m_currentStep > 3) {
          m_currentStep = 0;
        }
      }

      lastMillis = millis();
    };

    void toggle () {
      m_state = !m_state;
    };

    void toggleStep (int id) {
      m_steps[id].m_state = !m_steps[id].m_state;
    };

    void advancePPQN () {
      ++ppqn;
          
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
};

#endif