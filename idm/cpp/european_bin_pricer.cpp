
#include <vector>
#include <cmath>

#include "european_bin_pricer.h"

namespace idm
{
  double European_Binomial_Pricer::price() const
  {
    auto contract = dynamic_cast<European*>(mContract.get());

    // get contract data
    auto S = contract->get_spot_price();
    auto K = contract->get_strike_price();
    auto T = contract->get_time_to_maturity();
    auto r = contract->get_interest_rate();

    // pre-compute consts
    double dt = T/mN;
    double p = (exp(r * dt) - md)/( mu - md);
    double disc = exp(-r*dt);

    // initialise asset prices at maturity time step N
    std::vector<double> St;
    St.push_back(S * pow(md, mN));
    for( int j = 1; j <= mN; j++)
      St.push_back(St[j-1] * mu/md);

    // initialise option values as maturity
    std::vector<double> C;
    for( int j = 0; j <= mN; j++)
      C.push_back(fmax( 0.0, St[j] - K));

    for( int i = (mN-1); i >= 0; i--)
      for( int j = 0; j <= i; j++)
        C[j] = disc * ( p * C[j+1] + (1-p) * C[j]);

    return C[0];
  }
}
