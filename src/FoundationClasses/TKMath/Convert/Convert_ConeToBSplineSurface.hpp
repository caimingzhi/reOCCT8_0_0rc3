#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ElementarySurfaceToBSplineSurface.hpp>
class gp_Cone;

//! This algorithm converts a bounded Cone into a rational
//! B-spline surface.
//! The cone a Cone from package gp. Its parametrization is:
//! P (U, V) = Loc + V * Zdir +
//! (R + V*Tan(Ang)) * (std::cos(U)*Xdir + std::sin(U)*Ydir)
//! where Loc is the location point of the cone, Xdir, Ydir and Zdir
//! are the normalized directions of the local cartesian coordinate
//! system of the cone (Zdir is the direction of the Cone's axis),
//! Ang is the cone semi-angle. The U parametrization range is
//! [0, 2PI].
//! KeyWords :
//! Convert, Cone, BSplineSurface.
class Convert_ConeToBSplineSurface : public Convert_ElementarySurfaceToBSplineSurface
{
public:
  DEFINE_STANDARD_ALLOC

  //! The equivalent B-spline surface as the same orientation as the
  //! Cone in the U and V parametric directions.
  //!
  //! Raised if U1 = U2 or U1 = U2 + 2.0 * Pi
  //! Raised if V1 = V2.
  Standard_EXPORT Convert_ConeToBSplineSurface(const gp_Cone& C,
                                               const double   U1,
                                               const double   U2,
                                               const double   V1,
                                               const double   V2);

  //! The equivalent B-spline surface as the same orientation as the
  //! Cone in the U and V parametric directions.
  //!
  //! Raised if V1 = V2.
  Standard_EXPORT Convert_ConeToBSplineSurface(const gp_Cone& C, const double V1, const double V2);
};
