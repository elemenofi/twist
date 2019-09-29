#ifndef sequence_h
#define sequence_h

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
    Step* steps[4] = {0,0,0,0};

    Sequence (
      Led* leds[6]
    ) {
      memcpy(m_leds, leds, 6);
      memcpy(m_buttons, buttons, 6);
      memcpy(m_knobs, knobs, 6);
      m_currentStep = 0;
      m_mode = PITCH;
      m_reverse = false;
      m_leds[4]->toggle();
      m_leds[5]->toggle();
    };

    void check () {
      if (usbMIDI.read()) {
        processMidi();
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
        // m_leds[4]->blink(999);
      } else if (currentMode == VELOCITY) {
        currentMode = NOTELENGTH;
        Serial.println("NOTELENGTH");
        // m_leds[4]->blink();
        // m_leds[4]->off();
      } else if (currentMode == NOTELENGTH) {
        currentMode = PITCH;
        Serial.println("PITCH");
        // m_leds[4]->blink(); // shut the 999 blinks off
        // m_leds[4]->on();
      }
    }

    void doStep () {  
      // m_leds[m_currentStep]->blink();

      // if (m_steps[m_currentStep]->m_state) {
      // }

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

    boolean stepIsOver (int ppqn) {
      // return ppqn >= m_steps[m_currentStep]->m_length;
      return true;
    };

    void stopCurrentStep () {
    };

    void resetStep () {
      m_currentStep = 0;
    };

    void reverse () {
      m_reverse = !m_reverse;
    };

    void stopSteps (int ppqn) {
      if (stepIsOver(ppqn)) {
        // here i have to check the note length
        // of the active note to see if i do the stop step
        stopCurrentStep();
      }
    };

    void processMidi () {
    };
};

#endif