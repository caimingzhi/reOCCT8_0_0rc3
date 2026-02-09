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

class GeomProjLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Geom2d_Curve> Curve2d(const occ::handle<Geom_Curve>&   C,
                                                           const double                     First,
                                                           const double                     Last,
                                                           const occ::handle<Geom_Surface>& S,
                                                           const double                     UFirst,
                                                           const double                     ULast,
                                                           const double                     VFirst,
                                                           const double                     VLast,
                                                           double& Tolerance);

  Standard_EXPORT static occ::handle<Geom2d_Curve> Curve2d(const occ::handle<Geom_Curve>&   C,
                                                           const double                     First,
                                                           const double                     Last,
                                                           const occ::handle<Geom_Surface>& S,
                                                           double& Tolerance);

  Standard_EXPORT static occ::handle<Geom2d_Curve> Curve2d(const occ::handle<Geom_Curve>&   C,
                                                           const double                     First,
                                                           const double                     Last,
                                                           const occ::handle<Geom_Surface>& S);

  Standard_EXPORT static occ::handle<Geom2d_Curve> Curve2d(const occ::handle<Geom_Curve>&   C,
                                                           const occ::handle<Geom_Surface>& S);

  Standard_EXPORT static occ::handle<Geom2d_Curve> Curve2d(const occ::handle<Geom_Curve>&   C,
                                                           const occ::handle<Geom_Surface>& S,
                                                           const double                     UDeb,
                                                           const double                     UFin,
                                                           const double                     VDeb,
                                                           const double                     VFin);

  Standard_EXPORT static occ::handle<Geom2d_Curve> Curve2d(const occ::handle<Geom_Curve>&   C,
                                                           const occ::handle<Geom_Surface>& S,
                                                           const double                     UDeb,
                                                           const double                     UFin,
                                                           const double                     VDeb,
                                                           const double                     VFin,
                                                           double& Tolerance);

  Standard_EXPORT static occ::handle<Geom_Curve> Project(const occ::handle<Geom_Curve>&   C,
                                                         const occ::handle<Geom_Surface>& S);

  Standard_EXPORT static occ::handle<Geom_Curve> ProjectOnPlane(
    const occ::handle<Geom_Curve>& Curve,
    const occ::handle<Geom_Plane>& Plane,
    const gp_Dir&                  Dir,
    const bool                     KeepParametrization);
};
