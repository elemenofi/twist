#ifndef step_h
#define step_h

#include "controller.h"

class Step {


  public:
    boolean m_state;
    int m_pitch;
    int m_velocity;
    int m_length;

    Step () {
      m_state = false;
      
      m_pitch = 38;
      m_velocity = 100;
      m_length = 4;
    };

    void toggle () {
      m_state = !m_state;
    };

    void controlLength (int value) {
      int newValue = map(value, 0, 1023, 24, 1);
      m_length = newValue;
    };

    void controlPitch (int value) {
      int newValue = map(value, 0, 1023, 51, 38);
      m_pitch = newValue;
    };

    void controlVelocity (int value) {
      int newValue = map(value, 0, 1023, 127, 63);
      m_velocity = newValue;
    };
};

#endif