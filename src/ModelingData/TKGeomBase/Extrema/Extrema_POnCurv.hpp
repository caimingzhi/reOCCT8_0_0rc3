#pragma once

#include <gp_Pnt.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class Extrema_POnCurv
{
public:
  DEFINE_STANDARD_ALLOC

  Extrema_POnCurv()
      : myU(0.0)
  {
  }

  Extrema_POnCurv(const double theU, const gp_Pnt& theP)
      : myU(theU),
        myP(theP)
  {
  }

  void SetValues(const double theU, const gp_Pnt& theP)
  {
    myU = theU;
    myP = theP;
  }

  const gp_Pnt& Value() const { return myP; }

  double Parameter() const { return myU; }

private:
  double myU;
  gp_Pnt myP;
};
