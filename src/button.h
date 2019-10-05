#ifndef button_h
#define button_h

class Controller;
class Led;

class Button {
  private:
    int _id;
    int _state;
    int _lastState;
    int _reading;
    bool _shiftButton;
    bool _reverseButton;
    unsigned long _lastDebounceTime;
    int _pin;    
    int _current;
    int _previous;
    unsigned long _firstTime; // how long since the button was first pressed 
    unsigned long _firstHoldTime; // how long since the button was first pressed
    unsigned long _holdThreshold;
    Controller* _controller;
    Led* _led;

  public:    
    Button (
      int id,
      int pin,
      Led* led,
      bool shiftButton,
      bool reverseButton,
      Controller* controller
    );

    void onPress();
    void reverse();
    bool currentIsUp();
    bool currentWentUp();
    bool currentWentDown();     
    bool currentChanged();
    unsigned long timeSincePress();    
    void tick(void);
};

#endif