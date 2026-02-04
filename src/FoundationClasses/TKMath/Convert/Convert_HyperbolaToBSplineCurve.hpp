#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ConicToBSplineCurve.hpp>
class gp_Hypr2d;

//! This algorithm converts a hyperbola into a rational B-spline curve.
//! The hyperbola is an Hypr2d from package gp with the
//! parametrization :
//! P (U) =
//! Loc + (MajorRadius * std::cosh(U) * Xdir + MinorRadius * std::sinh(U) * Ydir)
//! where Loc is the location point of the hyperbola, Xdir and Ydir are
//! the normalized directions of the local cartesian coordinate system
//! of the hyperbola.
//! KeyWords :
//! Convert, Hyperbola, BSplineCurve, 2D .
class Convert_HyperbolaToBSplineCurve : public Convert_ConicToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  //! The hyperbola H is limited between the parametric values U1, U2
  //! and the equivalent B-spline curve has the same orientation as the
  //! hyperbola.
  Standard_EXPORT Convert_HyperbolaToBSplineCurve(const gp_Hypr2d& H,
                                                  const double     U1,
                                                  const double     U2);
};

