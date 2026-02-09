#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IGESToBRep_CurveAndSurface.hpp>
class Geom_Surface;
class IGESData_IGESEntity;
class Geom_Plane;
class IGESSolid_PlaneSurface;
class Geom_CylindricalSurface;
class IGESSolid_CylindricalSurface;
class Geom_ConicalSurface;
class IGESSolid_ConicalSurface;
class Geom_SphericalSurface;
class IGESSolid_SphericalSurface;
class Geom_ToroidalSurface;
class IGESSolid_ToroidalSurface;
class Geom_BSplineSurface;
class IGESGeom_SplineSurface;
class IGESGeom_BSplineSurface;

class IGESToBRep_BasicSurface : public IGESToBRep_CurveAndSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESToBRep_BasicSurface();

  Standard_EXPORT IGESToBRep_BasicSurface(const IGESToBRep_CurveAndSurface& CS);

  Standard_EXPORT IGESToBRep_BasicSurface(const double eps,
                                          const double epsGeom,
                                          const double epsCoeff,
                                          const bool   mode,
                                          const bool   modeapprox,
                                          const bool   optimized);

  Standard_EXPORT occ::handle<Geom_Surface> TransferBasicSurface(
    const occ::handle<IGESData_IGESEntity>& start);

  Standard_EXPORT occ::handle<Geom_Plane> TransferPlaneSurface(
    const occ::handle<IGESSolid_PlaneSurface>& start);

  Standard_EXPORT occ::handle<Geom_CylindricalSurface> TransferRigthCylindricalSurface(
    const occ::handle<IGESSolid_CylindricalSurface>& start);

  Standard_EXPORT occ::handle<Geom_ConicalSurface> TransferRigthConicalSurface(
    const occ::handle<IGESSolid_ConicalSurface>& start);

  Standard_EXPORT occ::handle<Geom_SphericalSurface> TransferSphericalSurface(
    const occ::handle<IGESSolid_SphericalSurface>& start);

  Standard_EXPORT occ::handle<Geom_ToroidalSurface> TransferToroidalSurface(
    const occ::handle<IGESSolid_ToroidalSurface>& start);

  Standard_EXPORT occ::handle<Geom_BSplineSurface> TransferSplineSurface(
    const occ::handle<IGESGeom_SplineSurface>& start);

  Standard_EXPORT occ::handle<Geom_BSplineSurface> TransferBSplineSurface(
    const occ::handle<IGESGeom_BSplineSurface>& start);
};
