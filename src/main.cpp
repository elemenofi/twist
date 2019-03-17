#include <Arduino.h>
#include "sequence.h"
#include "piano.h"
#include "led.h"

class Button {
  private:
    int m_id;
    int m_pin;
    int m_state;
    int m_lastState;
    int m_reading;
    boolean m_startStop;
    unsigned long m_lastDebounceTime;
    Led &m_led;
    Sequence &m_sequence;

  public:
    Button ();
    Button (
      int id,
      int pin, 
      Led& led,
      Sequence& sequence,
      boolean startStop = false
    ): m_led(led), m_sequence(sequence) {
      m_id = id;
      m_pin = pin;
      m_startStop = startStop;

      pinMode(pin, INPUT);
    };

    void onClick () {
      if (m_state == LOW && m_startStop) {
        m_led.toggle();
        m_sequence.toggle();
      } else if (m_state == LOW) {
        m_led.toggle();
        m_sequence.toggleStep(m_id - 1);
      } 
    };

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

enum Knobs {
  TEMPO,
  LENGTH,
  MAGIC,
  NOTE,
};

class Knob {
  private:
    uint8_t m_pin;
    int m_value;
    int m_lastValue;
    Sequence &m_sequence;
    Knobs m_knobType;
  
  public:
    Knob (uint8_t pin, Sequence& sequence, Knobs knobType): m_sequence(sequence) {
      m_pin = pin;
      m_knobType = knobType;
    };

    void check () {
      m_value = analogRead(m_pin);

      if (m_value != m_lastValue) {
        // Serial.print("a");
        if (m_knobType == TEMPO) {
          m_sequence.controlTempo(m_value);
        } else if (m_knobType == LENGTH) {
        } else if (m_knobType == NOTE) {
        } else if (m_knobType == MAGIC) {
        }

        m_lastValue = m_value;
      }
    };
};

const int step1pin = 2;
const int step2pin = 4;
const int step3pin = 6;
const int step4pin = 8;
const int shiftPin = 10;
const int startStopPin = 12;

Led led1(3, LOW);
Led led2(5, LOW);
Led led3(7, LOW);
Led led4(9, LOW);
Led led5(13, LOW);

Led* leds[5] = {&led1, &led2, &led3, &led4, &led5};
Piano piano;
Sequence sequence1(leds, false, &piano);

Button button1(1, step1pin, *leds[0], sequence1);
Button button2(2, step2pin, *leds[1], sequence1);
Button button3(3, step3pin, *leds[2], sequence1);
Button button4(4, step4pin, *leds[3], sequence1);
Button button5(5, shiftPin, *leds[4], sequence1);
Button button6(6, startStopPin, *leds[4], sequence1, true);

Knob knob1(A0, sequence1, TEMPO);
Knob knob2(A1, sequence1, LENGTH);
Knob knob3(A2, sequence1, NOTE);
Knob knob4(A3, sequence1, MAGIC);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (usbMIDI.read()) {
    sequence1.processMidi();
  }
  
  button1.check();
  button2.check();
  button3.check();
  button4.check();
  button5.check();
  button6.check();
  led1.check();
  led2.check();
  led3.check();
  led4.check();
  led5.check();
  knob1.check();
  knob2.check();
  knob3.check();
  knob4.check();
}
