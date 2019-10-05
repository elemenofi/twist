#ifndef note_h
#define note_h

class Note {
  int _pitch;
  int _velocity;
  int _length;
  int _channel;
  public:
    Note();
    void tick();
};


#endif