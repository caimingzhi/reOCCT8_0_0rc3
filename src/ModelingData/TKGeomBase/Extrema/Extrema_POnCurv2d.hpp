#pragma once

#include <gp_Pnt2d.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class Extrema_POnCurv2d
{
public:
  DEFINE_STANDARD_ALLOC

  Extrema_POnCurv2d()
      : myU(0.0)
  {
  }

  Extrema_POnCurv2d(const double theU, const gp_Pnt2d& theP)
      : myU(theU),
        myP(theP)
  {
  }

  void SetValues(const double theU, const gp_Pnt2d& theP)
  {
    myU = theU;
    myP = theP;
  }

  const gp_Pnt2d& Value() const { return myP; }

  double Parameter() const { return myU; }

private:
  double   myU;
  gp_Pnt2d myP;
};
