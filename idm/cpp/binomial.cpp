#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

class Pricer
{
  public:
    virtual double price() const = 0;
};

class European_Binomial: public Pricer
{
  private:
    double mS;
    double mK;
    double mT;
    double mr;
    int mN;
    double mu;
    double md;

  public:
     European_Binomial( double S, double K, double T, double r, int N, double u, double d)
       :mS{S}, mK{K}, mT{T}, mr{r}, mN{N}, mu{u}, md{d}
     {}

     double price() const;
};

double European_Binomial::price() const
{
  // pre-compute consts
  double dt = mT/mN;
  double p = (exp(mr * dt) - md)/( mu - md);
  double disc = exp(-mr*dt);

  // initialise asset prices at maturity time step N
  vector<double> St;
  St.push_back(mS * pow(md, mN));
  for( int j = 1; j <= mN; j++)
    St.push_back(St[j-1] * mu/md);

  // initialise option values as maturity
  vector<double> C;
  for( int j = 0; j <= mN; j++)
    C.push_back(fmax( 0.0, St[j] - mK));

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

  European_Binomial bin_pricer( S, K, T, r, N, u, d);

  cout << "European Call Price: " + to_string(bin_pricer.price()) + '\n';

}
