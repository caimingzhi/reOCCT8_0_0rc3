#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepGeom_Pcurve;
class StepGeom_SurfaceCurve;
class StepGeom_CompositeCurveOnSurface;

class StepGeom_CurveOnSurface : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepGeom_CurveOnSurface();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepGeom_Pcurve> Pcurve() const;

  Standard_EXPORT occ::handle<StepGeom_SurfaceCurve> SurfaceCurve() const;

  Standard_EXPORT occ::handle<StepGeom_CompositeCurveOnSurface> CompositeCurveOnSurface() const;
};
