#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
class Geom2d_Curve;
class Geom_Curve;
class Geom_Surface;
class Geom_Plane;
class gp_Dir;

//! Projection of a curve on a surface.
class GeomProjLib
{
public:
  DEFINE_STANDARD_ALLOC

  //! gives the 2d-curve of a 3d-curve lying on a
  //! surface (uses GeomProjLib_ProjectedCurve)
  //! The 3dCurve is taken between the parametrization
  //! range [First, Last]
  //! <Tolerance> is used as input if the projection needs
  //! an approximation. In this case, the reached
  //! tolerance is set in <Tolerance> as output.
  //! WARNING: if the projection has failed, this
  //! method returns a null Handle.
  Standard_EXPORT static occ::handle<Geom2d_Curve> Curve2d(const occ::handle<Geom_Curve>&   C,
                                                           const double                     First,
                                                           const double                     Last,
                                                           const occ::handle<Geom_Surface>& S,
                                                           const double                     UFirst,
                                                           const double                     ULast,
                                                           const double                     VFirst,
                                                           const double                     VLast,
                                                           double& Tolerance);

  //! gives the 2d-curve of a 3d-curve lying on a
  //! surface (uses GeomProjLib_ProjectedCurve)
  //! The 3dCurve is taken between the parametrization
  //! range [First, Last]
  //! <Tolerance> is used as input if the projection needs
  //! an approximation. In this case, the reached
  //! tolerance is set in <Tolerance> as output.
  //! WARNING: if the projection has failed, this
  //! method returns a null Handle.
  Standard_EXPORT static occ::handle<Geom2d_Curve> Curve2d(const occ::handle<Geom_Curve>&   C,
                                                           const double                     First,
                                                           const double                     Last,
                                                           const occ::handle<Geom_Surface>& S,
                                                           double& Tolerance);

  //! gives the 2d-curve of a 3d-curve lying on a
  //! surface (uses GeomProjLib_ProjectedCurve)
  //! The 3dCurve is taken between the parametrization
  //! range [First, Last]
  //! If the projection needs an approximation,
  //! Precision::PApproximation() is used.
  //! WARNING: if the projection has failed, this
  //! method returns a null Handle.
  Standard_EXPORT static occ::handle<Geom2d_Curve> Curve2d(const occ::handle<Geom_Curve>&   C,
                                                           const double                     First,
                                                           const double                     Last,
                                                           const occ::handle<Geom_Surface>& S);

  //! gives the 2d-curve of a 3d-curve lying on a
  //! surface (uses GeomProjLib_ProjectedCurve)
  //! If the projection needs an approximation,
  //! Precision::PApproximation() is used.
  //! WARNING: if the projection has failed, this
  //! method returns a null Handle.
  Standard_EXPORT static occ::handle<Geom2d_Curve> Curve2d(const occ::handle<Geom_Curve>&   C,
                                                           const occ::handle<Geom_Surface>& S);

  //! gives the 2d-curve of a 3d-curve lying on a
  //! surface (uses GeomProjLib_ProjectedCurve)
  //! If the projection needs an approximation,
  //! Precision::PApproximation() is used.
  //! WARNING: if the projection has failed, this
  //! method returns a null Handle.
  //! can expand a little the bounds of surface
  Standard_EXPORT static occ::handle<Geom2d_Curve> Curve2d(const occ::handle<Geom_Curve>&   C,
                                                           const occ::handle<Geom_Surface>& S,
                                                           const double                     UDeb,
                                                           const double                     UFin,
                                                           const double                     VDeb,
                                                           const double                     VFin);

  //! gives the 2d-curve of a 3d-curve lying on a
  //! surface (uses GeomProjLib_ProjectedCurve)
  //! If the projection needs an approximation,
  //! Precision::PApproximation() is used.
  //! WARNING: if the projection has failed, this
  //! method returns a null Handle.
  //! can expand a little the bounds of surface
  Standard_EXPORT static occ::handle<Geom2d_Curve> Curve2d(const occ::handle<Geom_Curve>&   C,
                                                           const occ::handle<Geom_Surface>& S,
                                                           const double                     UDeb,
                                                           const double                     UFin,
                                                           const double                     VDeb,
                                                           const double                     VFin,
                                                           double& Tolerance);

  //! Constructs the 3d-curve from the normal
  //! projection of the Curve <C> on the surface <S>.
  //! WARNING: if the projection has failed, returns a
  //! null Handle.
  Standard_EXPORT static occ::handle<Geom_Curve> Project(const occ::handle<Geom_Curve>&   C,
                                                         const occ::handle<Geom_Surface>& S);

  //! Constructs the 3d-curves from the projection
  //! of the curve <Curve> on the plane <Plane> along
  //! the direction <Dir>.
  //! If <KeepParametrization> is true, the parametrization
  //! of the Projected Curve <PC> will be the same as the
  //! parametrization of the initial curve <C>.
  //! It means: proj(C(u)) = PC(u) for each u.
  //! Otherwise, the parametrization may change.
  Standard_EXPORT static occ::handle<Geom_Curve> ProjectOnPlane(
    const occ::handle<Geom_Curve>& Curve,
    const occ::handle<Geom_Plane>& Plane,
    const gp_Dir&                  Dir,
    const bool                     KeepParametrization);
};
