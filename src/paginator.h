#ifndef paginator_h
#define paginator_h

class Sequencer;

class Paginator {
  int _page;
  Sequencer* _sequencer;

  public:
    Paginator(Sequencer* sequencer);
    int getPage();
    void nextPage();
    void previousPage();
};

#endif