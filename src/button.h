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
    Modes m_mode;
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
      m_mode = GLOBAL;

      pinMode(pin, INPUT);
    };

    void onClick () {
      if (m_state == LOW && m_shiftButton) {
        m_led.toggle();
        toggleGlobalMode();
      } else if (m_state == LOW && m_playButton) {
        m_led.toggle();
        play();
      } else if (m_state == LOW) {
        m_led.toggle();
        m_sequence.toggleStep(m_id - 1);
      } 
    }

    void play () {
      Serial.println("Play");
    }

    void toggleGlobalMode () {
      m_led.blink();
      
      if (currentMode == GLOBAL) {
        currentMode = PITCH;
        Serial.println("PITCH");
        m_sequence.m_leds[0]->blink(3);
      } else if (currentMode == PITCH) {
        currentMode = VELOCITY;
        Serial.println("VELOCITY");
        m_sequence.m_leds[1]->blink(3);
      } else if (currentMode == VELOCITY) {
        currentMode = NOTELENGTH;
        Serial.println("NOTELENGTH");
        m_sequence.m_leds[2]->blink(3);
      } else if (currentMode == NOTELENGTH) {
        currentMode = GLOBAL;
        Serial.println("GLOBAL");
        m_sequence.m_leds[3]->blink(3);
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