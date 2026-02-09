

#include <Standard_OutOfRange.hpp>
#include <StepData_FieldList1.hpp>

StepData_FieldList1::StepData_FieldList1() = default;

int StepData_FieldList1::NbFields() const
{
  return 1;
}

const StepData_Field& StepData_FieldList1::Field(const int num) const
{
  if (num != 1)
    throw Standard_OutOfRange("StepData_FieldList1 : Field");
  return thefield;
}

StepData_Field& StepData_FieldList1::CField(const int num)
{
  if (num != 1)
    throw Standard_OutOfRange("StepData_FieldList1 : CField");
  return thefield;
}
