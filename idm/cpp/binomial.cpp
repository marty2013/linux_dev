#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <memory>

using namespace std;

class Contract
{
};

class Pricer
{
  public:
    virtual double price() const = 0;
};

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

class European_Binomial_Pricer: public Pricer
{
  private:
    shared_ptr<const European> mContract;
    int mN;
    double mu;
    double md;

  public:
    European_Binomial_Pricer(shared_ptr<const European> contract, int N, double u, double d)
      : mContract(contract), mN{N}, mu{u}, md{d}
    {}

    double price() const;
};

double European_Binomial_Pricer::price() const
{
  // get contract data
  auto S = mContract->get_spot_price();
  auto K = mContract->get_strike_price();
  auto T = mContract->get_time_to_maturity();
  auto r = mContract->get_interest_rate();

  // pre-compute consts
  double dt = T/mN;
  double p = (exp(r * dt) - md)/( mu - md);
  double disc = exp(-r*dt);

  // initialise asset prices at maturity time step N
  vector<double> St;
  St.push_back(S * pow(md, mN));
  for( int j = 1; j <= mN; j++)
    St.push_back(St[j-1] * mu/md);

  // initialise option values as maturity
  vector<double> C;
  for( int j = 0; j <= mN; j++)
    C.push_back(fmax( 0.0, St[j] - K));

  for( int i = (mN-1); i >= 0; i--)
    for( int j = 0; j <= i; j++)
      C[j] = disc * ( p * C[j+1] + (1-p) * C[j]);

  return C[0];
}

int main()
{
  // inputs

  constexpr float S = 100.0;
  constexpr float K = 100.0;
  constexpr float T = 1.0;
  constexpr float r = 0.06;
  constexpr int N = 3;
  constexpr float u = 1.1;
  constexpr float d = 1.0/u;

  auto contract = make_shared<const European>(European( S, K, T, r));

  European_Binomial_Pricer pricer(contract, N, u, d);

  cout << "European Call Price: " + to_string(pricer.price()) + '\n';

}
