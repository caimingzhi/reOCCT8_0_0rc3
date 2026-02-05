#include <BOPDS_Pave.hpp>

#include <cstdio>

//=================================================================================================

void BOPDS_Pave::Dump() const
{
  printf(" { %-d %-7.3lf}", myIndex, myParameter);
}
