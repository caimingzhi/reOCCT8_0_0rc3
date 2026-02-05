#include <Hatch_Hatcher.hpp>
#include <Hatch_Line.hpp>
#include <Hatch_Parameter.hpp>

//=================================================================================================

Hatch_Line::Hatch_Line()
    : myForm(Hatch_ANYLINE)
{
}

//=================================================================================================

Hatch_Line::Hatch_Line(const gp_Lin2d& L, const Hatch_LineForm T)
    : myLin(L),
      myForm(T)
{
}

//=================================================================================================

void Hatch_Line::AddIntersection(const double Par1,
                                 const bool   Start,
                                 const int    Index,
                                 const double Par2,
                                 const double theToler)
{
  Hatch_Parameter P(Par1, Start, Index, Par2);
  int             i;
  for (i = 1; i <= myInters.Length(); i++)
  {
    double dfIntPar1 = myInters(i).myPar1;
    // akm OCC109 vvv : Two intersections too close
    if (std::abs(Par1 - dfIntPar1) < theToler)
    {
      myInters.Remove(i);
      return;
    }
    // akm OCC109 ^^^
    if (Par1 < dfIntPar1)
    {
      myInters.InsertBefore(i, P);
      return;
    }
  }
  myInters.Append(P);
}
