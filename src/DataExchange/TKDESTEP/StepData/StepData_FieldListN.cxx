

#include <StepData_FieldListN.hpp>

StepData_FieldListN::StepData_FieldListN(const int nb)
    : thefields((nb == 0 ? 0 : 1), nb)
{
}

int StepData_FieldListN::NbFields() const
{
  return thefields.Upper();
}

const StepData_Field& StepData_FieldListN::Field(const int num) const
{
  return thefields.Value(num);
}

StepData_Field& StepData_FieldListN::CField(const int num)
{
  return thefields.ChangeValue(num);
}
