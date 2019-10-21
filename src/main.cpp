#include <Arduino.h>
#include "sequencer.h" 

// todo: here im going to create 16 channels
// and each will have a sequencer
// so the sequencer can change from
// one channel to another because
// the easiest way i can think of right now
// is to change some sort of variable that all
// channels have and if that channel is the
// selected one then you would be controlling
// only the sequencer for that channel, the other
// channels would be runnning independently.
// thus giving the machine 16 channels of midi
// another option is to make it so that
// its not one sequencer per each channel
// but actually many tracks with each one 
// having a sequencer but all in the same
// channel, this would be cool to program
// for example drum machines or maybe more 
// complex polyphonic stuff
Sequencer* sequencer = new Sequencer();

void setup() {
  Serial.begin(9600); 
}

void loop() {
  sequencer->tick();
}