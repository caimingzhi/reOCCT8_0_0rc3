

#include <StepData_SelectArrReal.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepData_SelectArrReal, StepData_SelectNamed)

#define myKindArrReal 8

StepData_SelectArrReal::StepData_SelectArrReal() = default;

int StepData_SelectArrReal::Kind() const
{
  return myKindArrReal;
}

occ::handle<NCollection_HArray1<double>> StepData_SelectArrReal::ArrReal() const
{
  return theArr;
}

void StepData_SelectArrReal::SetArrReal(const occ::handle<NCollection_HArray1<double>>& arr)
{
  theArr = arr;
}
