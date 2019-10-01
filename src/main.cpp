#include <Arduino.h>
#include "sequence.h"
#include "led.h"
#include "knob.h"
#include "button.h"
#include "definitions.h"
#include "controller.h"
#include "transport.h"
#include "step.h"

Led led1(3, LOW);
Led led2(5, LOW);
Led led3(7, LOW);
Led led4(9, LOW);
Led led5(11, LOW);
Led led6(24, LOW);
Led* leds[6] = {&led1, &led2, &led3, &led4, &led5, &led6};

Controller controller;
Step step1(controller);
Step step2(controller);
Step step3(controller);
Step step4(controller);
Step* steps[4] = {&step1, &step2, &step3, &step4};

Sequence sequence(steps, leds);
Transport transport(sequence);

// implement a hold function to be able to switch pages with the right and left
Button button1(1, step1pin, *leds[0], sequence);
Button button2(2, step2pin, *leds[1], sequence);
Button button3(3, step3pin, *leds[2], sequence);
Button button4(4, step4pin, *leds[3], sequence);
Button button5(5, shiftPin, *leds[4], sequence, true);
Button button6(6, playPin, *leds[5], sequence, false, true);

Knob knob1(A0, sequence, transport, FIRST, 0);
Knob knob2(A1, sequence, transport, SECOND, 1);
Knob knob3(A2, sequence, transport, THIRD, 2);
Knob knob4(A3, sequence, transport, FOURTH, 3);
Knob knob5(A4, sequence, transport, FIFTH, 4);
// implement a scale knob that transposes the sequencer

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (usbMIDI.read()) {
    transport.processMidi();
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
