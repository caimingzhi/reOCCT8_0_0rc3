#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ConicToBSplineCurve.hpp>
#include <Convert_ParameterisationType.hpp>
class gp_Elips2d;

//! This algorithm converts a ellipse into a rational B-spline curve.
//! The ellipse is represented an Elips2d from package gp with
//! the parametrization :
//! P (U) =
//! Loc + (MajorRadius * std::cos(U) * Xdir + MinorRadius * std::sin(U) * Ydir)
//! where Loc is the center of the ellipse, Xdir and Ydir are the
//! normalized directions of the local cartesian coordinate system of
//! the ellipse. The parametrization range is U [0, 2PI].
//! KeyWords :
//! Convert, Ellipse, BSplineCurve, 2D .
class Convert_EllipseToBSplineCurve : public Convert_ConicToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  //! The equivalent B-spline curve has the same orientation
  //! as the ellipse E.
  Standard_EXPORT Convert_EllipseToBSplineCurve(
    const gp_Elips2d&                  E,
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);

  //! The ellipse E is limited between the parametric values U1, U2.
  //! The equivalent B-spline curve is oriented from U1 to U2 and has
  //! the same orientation as E.
  //!
  //! Raised if U1 = U2 or U1 = U2 + 2.0 * Pi
  Standard_EXPORT Convert_EllipseToBSplineCurve(
    const gp_Elips2d&                  E,
    const double                       U1,
    const double                       U2,
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);
};

