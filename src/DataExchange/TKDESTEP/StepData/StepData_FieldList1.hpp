#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <StepData_Field.hpp>
#include <StepData_FieldList.hpp>
#include <Standard_Integer.hpp>

//! Describes a list of ONE field
class StepData_FieldList1 : public StepData_FieldList
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a FieldList of 1 Field
  Standard_EXPORT StepData_FieldList1();

  //! Returns the count of fields. Here, returns 1
  Standard_EXPORT int NbFields() const override;

  //! Returns the field n0 <num> between 1 and NbFields (read only)
  Standard_EXPORT const StepData_Field& Field(const int num) const override;

  //! Returns the field n0 <num> between 1 and NbFields, in order to
  //! modify its content
  Standard_EXPORT StepData_Field& CField(const int num) override;

private:
  StepData_Field thefield;
};

