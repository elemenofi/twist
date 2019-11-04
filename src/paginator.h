#ifndef paginator_h
#define paginator_h

class Sequencer;
class Step;

class Paginator {
  Sequencer* _sequencer;
  
  void logPages();

  public:
    Paginator(Sequencer* sequencer);
    int _currentEditPage;
    int _currentPlaybackPage;
    int _createdPages;
    // Pages are important because they are used to when moving
    // around with 1 + shift and 1 + reverse, and also when the
    // sequencer gets to the last step it asks the paginator
    // what the next page should be, this way the paginator
    // sets the playback steps that have been copied or saved
    // by the user
    Step * _pages[4][4] = {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    };

    int getPage();
    void nextPage();
    void getNextPlaybackPage(int direction);
    void previousPage();
    void changePage(int direction);
    void debugPages();
    // maybe setLeds could actually be in the led object like .setLedsForSteps
    void setLeds(size_t i);
    void copyStep(Step* step1, Step* step2);
};

#endif