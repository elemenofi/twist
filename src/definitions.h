#ifndef definitions_h
#define definitions_h

const int step1pin = 2;
const int step2pin = 4;
const int step3pin = 6;
const int step4pin = 8;
const int shiftPin = 10;
const int playPin = 12;

enum Modes {
  PITCH,
  VELOCITY,
  NOTELENGTH,
  CHANCE,
  SWING
};

#endif