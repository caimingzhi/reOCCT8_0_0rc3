#include <Hatch_Hatcher.hpp>
#include <Hatch_Line.hpp>
#include <Hatch_Parameter.hpp>

//=================================================================================================

Hatch_Parameter::Hatch_Parameter()
    : myPar1(0.0),
      myStart(false),
      myIndex(0),
      myPar2(0.0)
{
}

//=================================================================================================

Hatch_Parameter::Hatch_Parameter(const double Par1,
                                 const bool   Start,
                                 const int    Index,
                                 const double Par2)
    : myPar1(Par1),
      myStart(Start),
      myIndex(Index),
      myPar2(Par2)
{
}
