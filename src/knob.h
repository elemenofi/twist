
#ifndef knob_h
#define knob_h

#include "definitions.h"

class Knob {
  private:
    uint8_t m_pin;
    int m_value;
    int m_lastValue;
    int m_id;
    Sequence &m_sequence;
    Knobs m_knobType;
  
  public:
    Knob (uint8_t pin, Sequence& sequence, Knobs knobType, int id): m_sequence(sequence) {
      m_pin = pin;
      m_knobType = knobType;
      m_id = id;
    };

    void check () {
      m_value = analogRead(m_pin);

      // "filter"
      int diff = abs(m_value - m_lastValue);

      if (m_value != m_lastValue && diff > 10) {
        if (currentMode == GLOBAL) {
          if (m_knobType == FIRST) {
            m_sequence.controlTempo(m_value);
          } else if (m_knobType == SECOND) {
            
          } else if (m_knobType == THIRD) {
          } else if (m_knobType == FOURTH) {  
            // delay
            // transpose
          }
        } else if (currentMode == VELOCITY) {
          m_sequence.controlVelocity(m_value, m_id);
        } else if (currentMode == PITCH) {
          m_sequence.controlPitch(m_value, m_id);
        } else if (currentMode == PITCH) {
          m_sequence.controlLength(m_value, m_id);
        }

        m_lastValue = m_value;
      }
    };
};

#endif