#include <Arduino.h>
#include "sequencer.h"
#include "controller.h"
#include "transport.h"
#include "paginator.h"
#include "step.h"
#include "led.h"

Sequencer::Sequencer () {
  _controller = new Controller(this);
  _transport = new Transport(this);
  _paginator = new Paginator(this);
  _reversed = false;
  _currentStep = 0;

  for (int i = 0; i < 4; i++){
    _steps[i] = new Step(this);
  }
};

void Sequencer::tick() {
  _transport->tick();
  _controller->tick();
}

void Sequencer::reverse() {
  _reversed = !_reversed;
}

void Sequencer::step () {  
  _controller->_leds[_currentStep]->blink(1);

  Step* current = _steps[_currentStep];

  if (current->_state) {
    // piano play step
    // m_controller.play(
    //   current->m_pitch,
    //   current->m_velocity,
    //   current->m_length
    // );
  }

  if (!_reversed) {
    _currentStep++;

    if (_currentStep > 3) {
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
