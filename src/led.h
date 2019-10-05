#ifndef led_h
#define led_h

class Led {
  private:
    int _pin;
    int _state;
    unsigned long _lastBlink;
    unsigned long _blinkLength;
    bool _blinking;
    int _blinkingCounter;
  
  public:
    Led(int pin, int state);
    void blink(int times = 0);
    void toggle();
    void off();
    void on();
    void tick();
    bool blinkTimePassed();
};

#endif




