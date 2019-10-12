#ifndef paginator_h
#define paginator_h

class Sequencer;
class Step;

class Paginator {
  Sequencer* _sequencer;
  
  void logPages();

  public:
    Paginator(Sequencer* sequencer);
    int _currentPage;
    Step * _pages[4][4] = {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    };

    int getPage();
    void nextPage();
    void previousPage();
    void changePage(int direction);
    void debugPages();
};

#endif