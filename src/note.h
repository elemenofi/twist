#ifndef note_h
#define note_h

class Step;

class Note {
  public:
    int _pitch;
    int _velocity;
    int _length;
    int _channel;
    Note(Step* step);
    void tick();
};

#endif