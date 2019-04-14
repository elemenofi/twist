#ifndef sequence_h
#define sequence_h

#include "led.h"
#include "definitions.h"
#include "controller.h"
#include "step.h"

class Sequence {
  private:
    boolean m_state;
    int m_currentStep;
    int tempo = 120;
    double millisTempo = 60000 / tempo;
    unsigned long lastMillis = 0;
    int ppqn = 0;
    int max_ppqn = 24;
    int activeNote = 0;
  
  public:
    Step* m_steps[4];
    Led* m_leds[6];
    Modes m_mode;
    Controller &m_controller;

    Sequence (Step* steps[4], Led* leds[6], boolean state, Controller& controller): m_controller(controller) {
      m_leds[0] = leds[0];
      m_leds[1] = leds[1];
      m_leds[2] = leds[2];
      m_leds[3] = leds[3];
      m_leds[4] = leds[4];
      m_leds[5] = leds[5];
      m_steps[0] = steps[0];
      m_steps[1] = steps[1];
      m_steps[2] = steps[2];
      m_steps[3] = steps[3];
      m_state = state;
      m_currentStep = 0;
      m_mode = PITCH;
      m_controller = controller;
    };

    void toggleGlobalMode () {
      m_leds[4]->blink(3);
      
      // i would like to add a global mode here 
      // where each knob does something globally
      // special, but no good ideas yet so just a
      // reminder
      
      if (currentMode == PITCH) {
        currentMode = VELOCITY;
        Serial.println("VELOCITY");
        m_leds[0]->blink(3);
      } else if (currentMode == VELOCITY) {
        currentMode = NOTELENGTH;
        Serial.println("NOTELENGTH");
        m_leds[1]->blink(3);
      } else if (currentMode == NOTELENGTH) {
        currentMode = PITCH;
        Serial.println("PITCH");
        m_leds[2]->blink(3);
      }
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

      m_controller.setPPQN(max_ppqn);
    };

    int randValue (int min, int max) {
      int range = max - min + 1;
      int num = rand() % range + min;
      return num;
    };

    void doStep () {  
      if (m_state) {
        m_leds[m_currentStep]->blink();

        if (m_steps[m_currentStep]->m_state) {
          activeNote = m_steps[m_currentStep]->play();
        }

        m_currentStep++;

        if (m_currentStep > 3) {
          m_currentStep = 0;
        }
      }
    };

    void play () {
      Serial.println("Play");
    }

    void toggle () {
      m_state = !m_state;
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

      if (ppqn >= m_steps[m_currentStep]->m_length) {
        // here i have to check the note length
        // of the active note to see if i do the stop step
        m_steps[m_currentStep]->stop();
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
      m_leds[5]->toggle();
    };

    void stopPPQN () {
      m_state = false;
      ppqn = 0;
      m_currentStep = 0;
      m_leds[5]->toggle();
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