#ifndef note_h
#define note_h

class Step;

class Note {
  public:
    int _pitch;
    int _velocity;
    int _length;
    int _channel;
    bool _ended;
    Note(Step* step);
    void tick();
};


#endif