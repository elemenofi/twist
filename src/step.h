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
    int chance;
    int swing;

    Step (Sequencer* sequencer);
    void toggle ();
    void controlLength (int value);
    void controlPitch (int value);
    void controlVelocity (int value);
    void controlChance (int value);
    void controlSwing (int value);
    void setStep (Step* step);
    void reset();
};

#endif