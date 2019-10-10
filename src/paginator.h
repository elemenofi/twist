#ifndef paginator_h
#define paginator_h

class Sequencer;
class Step;

class Paginator {
  int _currentPage;
  Sequencer* _sequencer;
  // int _pages[4][4][4];
  // int _pages[4][4][4] = {
  //   {
  //     {38, 100, 1, 0},
  //     {38, 100, 1, 0},
  //     {38, 100, 1, 0},
  //     {38, 100, 1, 0}
  //   },
  //   {
  //     {40, 100, 1, 0},
  //     {40, 100, 1, 0},
  //     {40, 100, 1, 0},
  //     {40, 100, 1, 0}
  //   },
  //   {
  //     {43, 100, 1, 0},
  //     {43, 100, 1, 0},
  //     {43, 100, 1, 0},
  //     {43, 100, 1, 0}
  //   },
  //   {
  //     {45, 100, 1, 0},
  //     {45, 100, 1, 0},
  //     {45, 100, 1, 0},
  //     {45, 100, 1, 0}
  //   }
  // };
  void logPages();

  public:
    Paginator(Sequencer* sequencer);
    int getPage();
    void nextPage();
    void previousPage();
    void savePage();
    void loadPage(int direction);
};

#endif