#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepGeom_CompositeCurve;
class StepShape_Path;

class StepVisual_PathOrCompositeCurve : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_PathOrCompositeCurve();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepGeom_CompositeCurve> CompositeCurve() const;

  Standard_EXPORT occ::handle<StepShape_Path> Path() const;
};
