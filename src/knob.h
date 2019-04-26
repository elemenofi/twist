
#ifndef knob_h
#define knob_h

#include "definitions.h"
#include "transport.h"

class Knob {
  private:
    uint8_t m_pin;
    int m_value;
    int m_lastValue;
    int m_id;
    Sequence &m_sequence;
    Transport &m_transport;
    Knobs m_knobType;
  
  public:
    Knob (uint8_t pin, Sequence& sequence, Transport& transport, Knobs knobType, int id): m_sequence(sequence), m_transport(transport) {
      m_pin = pin;
      m_knobType = knobType;
      m_id = id;
    };

    void onChange () {
      if (m_knobType == FIFTH) {
        m_transport.controlTempo(m_value);
      } else {
        if (currentMode == VELOCITY) {
          m_sequence.m_steps[m_id]->controlVelocity(m_value);
        } else if (currentMode == PITCH) {
          m_sequence.m_steps[m_id]->controlPitch(m_value);
        } else if (currentMode == NOTELENGTH) {
          m_sequence.m_steps[m_id]->controlLength(m_value);
        }
      }
    }

    void check () {
      // todo latch

      m_value = analogRead(m_pin);

      int diff = abs(m_value - m_lastValue);

      // "filter"
      const boolean isChanging = m_value != m_lastValue && diff > 10;

      if (isChanging) {
        onChange();

        m_lastValue = m_value;
      }
    };
};

#endif