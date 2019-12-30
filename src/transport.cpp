#include <Arduino.h>
#include "transport.h"
#include "definitions.h"
#include "sequencer.h"
#include "controller.h"
#include "led.h"
#include "piano.h"
#include "step.h"

// this class has to keep track of the midi packets coming from the outside
// it also has the implementation of the top right knob that controls resolution
// and its job is also to tell the sequence when the next step starts
// step timing is what is handled here

Transport::Transport (Sequencer* sequencer) {
  _sequencer = sequencer;
  _state = false;
  max_ppqn = 24;
  ppqn = 0;
  swingPpqn = 0;
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
  if (value < 250) {
    max_ppqn = 6;

    if (ppqn >= 6) {
      ppqn = 0;
    }
  } else if (value >= 250 && value < 500) {
    max_ppqn = 8;

    if (ppqn >= 8) {
      ppqn = 0;
    }
  } else if (value >= 500 && value < 750) {
    max_ppqn = 10;

    if (ppqn >= 10) {
      ppqn = 0;
    }
  } else if (value >= 750 && value <= 1023) {
    max_ppqn = 24;
  }
};

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
      Serial.println("START");
      startPPQN();
      break;

    case usbMIDI.Stop: // 0xFC
      Serial.println("STOP");
      stopPPQN();
      break;

    default:;
      //Serial.println("Opps, an unknown MIDI message type!");
  }
}

void Transport::advancePPQN () {
  ++ppqn;

  _sequencer->_piano->tick();

  Step* current = _sequencer->_stepsPlayback[_sequencer->_currentStep];

  // todo maybe the chance logic should be in the sequencer
  // so sequencer should have a play step function that
  // gets called when the transport knows about a steps swing
  // and then a normal step function to just advance the ui
  // because that should be unaffected by swing

  if (ppqn == (max_ppqn + current->swing) && current->_state) {
    int rand = random(100);
    if (rand <= current->chance) _sequencer->_piano->play(current);
  } else if (ppqn == swingPpqn && ppqn > 0) {
    int rand = random(100);
    if (rand <= current->chance) _sequencer->_piano->play(current);
    swingPpqn = 0; 
  }

  // this maybe should go before so that the sequencer does not get
  // out of sync from the master
  if (ppqn == max_ppqn) {
    _sequencer->step();
    
    ppqn = 0;

    if (current->swing > 0) {
      swingPpqn = current->swing;
    }
  }
};

void Transport::startPPQN () {
  _state = true;
  ppqn = 0;
  _sequencer->step();
  _sequencer->_piano->tick();
  Step* current = _sequencer->_stepsPlayback[_sequencer->_currentStep];
  if (current->_state) _sequencer->_piano->play(current);
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
}


