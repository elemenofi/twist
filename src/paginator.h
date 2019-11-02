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