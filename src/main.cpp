#include <Arduino.h>
#include "sequence.h"
#include "led.h"
#include "knob.h"
#include "button.h"
#include "definitions.h"

const int step1pin = 2;
const int step2pin = 4;
const int step3pin = 6;
const int step4pin = 8;
const int shiftPin = 10;
const int playPin = 12;

Led led1(3, LOW);
Led led2(5, LOW);
Led led3(7, LOW);
Led led4(9, LOW);
Led led5(11, LOW);
Led led6(24, LOW);

Led* leds[6] = {&led1, &led2, &led3, &led4, &led5, &led6};
Sequence sequence1(leds, false);

Button button1(1, step1pin, *leds[0], sequence1);
Button button2(2, step2pin, *leds[1], sequence1);
Button button3(3, step3pin, *leds[2], sequence1);
Button button4(4, step4pin, *leds[3], sequence1);
Button button5(5, shiftPin, *leds[4], sequence1, true);
Button button6(6, playPin, *leds[5], sequence1, false, true);

Knob knob1(A0, sequence1, FIRST, 0);
Knob knob2(A1, sequence1, SECOND, 1);
Knob knob3(A2, sequence1, THIRD, 2);
Knob knob4(A3, sequence1, FOURTH, 3);
Knob knob5(A4, sequence1, FIFTH, 4);

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
  led6.check();
  knob1.check();
  knob2.check();
  knob3.check();
  knob4.check();
  knob5.check();
}
