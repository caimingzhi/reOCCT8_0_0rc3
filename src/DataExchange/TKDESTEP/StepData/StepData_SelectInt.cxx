

#include <Standard_Type.hpp>
#include <StepData_SelectInt.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepData_SelectInt, StepData_SelectMember)

StepData_SelectInt::StepData_SelectInt()
{
  thekind = 0;
  theval  = 0;
}

int StepData_SelectInt::Kind() const
{
  return thekind;
}

void StepData_SelectInt::SetKind(const int kind)
{
  thekind = kind;
}

int StepData_SelectInt::Int() const
{
  return theval;
}

void StepData_SelectInt::SetInt(const int val)
{
  theval = val;
}
