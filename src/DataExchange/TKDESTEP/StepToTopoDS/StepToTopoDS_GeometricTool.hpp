#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepGeom_SurfaceCurve;
class StepGeom_Surface;
class StepGeom_Pcurve;
class StepShape_Edge;
class StepShape_EdgeLoop;
class Geom_Curve;

//! This class contains some algorithmic services
//! specific to the mapping STEP to CAS.CADE
class StepToTopoDS_GeometricTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static int PCurve(const occ::handle<StepGeom_SurfaceCurve>& SC,
                                    const occ::handle<StepGeom_Surface>&      S,
                                    occ::handle<StepGeom_Pcurve>&             PC,
                                    const int                                 last = 0);

  Standard_EXPORT static bool IsSeamCurve(const occ::handle<StepGeom_SurfaceCurve>& SC,
                                          const occ::handle<StepGeom_Surface>&      S,
                                          const occ::handle<StepShape_Edge>&        E,
                                          const occ::handle<StepShape_EdgeLoop>&    EL);

  Standard_EXPORT static bool IsLikeSeam(const occ::handle<StepGeom_SurfaceCurve>& SC,
                                         const occ::handle<StepGeom_Surface>&      S,
                                         const occ::handle<StepShape_Edge>&        E,
                                         const occ::handle<StepShape_EdgeLoop>&    EL);

  Standard_EXPORT static bool UpdateParam3d(const occ::handle<Geom_Curve>& C,
                                            double&                        w1,
                                            double&                        w2,
                                            const double                   preci);
};

