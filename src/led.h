#ifndef led_h
#define led_h

class Led {
  private:
    int m_pin;
    int m_state;
    unsigned long lastBlink;
    int blinkLength = 25;
    boolean blinking = false;
  
  public:
    Led (int pin = 0, int state = LOW) {
      m_pin = pin;
      m_state = state;

      pinMode(m_pin, OUTPUT);
      digitalWrite(m_pin, m_state);
    };

    void blink () {
      digitalWrite(m_pin, !digitalRead(m_pin));
      blinking = true;
      lastBlink = millis();  
    };

    void toggle () {
      m_state = !m_state;

      Serial.print("Toggling led");
      Serial.print(m_pin);

      digitalWrite(m_pin, m_state); 
    };

    void check () {
      if (blinking) {
        if (millis() - lastBlink > blinkLength) {
          digitalWrite(m_pin, !digitalRead(m_pin));
          blinking = false;
        }
      }
    };
};


#endif