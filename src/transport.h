#ifndef transport_h
#define transport_h

#include <Arduino.h>

class Sequencer;

class Transport {
  Sequencer* _sequencer;
  
  public:
    Transport();
    int max_ppqn;
    int ppqn;
    int _state;
    Transport(Sequencer* sequence);
    void tick();
    int getPPQN();
    void controlTempo(int tempo);
    void processMidi();
    void advancePPQN();
    void startPPQN();
    void stopPPQN();
    void printBytes(const byte *data, unsigned int size);
};


#endif