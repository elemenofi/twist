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
    Sequence &m_sequence;
    int current;
    long millis_held;    // How long the button was held (milliseconds)
    long secs_held;      // How long the button was held (seconds)
    long prev_secs_held; // How long the button was held in the previous check
    byte previous = LOW;
    unsigned long firstTime; // how long since the button was first pressed 
    unsigned long firstHoldTime; // how long since the button was first pressed 

  public:
    int m_pin;

    Button ();
    
    Button (
      int id,
      int pin, 
      Led& led,
      Sequence& sequence,
      boolean shiftButton = false,
      boolean reverseButton = false
    ): m_led(led), m_sequence(sequence) {
      m_id = id;
      m_pin = pin;
      m_shiftButton = shiftButton;
      m_reverseButton = reverseButton;

      pinMode(pin, INPUT);
    };

    void onPress () {
      Paginator* paginator = m_sequence.m_paginator;
      Serial.println("onPress shiftMode");
      Serial.println(m_sequence.getShiftMode());
      Serial.println("onPress page");
      Serial.println(m_sequence.m_paginator->getPage());

      if (m_state == LOW && m_shiftButton) {
        if (m_sequence.getShiftMode()) {
          paginator->previousPage();
          Serial.println(paginator->getPage());
        } else {
          m_sequence.toggleGlobalMode();
        }
      } else if (m_state == LOW && m_reverseButton) {
        if (m_sequence.getShiftMode()) {
          paginator->nextPage();
          Serial.println(paginator->getPage());
        } else {
          m_led.toggle();
          reverse();
        }
      } else if (m_state == LOW) {
        m_led.toggle();
        m_sequence.m_steps[m_id - 1]->toggle();
      } 
    }

    void reverse () {
      m_sequence.reverse();
    }

    boolean debounce (int current) {
      if (current != previous) {  
        m_lastDebounceTime = millis();
      }

      // if the debounce time has passed
      if ((millis() - m_lastDebounceTime) > 00) {
        // and the current changed
        if (current != m_state) {
          m_state = current;
          
          return true;       
        }
      }

      return false;
    }

    // cleanup all this timing madness

    // in this microcontrollers i have to remember that this is a loop
    // and then i can save a point in time and store it in x
    // and then if x < millis() it is in the past
    // and if x > millis() its in the future
    // and if i want to know how much time has passed i do millis() - x
    // and if i compare millis() - x > z i check if z time has passed
    void check (void) {
      current = digitalRead(m_pin);

      // if the button state changes to pressed, remember the start time 
      if (current == HIGH && previous == LOW && (millis() - firstTime) > 200) {
        firstTime = millis();
        m_led.blink();
        Serial.println("onPress");
      }

      if (current == HIGH && previous == HIGH && (millis() - firstTime) > 1000) {
        firstHoldTime = millis();
        if (!m_sequence.getShiftMode()) Serial.println("onHold");
        m_sequence.enterShiftMode();
      }

      millis_held = (millis() - firstTime);
      secs_held = millis_held / 1000;

      boolean debounced = debounce(current);

      if (debounced && secs_held < 1) {
        onPress();
      }
 
      if (millis_held > 50) {
        // check if the button was released since we last checked
        if (current == LOW && previous == HIGH) {
          if (secs_held >= 1) {
            Serial.print("Seconds held: ");
            Serial.print(secs_held);
            Serial.print("Milliseconds held: ");
            Serial.println(millis_held);
            m_sequence.exitShiftMode();
          }
        }
      }

      previous = current;
      prev_secs_held = secs_held;
    };
};

#endif