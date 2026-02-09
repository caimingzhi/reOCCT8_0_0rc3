

#include <NCollection_Primes.hpp>

#include <Standard_OutOfRange.hpp>

#include <algorithm>
#include <array>

namespace
{

  constexpr std::array<int, 24> THE_PRIME_VECTOR = {
    101,      1009,     2003,     5003,      10007,     20011,     37003,      57037,
    65003,    100019,   209953,   472393,    995329,    2359297,   4478977,    9437185,
    17915905, 35831809, 71663617, 150994945, 301989889, 573308929, 1019215873, 2038431745};
}

int NCollection_Primes::NextPrimeForMap(const int theN) noexcept
{
  auto aResult = std::lower_bound(THE_PRIME_VECTOR.begin(), THE_PRIME_VECTOR.end(), theN + 1);
  if (aResult == THE_PRIME_VECTOR.end())
  {

    return theN + 1;
  }
  return *aResult;
}
