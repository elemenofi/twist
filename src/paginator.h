#ifndef paginator_h
#define paginator_h

class Sequencer;
class Step;

class Paginator {
  int _page;
  Sequencer* _sequencer;
  Step* _pages[4][4];

  public:
    Paginator(Sequencer* sequencer);
    int getPage();
    void nextPage();
    void previousPage();
    void createPage();
};

#endif