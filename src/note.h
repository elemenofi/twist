#ifndef note_h
#define note_h

class Step;

class Note {
  public:
    int _pitch;
    int _velocity;
    int _length;
    int _channel;
    int _active;
    Note();
    void tick();
    bool isActive();
    void reset();
    void play(Step* step, int scale[3]);
    void noteOn(byte channel, byte pitch, byte velocity);
    void noteOff(byte channel, byte pitch, byte velocity);
    // First parameter is the event type (0x0B = control change).
    // Second parameter is the event type, combined with the channel.
    // Third parameter is the control number number (0-119).
    // Fourth parameter is the control value (0-127).
    void controlChange (byte channel, byte control, byte value);
};

#endif