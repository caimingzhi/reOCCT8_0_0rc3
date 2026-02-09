#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_Field.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepData_FieldList.hpp>
#include <Standard_Integer.hpp>
class StepData_Field;

class StepData_FieldListD : public StepData_FieldList
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepData_FieldListD(const int nb);

  Standard_EXPORT void SetNb(const int nb);

  Standard_EXPORT int NbFields() const override;

  Standard_EXPORT const StepData_Field& Field(const int num) const override;

  Standard_EXPORT StepData_Field& CField(const int num) override;

private:
  occ::handle<NCollection_HArray1<StepData_Field>> thefields;
};
