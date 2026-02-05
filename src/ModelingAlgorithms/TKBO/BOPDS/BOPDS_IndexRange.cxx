#include <BOPDS_IndexRange.hpp>

#include <cstdio>

//=================================================================================================

void BOPDS_IndexRange::Dump() const
{
  printf(" range: %d %d", myFirst, myLast);
}
