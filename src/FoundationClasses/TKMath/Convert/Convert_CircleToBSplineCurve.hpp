#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ConicToBSplineCurve.hpp>
#include <Convert_ParameterisationType.hpp>
class gp_Circ2d;

//! This algorithm converts a circle into a rational B-spline curve.
//! The circle is a Circ2d from package gp and its parametrization is :
//! P (U) = Loc + R * (std::cos(U) * Xdir + std::sin(U) * YDir) where Loc is the
//! center of the circle Xdir and Ydir are the normalized directions
//! of the local cartesian coordinate system of the circle.
//! The parametrization range for the circle is U [0, 2Pi].
//!
//! Warnings :
//! The parametrization range for the B-spline curve is not [0, 2Pi].
//!
//! KeyWords :
//! Convert, Circle, BSplineCurve, 2D .
class Convert_CircleToBSplineCurve : public Convert_ConicToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  //! The equivalent B-spline curve has the same orientation
  //! as the circle C.
  Standard_EXPORT Convert_CircleToBSplineCurve(
    const gp_Circ2d&                   C,
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);

  //! The circle C is limited between the parametric values U1, U2
  //! in radians. U1 and U2 [0.0, 2*Pi] .
  //! The equivalent B-spline curve is oriented from U1 to U2 and has
  //! the same orientation as the circle C.
  //!
  //! Raised if U1 = U2 or U1 = U2 + 2.0 * Pi
  Standard_EXPORT Convert_CircleToBSplineCurve(
    const gp_Circ2d&                   C,
    const double                       U1,
    const double                       U2,
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);
};

