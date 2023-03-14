#include <iostream>
#include <string>
#include <memory>

#include "european.h"
#include "european_bin_pricer.h"

using namespace idm;

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

  auto contract = std::make_shared<European>(European( S, K, T, r));

  European_Binomial_Pricer pricer(contract, N, u, d);

  std::cout << "European Call Price: " + std::to_string(pricer.price()) + '\n';
}
