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
      m_length = 4;
    };

    void toggle () {
      m_state = !m_state;
    };


    // i will move this responsibility to the 
    // note manager that i will communicate with in the controller
    // in this class i wanna save data per step and control that data

    // void play () {
    //   m_controller.noteOn(0, m_pitch, m_velocity);
    // };

    
    // void stop () {
    //   m_controller.controlChange(0, 123, 127);
    // };

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