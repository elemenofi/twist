#ifndef sequencer_h
#define sequencer_h

class Controller;
class Transport;
class Paginator;
class Step;
class Piano;

class Sequencer {
  Piano* _piano;
  bool _reversed;

  public:
    Transport* _transport;
    Controller* _controller;
    Paginator* _paginator;
    Step* _stepsEdit[4];
    Step* _stepsPlayback[4];
    int _currentStep;

    Sequencer();
    void tick();
    int getNumber();
    void reverse();
    void step();
    void resetStep();
};

#endif

