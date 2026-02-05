#include <IntPolyh_Edge.hpp>
#include <cstdio>

//=================================================================================================

void IntPolyh_Edge::Dump(const int i) const
{
  printf("\nEdge(%3d) : P1:%5d   P2:%5d   T1:%5d   T2:%5d\n",
         i,
         myPoint1,
         myPoint2,
         myTriangle1,
         myTriangle2);
}
