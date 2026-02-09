#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <StepData_Field.hpp>
#include <StepData_FieldList.hpp>
#include <Standard_Integer.hpp>

class StepData_FieldList1 : public StepData_FieldList
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepData_FieldList1();

  Standard_EXPORT int NbFields() const override;

  Standard_EXPORT const StepData_Field& Field(const int num) const override;

  Standard_EXPORT StepData_Field& CField(const int num) override;

private:
  StepData_Field thefield;
};
