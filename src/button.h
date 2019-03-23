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
    unsigned long m_lastDebounceTime;
    Led &m_led;
    Sequence &m_sequence;

  public:
    int m_pin;
    Modes m_mode;
    Button ();
    Button (
      int id,
      int pin, 
      Led& led,
      Sequence& sequence,
      boolean shiftButton = false
    ): m_led(led), m_sequence(sequence) {
      m_id = id;
      m_pin = pin;
      m_shiftButton = shiftButton;
      m_mode = GLOBAL;

      pinMode(pin, INPUT);
    };

    void onClick () {
      if (m_state == LOW && m_shiftButton) {
        toggleGlobalMode();
      } else if (m_state == LOW) {
        m_led.toggle();
        m_sequence.toggleStep(m_id - 1);
      } 
    };

    void toggleGlobalMode() {
      if (currentMode == GLOBAL) {
        currentMode = PITCH;
        Serial.println("PITCH");
      } else if (currentMode == PITCH) {
        currentMode = VELOCITY;
        Serial.println("VELOCITY");
      } else if (currentMode == VELOCITY) {
        currentMode = NOTELENGTH;
        Serial.println("NOTELENGTH");
      } else if (currentMode == NOTELENGTH) {
        currentMode = GLOBAL;
        Serial.println("GLOBAL");
      }
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