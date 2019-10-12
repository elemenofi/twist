#ifndef paginator_h
#define paginator_h

class Sequencer;
class Step;

class Paginator {
  int _currentPage;
  Sequencer* _sequencer;
  
  void logPages();

  public:
    Paginator(Sequencer* sequencer);
    Step * _pages[4][4];

    int getPage();
    void nextPage();
    void previousPage();
    void changePage(int direction);
};

#endif