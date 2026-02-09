

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepGeom_Direction.hpp>
#include <StepGeom_Vector.hpp>
#include <StepGeom_VectorOrDirection.hpp>

StepGeom_VectorOrDirection::StepGeom_VectorOrDirection() = default;

int StepGeom_VectorOrDirection::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Vector)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Direction)))
    return 2;
  return 0;
}

occ::handle<StepGeom_Vector> StepGeom_VectorOrDirection::Vector() const
{
  return GetCasted(StepGeom_Vector, Value());
}

occ::handle<StepGeom_Direction> StepGeom_VectorOrDirection::Direction() const
{
  return GetCasted(StepGeom_Direction, Value());
}
