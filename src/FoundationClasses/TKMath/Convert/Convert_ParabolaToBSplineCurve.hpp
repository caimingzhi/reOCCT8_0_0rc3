#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ConicToBSplineCurve.hpp>
class gp_Parab2d;

//! This algorithm converts a parabola into a non rational B-spline
//! curve.
//! The parabola is a Parab2d from package gp with the parametrization
//! P (U) = Loc + F * (U*U * Xdir + 2 * U * Ydir) where Loc is the
//! apex of the parabola, Xdir is the normalized direction of the
//! symmetry axis of the parabola, Ydir is the normalized direction of
//! the directrix and F is the focal length.
//! KeyWords :
//! Convert, Parabola, BSplineCurve, 2D .
class Convert_ParabolaToBSplineCurve : public Convert_ConicToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  //! The parabola Prb is limited between the parametric values U1, U2
  //! and the equivalent B-spline curve as the same orientation as the
  //! parabola Prb.
  Standard_EXPORT Convert_ParabolaToBSplineCurve(const gp_Parab2d& Prb,
                                                 const double      U1,
                                                 const double      U2);
};

