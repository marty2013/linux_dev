#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

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

  // pre-compute consts
  constexpr float dt = T/N;
  constexpr float p = (exp(r * dt) - d)/( u - d);
  constexpr float disc = exp(-r*dt);

  // initialise asset prices at maturity time step N
  vector<float> St;
  St.push_back(S * pow(d, N));
  for( int j = 1; j <= N; j++)
    St.push_back(St[j-1] * u/d);

  // initialise option values as maturity
  vector<float> C;
  for( int j = 0; j <= N; j++)
    C.push_back(fmax( 0.0, St[j] - K));

  for( int i = (N-1); i >= 0; i--)
    for( int j = 0; j <= i; j++)
      C[j] = disc * ( p * C[j+1] + (1-p) * C[j]);

  cout << "European Call Price: " + to_string(C[0]) + '\n';

}
