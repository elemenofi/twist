#ifndef step_h
#define step_h

class Sequencer;

class Step {
  Sequencer* _sequencer;

  public:
    int pitchScale;
    int pitchGrade;
    int velocity;
    int length;
    bool _state;

    Step (Sequencer* sequencer);
    void toggle ();
    void controlLength (int value);
    void controlPitch (int value);
    void controlVelocity (int value);
};

#endif