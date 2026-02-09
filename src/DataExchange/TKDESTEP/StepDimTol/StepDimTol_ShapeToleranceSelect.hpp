#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepDimTol_GeometricTolerance;
class StepShape_PlusMinusTolerance;

class StepDimTol_ShapeToleranceSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepDimTol_ShapeToleranceSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepDimTol_GeometricTolerance> GeometricTolerance() const;

  Standard_EXPORT occ::handle<StepShape_PlusMinusTolerance> PlusMinusTolerance() const;
};
