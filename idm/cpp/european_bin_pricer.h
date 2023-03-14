#ifndef __IDM_EUROPEAN_BINOMIAL_PRICER
#define __IDM_EUROPEAN_BINOMIAL_PRICER

#include <memory>
#include "european.h"
#include "pricer.h"

namespace idm
{
  class European_Binomial_Pricer: public Pricer
  {
    private:
      int mN;
      double mu;
      double md;

    public:
      European_Binomial_Pricer(std::shared_ptr<European> contract, int N, double u, double d)
        : Pricer(contract), mN{N}, mu{u}, md{d}
      {}

      double price() const;
  };
}

#endif // __IDM_EUROPEAN_BINOMIAL_PRICER
