#ifndef __IDM_EUROPEAN_H
#define __IDM_EUROPEAN_H

#include "contract.h"

namespace idm
{
  class European: public Contract
  {
    private:
      double mS;
      double mK;
      double mT;
      double mr;

    public:
      European( double S, double K, double T, double r)
        :mS{S}, mK{K}, mT{T}, mr{r}
      {}
      
      double get_spot_price() const { return mS;}
      double get_strike_price() const { return mK;}
      double get_time_to_maturity() const { return mT;}
      double get_interest_rate() const { return mr;}
  };
}

#endif // __IDM_EUROPEAN_H

