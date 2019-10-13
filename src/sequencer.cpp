#include <Arduino.h>
#include "sequencer.h"
#include "controller.h"
#include "transport.h"
#include "paginator.h"
#include "step.h"
#include "led.h"
#include "piano.h"

Sequencer::Sequencer () {
  _controller = new Controller(this);
  _transport = new Transport(this);
  _paginator = new Paginator(this);
  _piano = new Piano(this);
  _reversed = false;
  _currentStep = 0;

  for (int i = 0; i < 4; i++) {
    _stepsEdit[i] = new Step(this);
    _stepsPlayback[i] = _stepsEdit[i];
  };
};

void Sequencer::tick() {
  _transport->tick();
  _controller->tick();
}

void Sequencer::reverse() {
  _reversed = !_reversed;
}

void Sequencer::step () {  
  _piano->tick();

  _controller->_leds[_currentStep]->blink();

  Step* current = _stepsPlayback[_currentStep];

  if (current->_state) {
    Serial.println(current->pitch);
    
    _piano->play(current);
  }

  if (!_reversed) {
    _currentStep++;

    if (_currentStep > 3) {
      _paginator->getNextPage();
      _currentStep = 0;
    }
  } else {
    _currentStep--;

    if (_currentStep == -1) {
      _currentStep = 3;
    }
  }
};

void Sequencer::resetStep () {
  _currentStep = 0;
};
