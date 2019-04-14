#ifndef button_h
#define button_h

#include "definitions.h"

class Button {
  private:
    int m_id;
    int m_state;
    int m_lastState;
    int m_reading;
    boolean m_shiftButton;
    boolean m_playButton;
    unsigned long m_lastDebounceTime;
    Led &m_led;
    Sequence &m_sequence;

  public:
    int m_pin;

    Button ();
    
    Button (
      int id,
      int pin, 
      Led& led,
      Sequence& sequence,
      boolean shiftButton = false,
      boolean playButton = false
    ): m_led(led), m_sequence(sequence) {
      m_id = id;
      m_pin = pin;
      m_shiftButton = shiftButton;
      m_playButton = playButton;

      pinMode(pin, INPUT);
    };

    void onClick () {
      if (m_state == LOW && m_shiftButton) {
        m_led.toggle();
        m_sequence.toggleGlobalMode();
      } else if (m_state == LOW && m_playButton) {
        m_led.toggle();
        play();
      } else if (m_state == LOW) {
        m_led.toggle();
        m_sequence.m_steps[m_id - 1]->toggle();
      } 
    }

    void play () {
      m_sequence.play();
    }

    boolean debounce (int reading) {
      if (reading != m_lastState) {  
        m_lastDebounceTime = millis();
      }

      if ((millis() - m_lastDebounceTime) > 00) {
        if (reading != m_state) {
          m_state = reading;
          
          return true;       
        }
      }

      return false;
    }

    void check (void) {
      m_reading = digitalRead(m_pin);

      boolean debounced = debounce(m_reading);

      if (debounced) {
        onClick();
      }
 
      m_lastState = m_reading;
    };
};

#endif