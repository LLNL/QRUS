

typedef unsigned Index_t;
typedef double   Real_t;

template <typename T>
struct vector {
  T * data;

  T       & operator[](Index_t i)       { return data[i]; }
  T const & operator[](Index_t i) const { return data[i]; }
};

struct Mesh {
  public:
    Real_t  & x         (Index_t idx) { return m_x[idx];    }
    Real_t  & xd        (Index_t idx) { return m_xd[idx];   }
    Real_t  & deltatime ()            { return m_deltatime; }
    Index_t & numNode   ()            { return m_numNode;   }

  private:
    vector<Real_t> m_x;
    vector<Real_t> m_xd;
    Real_t         m_deltatime;
    Index_t        m_numNode;
} mesh;

static inline void CalcPositionForNodes(const Real_t dt) {
  Index_t numNode = mesh.numNode();
  for ( Index_t i = 0; i < numNode; ++i) {
    mesh.x(i) += mesh.xd(i) * dt;
  }
}

int main(int argc, char *argv[]) {
  const Real_t delt = mesh.deltatime();
  CalcPositionForNodes(delt);
  return 0 ;
}


