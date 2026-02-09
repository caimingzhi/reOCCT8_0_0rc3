#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_Field.hpp>
#include <NCollection_Array1.hpp>
#include <StepData_FieldList.hpp>
class StepData_Field;

class StepData_FieldListN : public StepData_FieldList
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepData_FieldListN(const int nb);

  Standard_EXPORT int NbFields() const override;

  Standard_EXPORT const StepData_Field& Field(const int num) const override;

  Standard_EXPORT StepData_Field& CField(const int num) override;

private:
  NCollection_Array1<StepData_Field> thefields;
};
