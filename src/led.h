#ifndef led_h
#define led_h

#include "definitions.h"

class Led {
  private:
    int m_pin;
    int m_state;
    unsigned long lastBlink;
    unsigned long blinkLength = 75;
    boolean blinking = false;
  
  public:
    int blinkingCounter;
    Led (int pin = 0, int state = LOW) {
      m_pin = pin;
      m_state = state;

      pinMode(m_pin, OUTPUT);
      digitalWrite(m_pin, m_state);
    };

    void blink (int times = 0) {
      digitalWrite(m_pin, !digitalRead(m_pin));
      blinking = true;
      blinkingCounter = times;
      lastBlink = millis();  
    };

    void toggle () {
      m_state = !m_state;

      digitalWrite(m_pin, m_state); 
    };

    int check () {
      if (blinking && millis() - lastBlink > blinkLength) {
        digitalWrite(m_pin, !digitalRead(m_pin));
        blinking = false;
        lastBlink = millis();        
      }

      if (!blinking && blinkingCounter > 0 && millis() - lastBlink > blinkLength) {
        blink(blinkingCounter - 1);
        blinkingCounter--;
      }
    };
};


#endif