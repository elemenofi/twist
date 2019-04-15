#ifndef sequence_h
#define sequence_h

#include "led.h"
#include "definitions.h"
#include "step.h"

class Sequence {  
  public:
    int m_currentStep;
    Step* m_steps[4];
    Led* m_leds[6];
    Modes m_mode;

    Sequence (Step* steps[4], Led* leds[6]) {
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
      m_currentStep = 0;
      m_mode = PITCH;
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
      } else if (currentMode == VELOCITY) {
        currentMode = NOTELENGTH;
        Serial.println("NOTELENGTH");
      } else if (currentMode == NOTELENGTH) {
        currentMode = PITCH;
        Serial.println("PITCH");
      }
    }

    void doStep () {  
      m_leds[m_currentStep]->blink();

      if (m_steps[m_currentStep]->m_state) {
        m_steps[m_currentStep]->play();
      }

      m_currentStep++;

      if (m_currentStep > 3) {
        m_currentStep = 0;
      }
    };

    boolean stepIsOver (int ppqn) {
      return ppqn >= m_steps[m_currentStep]->m_length;
    };

    void stopCurrentStep () {
      m_steps[m_currentStep]->stop();
    };

    void resetStep () {
      m_currentStep = 0;
    };

    void play () {
      Serial.println("Play");
    };
};

#endif