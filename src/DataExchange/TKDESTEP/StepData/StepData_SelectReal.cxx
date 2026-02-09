

#include <Standard_Type.hpp>
#include <StepData_SelectReal.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepData_SelectReal, StepData_SelectMember)

#define KindReal 5

StepData_SelectReal::StepData_SelectReal()
{
  theval = 0.0;
}

int StepData_SelectReal::Kind() const
{
  return KindReal;
}

double StepData_SelectReal::Real() const
{
  return theval;
}

void StepData_SelectReal::SetReal(const double val)
{
  theval = val;
}
