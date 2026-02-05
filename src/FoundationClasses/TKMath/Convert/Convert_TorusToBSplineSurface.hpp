#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ElementarySurfaceToBSplineSurface.hpp>
#include <Standard_Boolean.hpp>
class gp_Torus;

//! This algorithm converts a bounded Torus into a rational
//! B-spline surface. The torus is a Torus from package gp.
//! The parametrization of the torus is :
//! P (U, V) =
//! Loc + MinorRadius * std::sin(V) * Zdir +
//! (MajorRadius+MinorRadius*std::cos(V)) * (std::cos(U)*Xdir + std::sin(U)*Ydir)
//! where Loc is the center of the torus, Xdir, Ydir and Zdir are the
//! normalized directions of the local cartesian coordinate system of
//! the Torus. The parametrization range is U [0, 2PI], V [0, 2PI].
//! KeyWords :
//! Convert, Torus, BSplineSurface.
class Convert_TorusToBSplineSurface : public Convert_ElementarySurfaceToBSplineSurface
{
public:
  DEFINE_STANDARD_ALLOC

  //! The equivalent B-spline surface as the same orientation as the
  //! torus in the U and V parametric directions.
  //!
  //! Raised if U1 = U2 or U1 = U2 + 2.0 * Pi
  //! Raised if V1 = V2 or V1 = V2 + 2.0 * Pi
  Standard_EXPORT Convert_TorusToBSplineSurface(const gp_Torus& T,
                                                const double    U1,
                                                const double    U2,
                                                const double    V1,
                                                const double    V2);

  //! The equivalent B-spline surface as the same orientation as the
  //! torus in the U and V parametric directions.
  //!
  //! Raised if Param1 = Param2 or Param1 = Param2 + 2.0 * Pi
  Standard_EXPORT Convert_TorusToBSplineSurface(const gp_Torus& T,
                                                const double    Param1,
                                                const double    Param2,
                                                const bool      UTrim = true);

  //! The equivalent B-spline surface as the same orientation as the
  //! torus in the U and V parametric directions.
  Standard_EXPORT Convert_TorusToBSplineSurface(const gp_Torus& T);
};
