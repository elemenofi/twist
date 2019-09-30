#ifndef sequence_h
#define sequence_h

#include <Arduino.h>

#include "led.h"
#include "button.h"
#include "knob.h"
#include "definitions.h"
#include "step.h"
#include "transport.h"

class Sequence {
  public:
    Led* m_leds[6];
    Button* m_buttons[6];
    Knob* m_knobs[5];
    Modes m_mode;
    int m_currentStep;
    boolean m_reverse;
    int steps[4] = {0,0,1,0};
    Transport transport;

    Sequence (
      Led* leds[6],
      Button* buttons[6],
      Knob* knobs[5]
    ) {
      assignControls(leds, buttons, knobs);
      m_currentStep = 0;
      m_mode = PITCH;
      m_reverse = false;      
    };

    void check () {
      if (usbMIDI.read()) {
        transport.processMidiClock();
      }

      // ask transport if step should play
    }

    void assignControls (Led* leds[6], Button* buttons[6], Knob* knobs[5]) {
      for (int i = 0; i < 6; i++) {
        m_leds[i] = leds[i];
        m_leds[i]->blink(3);
      }

      for (int i = 0; i < 6; i++) {
        m_buttons[i] = buttons[i];
      }

      for (int i = 0; i < 5; i++) {
        m_knobs[i] = knobs[i];
      }
    }

    void toggleGlobalMode () {
      
      // i would like to add a global mode here 
      // where each knob does something globally
      // special, but no good ideas yet so just a
      // reminder
      
      if (currentMode == PITCH) {
        currentMode = VELOCITY;
        Serial.println("VELOCITY");
        m_leds[4]->blink(999);
      } else if (currentMode == VELOCITY) {
        currentMode = NOTELENGTH;
        Serial.println("NOTELENGTH");
        m_leds[4]->blink();
        m_leds[4]->off();
      } else if (currentMode == NOTELENGTH) {
        currentMode = PITCH;
        Serial.println("PITCH");
        m_leds[4]->blink(); // shut the 999 blinks off
        m_leds[4]->on();
      }
    }

    void doStep () {  
      m_leds[m_currentStep]->blink();

      if (!m_reverse) {
        m_currentStep++;

        if (m_currentStep > 3) {
          m_currentStep = 0;
        }
      } else {
        m_currentStep--;

        if (m_currentStep == -1) {
          m_currentStep = 3;
        }
      }
    };

    void reverse () {
      m_reverse = !m_reverse;
    };
};

#endif