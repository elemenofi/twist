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
  if (!_controller->getShiftMode()) {
    _controller->_leds[_currentStep]->blink();
  }

  if (!_reversed) {
    _currentStep++;

    if (_currentStep > 3) {
      _paginator->getNextPage(1);
      _currentStep = 0;
    }
  } else {
    _currentStep--;

    if (_currentStep == -1) {
      _paginator->getNextPage(-1);
      _currentStep = 3;
    }
  }
};

void Sequencer::resetStep () {
  _currentStep = 0;
};
