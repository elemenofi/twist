#ifndef paginator_h
#define paginator_h

class Paginator {
  private:
    int m_page = 1; 
  
  public:
    Paginator () {};

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