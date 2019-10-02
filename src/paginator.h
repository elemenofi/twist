#ifndef paginator_h
#define paginator_h

#include "sequence.h"

class Sequence;

class Paginator {
  Sequence* m_sequence;
  private:
    int m_page = 1;  

  public:
    Paginator () {
      // this->m_page = 1;
    };

    int getPage () {
      return m_page;
    }

    void nextPage () {
      if (m_page < 4) m_page++;
    };

    void previousPage () {
      if (m_page > 1) m_page--;
    };
};

#endif