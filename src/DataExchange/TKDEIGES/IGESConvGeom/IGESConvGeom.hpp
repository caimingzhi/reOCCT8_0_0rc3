#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
class IGESGeom_SplineCurve;
class Geom_BSplineCurve;
class Geom2d_BSplineCurve;
class IGESGeom_SplineSurface;
class Geom_BSplineSurface;

class IGESConvGeom
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static int SplineCurveFromIGES(const occ::handle<IGESGeom_SplineCurve>& igesent,
                                                 const double                             epscoef,
                                                 const double                             epsgeom,
                                                 occ::handle<Geom_BSplineCurve>&          result);

  Standard_EXPORT static int IncreaseCurveContinuity(const occ::handle<Geom_BSplineCurve>& curve,
                                                     const double                          epsgeom,
                                                     const int continuity = 2);

  Standard_EXPORT static int IncreaseCurveContinuity(const occ::handle<Geom2d_BSplineCurve>& curve,
                                                     const double epsgeom,
                                                     const int    continuity = 2);

  Standard_EXPORT static int SplineSurfaceFromIGES(
    const occ::handle<IGESGeom_SplineSurface>& igesent,
    const double                               epscoef,
    const double                               epsgeom,
    occ::handle<Geom_BSplineSurface>&          result);

  Standard_EXPORT static int IncreaseSurfaceContinuity(
    const occ::handle<Geom_BSplineSurface>& surface,
    const double                            epsgeom,
    const int                               continuity = 2);
};
