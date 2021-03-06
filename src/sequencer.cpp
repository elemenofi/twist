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

    // creating steps in paginator memory
    // to prevent motion record bug in non existing pages
    // in the beggining
    Step * step = new Step(this);
    _paginator->copyStep(step, _stepsEdit[i]);
    _paginator->_pages[0][i] = step;
  };
};

// todo: implement sequencer motion record
// todo: implement multi midi channel

void Sequencer::tick() {
  _transport->tick();
  _controller->tick();
}

#define CPU_RESTART_ADDR (uint32_t *)0xE000ED0C
#define CPU_RESTART_VAL 0x5FA0004
#define CPU_RESTART (*CPU_RESTART_ADDR = CPU_RESTART_VAL);

void Sequencer::reset() {
  // CPU_RESTART
  
  _paginator->_currentEditPage = 0;
  _paginator->_createdPages = 0;
  _paginator->_currentPlaybackPage = 0;

  for (int i = 0; i < 4; i++) {
    _stepsEdit[i]->reset();
    _stepsPlayback[i]->reset();
    if (_paginator->_pages[i][0] != 0) _paginator->_pages[i][0]->reset();
    if (_paginator->_pages[i][1] != 0) _paginator->_pages[i][1]->reset();
    if (_paginator->_pages[i][2] != 0) _paginator->_pages[i][2]->reset();
    if (_paginator->_pages[i][3] != 0) _paginator->_pages[i][3]->reset();
    _controller->_leds[i]->off();
  }
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
      _paginator->getNextPlaybackPage(1);
      _currentStep = 0;
    }
  } else {
    _currentStep--;

    if (_currentStep == -1) {
      _paginator->getNextPlaybackPage(-1);
      _currentStep = 3;
    }
  }
};

void Sequencer::resetStep () {
  _currentStep = 0;
};
