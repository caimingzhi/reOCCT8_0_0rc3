#pragma once


#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

//! Definition of a point on surface.
class Extrema_POnSurf
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creation of an indefinite point on surface.
  Extrema_POnSurf()
      : myU(Precision::Infinite()),
        myV(Precision::Infinite()),
        myP(gp_Pnt(Precision::Infinite(), Precision::Infinite(), Precision::Infinite()))
  {
  }

  //! Creation of a point on surface with parameter
  //! values on the surface and a Pnt from gp.
  Extrema_POnSurf(const double theU, const double theV, const gp_Pnt& theP)
      : myU(theU),
        myV(theV),
        myP(theP)
  {
  }

  //! Returns the 3d point.
  const gp_Pnt& Value() const { return myP; }

  //! Sets the params of current POnSurf instance.
  //! (e.g. to the point to be projected).
  void SetParameters(const double theU, const double theV, const gp_Pnt& thePnt)
  {
    myU = theU;
    myV = theV;
    myP = thePnt;
  }

  //! Returns the parameter values on the surface.
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

