#ifndef step_h
#define step_h

#include "controller.h"

class Step {
  private:
    Controller &m_controller;

  public:
    boolean m_state;
    int m_pitch;
    int m_velocity;
    int m_length;

    Step (Controller& controller): m_controller(controller) {
      m_state = false;
      m_controller = controller;
      m_pitch = 38;
      m_velocity = 100;
      m_length = 1;
    };

    void toggle () {
      m_state = !m_state;
    };

    int play () {
      m_controller.noteOn(0, m_pitch, m_velocity);
      return m_pitch;
    };

    void stop () {
      // implement polyphony
      m_controller.controlChange(0, 123, 127);
    };

    void controlLength (int value) {
      int newValue = map(value, 0, 1023, m_controller.getPPQN(), 1);
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