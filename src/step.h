#ifndef step_h
#define step_h

#include "controller.h"

class Step {
  private:
    Controller m_controller;

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

    void play () {
      // we are going to create a piano singleton in the sequence class
      // and we are going to pass it to each state, so they can tell
      // the piano to add notes, and the piano will have the job of killing
      // the knobs and keeping track of them, the step just tells when the note should start
      // and what note with which velocity and length, but not when to stop. the polyphone lets
      // say is going to be a responsibility of the piano, which will be a member of sequence
      // and thus will be able to execute code whenever a step goes through and a note length has
      // been completed.
      // make a note class and check them all
      // clock cycles to know when they have to die
    }

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