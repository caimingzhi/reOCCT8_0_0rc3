#include <Contap_TheIWLineOfTheIWalking.hpp>

#include <Standard_Type.hpp>

#include <IntSurf_LineOn2S.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_DomainError.hpp>
#include <IntSurf_PathPoint.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <gp_Vec.hpp>

Contap_TheIWLineOfTheIWalking::Contap_TheIWLineOfTheIWalking(const IntSurf_Allocator& theAllocator)
    : line(new IntSurf_LineOn2S(theAllocator)),
      closed(false),
      hasFirst(false),
      hasLast(false),
      firstIndex(-1),
      lastIndex(-1),
      indextg(-1),
      istgtbeg(false),
      istgtend(false)
{
}

void Contap_TheIWLineOfTheIWalking::Reverse()
{
  line->Reverse();
  int N        = line->NbPoints();
  int NbCouple = couple.Length();
  for (int i = 1; i <= NbCouple; i++)
  {
    couple(i) = IntSurf_Couple(N - couple(i).First() + 1, couple(i).Second());
  }
}
