#pragma once


#include <gp_Pnt2d.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

//! Definition of a point on 2D curve.
class Extrema_POnCurv2d
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creation of an indefinite point on curve.
  Extrema_POnCurv2d()
      : myU(0.0)
  {
  }

  //! Creation of a point on curve with a parameter
  //! value on the curve and a Pnt from gp.
  Extrema_POnCurv2d(const double theU, const gp_Pnt2d& theP)
      : myU(theU),
        myP(theP)
  {
  }

  //! Sets the point and parameter values.
  void SetValues(const double theU, const gp_Pnt2d& theP)
  {
    myU = theU;
    myP = theP;
  }

  //! Returns the point.
  const gp_Pnt2d& Value() const { return myP; }

  //! Returns the parameter on the curve.
  double Parameter() const { return myU; }

private:
  double   myU;
  gp_Pnt2d myP;
};

