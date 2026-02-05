#include <Standard_Transient.hpp>
#include <StepDimTol_GeometricTolerance.hpp>
#include <StepDimTol_ShapeToleranceSelect.hpp>
#include <StepShape_PlusMinusTolerance.hpp>

//=================================================================================================

StepDimTol_ShapeToleranceSelect::StepDimTol_ShapeToleranceSelect() = default;

//=================================================================================================

int StepDimTol_ShapeToleranceSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepDimTol_GeometricTolerance)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepShape_PlusMinusTolerance)))
    return 2;
  return 0;
}

//=================================================================================================

occ::handle<StepDimTol_GeometricTolerance> StepDimTol_ShapeToleranceSelect::GeometricTolerance()
  const
{
  return occ::down_cast<StepDimTol_GeometricTolerance>(Value());
}

//=================================================================================================

occ::handle<StepShape_PlusMinusTolerance> StepDimTol_ShapeToleranceSelect::PlusMinusTolerance()
  const
{
  return occ::down_cast<StepShape_PlusMinusTolerance>(Value());
}
