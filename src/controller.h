#ifndef controller_h
#define controller_h

#include "definitions.h"

class Sequencer;
class Led;
class Button;
class Knob;

// _shiftMode and _copyMode get their own bool because they can happen at the same time
// the _currentMode is editing mode,  pitch, velocity, note length, it could be more
// then 1 at the same time, thats actually kinda cool, but right now its only one
// at the same time
class Controller {
  Button* _buttons[6];
  Knob* _knobs[6];
  bool _shiftMode;
  Modes _currentMode;
  Modes _modeBeforeChance;
  Modes _modeBeforeMotion;

  public:
    Led* _leds[6];
    Sequencer* _sequencer;
    bool _copyMode;
    Controller(Sequencer* sequencer);
    void tick();
    Modes getMode();
    void toggleMode();
    // i think these modes could be refactored into an enum and then 3 functions 
    // that take that enum as parameter, "shift", "chance", "copy"
    void enterShiftMode();
    void exitShiftMode();
    bool getShiftMode();
    void enterChanceMode();
    void exitChanceMode();
    bool getChanceMode();
    void enterSwingMode();
    void exitSwingMode();
    bool getSwingMode();
    void enterCopyMode();
    void exitCopyMode();
    bool getCopyMode();
    void enterMotionMode();
    void exitMotionMode();
    bool getMotionMode();
};


#endif