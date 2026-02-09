#include <IntPolyh_Couple.hpp>
#include <cstdio>

void IntPolyh_Couple::Dump(const int i) const
{
  printf("\nCouple(%3d) : %5d %5d %3d %5f\n", i, myIndex1, myIndex2, myAnalyzed, myAngle);
}
