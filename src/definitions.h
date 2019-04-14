#ifndef definitions_h
#define definitions_h

enum Modes {
  PITCH,
  VELOCITY,
  NOTELENGTH,
};

enum Knobs {
  FIRST,
  SECOND,
  THIRD,
  FOURTH,
  FIFTH,
};

Modes currentMode = PITCH;

#endif