#ifndef sequencer_h
#define sequencer_h

class Controller;
class Transport;
class Paginator;
class Step;
class Piano;

class Sequencer {
  Transport* _transport;
  Piano* _piano;
  bool _reversed;
  int _currentStep;

  public:
    Controller* _controller;
    Paginator* _paginator;
    Step* _steps[4];

    Sequencer();
    void tick();
    int getNumber();
    void reverse();
    void step();
    void resetStep();
};

#endif

