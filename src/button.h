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
    boolean m_reverseButton;
    unsigned long m_lastDebounceTime;
    Led &m_led;
    boolean m_wasPressed;

  public:
    int m_pin;

    Button ();
    
    Button (
      int id,
      int pin, 
      Led& led,
      boolean shiftButton = false,
      boolean reverseButton = false
    ): m_led(led) {
      m_id = id;
      m_pin = pin;
      m_shiftButton = shiftButton;
      m_reverseButton = reverseButton;
      m_wasPressed = false;

      pinMode(pin, INPUT);
    };

    void onPress () {
      if (m_state == LOW && m_shiftButton) {
        m_led.toggle();
      } else if (m_state == LOW && m_reverseButton) {
        m_led.toggle();
        reverse();
      } else if (m_state == LOW) {
        m_led.toggle();
        m_wasPressed = true;
      } 
    }

    void reverse () {
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

    // a debounced button press
    boolean check (void) {
      m_reading = digitalRead(m_pin);

      boolean debounced = debounce(m_reading);

      if (debounced) {
        onPress();
      }
 
      m_lastState = m_reading;

      if (m_wasPressed) {
        m_wasPressed = false;
        return true;
      } else {
        return false;
      }
    };
};

#endif