#ifndef controller_h
#define controller_h

#include "definitions.h"

class Sequencer;
class Led;
class Button;
class Knob;

class Controller {
  Button* _buttons[6];
  Knob* _knobs[6];
  bool _shiftMode;
  Modes _currentMode;
  Modes _modeBeforeChance;

  public:
    Led* _leds[6];
    Sequencer* _sequencer;
    Controller(Sequencer* sequencer);
    void tick();
    Modes getMode();
    void toggleMode();
    void enterShiftMode();
    void exitShiftMode();
    bool getShiftMode();
    void enterChanceMode();
    void exitChanceMode();
    bool getChanceMode();
};


#endif