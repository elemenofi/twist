#ifndef sequencer_h
#define sequencer_h

class Controller;
class Transport;
class Paginator;
class Step;
class Piano;

class Sequencer {
  bool _reversed;

  public:
    Transport* _transport;
    Controller* _controller;
    Paginator* _paginator;
    Step* _stepsEdit[4];
    Step* _stepsPlayback[4];
    int _currentStep;
    Piano* _piano;

    Sequencer();
    void tick();
    int getNumber();
    void reverse();
    void step();
    void reset();
    void resetStep();
};

#endif

