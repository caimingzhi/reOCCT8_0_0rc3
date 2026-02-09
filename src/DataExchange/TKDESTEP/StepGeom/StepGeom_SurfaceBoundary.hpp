#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepGeom_BoundaryCurve;
class StepGeom_DegeneratePcurve;

class StepGeom_SurfaceBoundary : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepGeom_SurfaceBoundary();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepGeom_BoundaryCurve> BoundaryCurve() const;

  Standard_EXPORT occ::handle<StepGeom_DegeneratePcurve> DegeneratePcurve() const;
};
