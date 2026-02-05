#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ElementarySurfaceToBSplineSurface.hpp>
#include <Standard_Boolean.hpp>
class gp_Sphere;

//! This algorithm converts a bounded Sphere into a rational
//! B-spline surface. The sphere is a Sphere from package gp.
//! The parametrization of the sphere is:
//! P (U, V) = Loc + Radius * std::sin(V) * Zdir +
//! Radius * std::cos(V) * (std::cos(U)*Xdir + std::sin(U)*Ydir)
//! where Loc is the center of the sphere Xdir, Ydir and Zdir are the
//! normalized directions of the local cartesian coordinate system of
//! the sphere. The parametrization range is U [0, 2PI] and
//! V [-PI/2, PI/2].
//! KeyWords :
//! Convert, Sphere, BSplineSurface.
class Convert_SphereToBSplineSurface : public Convert_ElementarySurfaceToBSplineSurface
{
public:
  DEFINE_STANDARD_ALLOC

  //! The equivalent B-spline surface as the same orientation as the
  //! sphere in the U and V parametric directions.
  //!
  //! Raised if U1 = U2 or U1 = U2 + 2.0 * Pi
  //! Raised if V1 = V2.
  Standard_EXPORT Convert_SphereToBSplineSurface(const gp_Sphere& Sph,
                                                 const double     U1,
                                                 const double     U2,
                                                 const double     V1,
                                                 const double     V2);

  //! The equivalent B-spline surface as the same orientation
  //! as the sphere in the U and V parametric directions.
  //!
  //! Raised if UTrim = True and Param1 = Param2 or
  //! Param1 = Param2 + 2.0 * Pi
  //! Raised if UTrim = False and Param1 = Param2
  Standard_EXPORT Convert_SphereToBSplineSurface(const gp_Sphere& Sph,
                                                 const double     Param1,
                                                 const double     Param2,
                                                 const bool       UTrim = true);

  //! The equivalent B-spline surface as the same orientation
  //! as the sphere in the U and V parametric directions.
  Standard_EXPORT Convert_SphereToBSplineSurface(const gp_Sphere& Sph);
};
