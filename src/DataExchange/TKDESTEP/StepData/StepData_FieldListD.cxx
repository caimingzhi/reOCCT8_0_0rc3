

#include <Standard_OutOfRange.hpp>
#include <StepData_FieldListD.hpp>

StepData_FieldListD::StepData_FieldListD(const int nb)
{
  if (nb > 0)
    thefields = new NCollection_HArray1<StepData_Field>(1, nb);
}

void StepData_FieldListD::SetNb(const int nb)
{
  thefields.Nullify();
  if (nb > 0)
    thefields = new NCollection_HArray1<StepData_Field>(1, nb);
}

int StepData_FieldListD::NbFields() const
{
  return (thefields.IsNull() ? 0 : thefields->Length());
}

const StepData_Field& StepData_FieldListD::Field(const int num) const
{
  if (thefields.IsNull())
    throw Standard_OutOfRange("StepData_FieldListD::Field");
  return thefields->Value(num);
}

StepData_Field& StepData_FieldListD::CField(const int num)
{
  if (thefields.IsNull())
    throw Standard_OutOfRange("StepData_FieldListD::Field");
  return thefields->ChangeValue(num);
}
