
#ifndef knob_h
#define knob_h

class Controller;

class Knob {
  private:
    int _pin;
    int _value;
    int _lastValue;
    int _id;
    Controller* _controller;
  
  public:
    Knob (uint8_t pin, int id, Controller* controller);
    void onChange();
    void tick ();
};

#endif