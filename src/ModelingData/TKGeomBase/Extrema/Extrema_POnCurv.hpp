#pragma once

#include <gp_Pnt.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

//! Definition of a point on curve.
class Extrema_POnCurv
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creation of an indefinite point on curve.
  Extrema_POnCurv()
      : myU(0.0)
  {
  }

  //! Creation of a point on curve with a parameter
  //! value on the curve and a Pnt from gp.
  Extrema_POnCurv(const double theU, const gp_Pnt& theP)
      : myU(theU),
        myP(theP)
  {
  }

  //! Sets the point and parameter values.
  void SetValues(const double theU, const gp_Pnt& theP)
  {
    myU = theU;
    myP = theP;
  }

  //! Returns the point.
  const gp_Pnt& Value() const { return myP; }

  //! Returns the parameter on the curve.
  double Parameter() const { return myU; }

private:
  double myU;
  gp_Pnt myP;
};
