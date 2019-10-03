#ifndef sequence_h
#define sequence_h

#include "led.h"
#include "definitions.h"
#include "step.h"
#include "paginator.h"

class Paginator;

class Sequence {  
  public:
    int m_currentStep;
    Step* m_steps[4];
    Led* m_leds[6];
    Modes m_mode;
    boolean m_reverse;
    boolean m_shiftMode;
    int m_page = 1;
    Paginator* m_paginator;
    Controller &m_controller;

    Sequence (Step* steps[4], Led* leds[6], Controller& controller): m_controller(controller) {
      for (int i = 0; i < 6; i++) {
        m_leds[i] = leds[i];
      };

      for (int i = 0; i < 4; i++) {
        m_steps[i] = steps[i];
      };
      
      m_currentStep = 0;
      m_mode = PITCH;
      m_reverse = false;
      m_controller = controller;
      m_paginator = new Paginator();
      m_leds[4]->toggle();
      m_leds[5]->toggle();
      Serial.println("Inited Sequence");
      Serial.println(m_paginator->getPage());
    };

    void enterShiftMode () {
      m_shiftMode = true;
    };

    void exitShiftMode () {
      m_shiftMode = false;
    };

    boolean getShiftMode () {
      return m_shiftMode;
    }

    void toggleGlobalMode () {
            
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

    void tick () {
      m_controller.tick();
    };

    void doStep () {  
      m_leds[m_currentStep]->blink();

      Step* current = m_steps[m_currentStep];

      if (current->m_state) {
        m_controller.play(
          current->m_pitch,
          current->m_velocity,
          current->m_length
        );
      }

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

    void resetStep () {
      m_currentStep = 0;
    };

    void reverse () {
      m_reverse = !m_reverse;
    };
};

#endif