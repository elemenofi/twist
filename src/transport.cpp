#include <Arduino.h>
#include "transport.h"
#include "definitions.h"
#include "sequencer.h"
#include "controller.h"
#include "led.h"

// this class has to keep track of the midi packets coming from the outside
// it also has the implementation of the top right knob that controls resolution
// and its job is also to tell the sequence when the next step starts
// its then responsibility of the controller to create the note and its responsibility
// of the note when to stop sounding. 
// step timing is what is handled here

Transport::Transport (Sequencer* sequencer) {
  _sequencer = sequencer;
  _state = false;
  max_ppqn = 24;
  ppqn = 0;
};

void Transport::tick () {
  if (usbMIDI.read()) {
    processMidi();
  }
};

int Transport::getPPQN () {
  return max_ppqn;
}

void Transport::controlTempo (int value) {
  if (value < 400) {
    max_ppqn = 6;

    if (ppqn >= 6) {
      ppqn = 0;
    }
  } else if (value >= 400 && value < 800) {
    max_ppqn = 8;

    if (ppqn >= 8) {
      ppqn = 0;
    }
  } else if (value >= 800 && value <= 1023) {
    max_ppqn = 10;
  }
};

  // move midi to midi class
void Transport::processMidi () {
  byte type;
  // byte type, channel, data1, data2, cable;

  type = usbMIDI.getType();       // which MIDI message, 128-255
  // channel = usbMIDI.getChannel(); // which MIDI channel, 1-16
  // data1 = usbMIDI.getData1();     // first data byte of message, 0-127
  // data2 = usbMIDI.getData2();     // second data byte of message, 0-127
  // cable = usbMIDI.getCable();     // which virtual cable with MIDIx8, 0-7

  switch (type) {
    case usbMIDI.Clock: // 0xF8 
      advancePPQN();
      break;

    case usbMIDI.Start: // 0xFA
      startPPQN();
      break;

    case usbMIDI.Stop: // 0xFC
      stopPPQN();
      break;

    default:
      Serial.println("Opps, an unknown MIDI message type!");
  }
}

void Transport::advancePPQN () {
  ++ppqn;

  Serial.println("Tick in transport");

  if (ppqn == max_ppqn) {
    _sequencer->step(); 
    ppqn = 0;
  }
};

void Transport::startPPQN () {
  _state = true;
  ppqn = 0;
  _sequencer->step(); 
  _sequencer->_controller->_leds[5]->toggle();
};

void Transport::stopPPQN () {
  _state = false;
  ppqn = 0;
  _sequencer->resetStep();
  _sequencer->_controller->_leds[5]->toggle();
};

void Transport::printBytes(const byte *data, unsigned int size) {
  while (size > 0) {
    byte b = *data++;
    if (b < 16) Serial.print('0');
    Serial.print(b, HEX);
    if (size > 1) Serial.print(' ');
    size = size - 1;
  }
};


