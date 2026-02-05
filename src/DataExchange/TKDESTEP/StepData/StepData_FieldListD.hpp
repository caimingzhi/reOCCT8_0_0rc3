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

//! Describes a list of fields, in a general way
//! This basic class is for a null size list
//! Subclasses are for 1, N (fixed) or Dynamic sizes
class StepData_FieldListD : public StepData_FieldList
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a FieldListD of <nb> Fields
  Standard_EXPORT StepData_FieldListD(const int nb);

  //! Sets a new count of Fields. Former contents are lost
  Standard_EXPORT void SetNb(const int nb);

  //! Returns the count of fields. Here, returns starting <nb>
  Standard_EXPORT int NbFields() const override;

  //! Returns the field n0 <num> between 1 and NbFields (read only)
  Standard_EXPORT const StepData_Field& Field(const int num) const override;

  //! Returns the field n0 <num> between 1 and NbFields, in order to
  //! modify its content
  Standard_EXPORT StepData_Field& CField(const int num) override;

private:
  occ::handle<NCollection_HArray1<StepData_Field>> thefields;
};
