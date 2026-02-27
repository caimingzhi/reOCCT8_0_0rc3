#pragma once

#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class Extrema_POnSurf
{
public:
  DEFINE_STANDARD_ALLOC

  Extrema_POnSurf()
      : myU(math::precision::Precision::Infinite()),
        myV(math::precision::Precision::Infinite()),
        myP(gp_Pnt(math::precision::Precision::Infinite(), math::precision::Precision::Infinite(), math::precision::Precision::Infinite()))
  {
  }

  Extrema_POnSurf(const double theU, const double theV, const gp_Pnt& theP)
      : myU(theU),
        myV(theV),
        myP(theP)
  {
  }

  const gp_Pnt& Value() const { return myP; }

  void SetParameters(const double theU, const double theV, const gp_Pnt& thePnt)
  {
    myU = theU;
    myV = theV;
    myP = thePnt;
  }

  void Parameter(double& theU, double& theV) const
  {
    theU = myU;
    theV = myV;
  }

private:
  double myU;
  double myV;
  gp_Pnt myP;
};
