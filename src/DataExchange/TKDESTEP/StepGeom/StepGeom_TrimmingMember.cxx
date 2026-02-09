

#include <Standard_Type.hpp>
#include <StepGeom_TrimmingMember.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_TrimmingMember, StepData_SelectReal)

StepGeom_TrimmingMember::StepGeom_TrimmingMember() = default;

bool StepGeom_TrimmingMember::HasName() const
{
  return true;
}

const char* StepGeom_TrimmingMember::Name() const
{
  return "PARAMETER_VALUE";
}

bool StepGeom_TrimmingMember::SetName(const char*)
{
  return true;
}
