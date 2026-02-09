

#include <Standard_Type.hpp>
#include <StepBasic_SizeMember.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SizeMember, StepData_SelectReal)

StepBasic_SizeMember::StepBasic_SizeMember() = default;

bool StepBasic_SizeMember::HasName() const
{
  return true;
}

const char* StepBasic_SizeMember::Name() const
{
  return "POSITIVE_LENGTH_MEASURE";
}

bool StepBasic_SizeMember::SetName(const char*)
{
  return true;
}
