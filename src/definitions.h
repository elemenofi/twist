#ifndef definitions_h
#define definitions_h

enum Modes {
  GLOBAL,
  PITCH,
  VELOCITY,
  NOTELENGTH,
  SWING,
  CHORD,
  ARP,
  RANDOM,
  SCALE,
};

enum Knobs {
  FIRST,
  SECOND,
  THIRD,
  FOURTH,
};

Modes currentMode = GLOBAL;

#endif