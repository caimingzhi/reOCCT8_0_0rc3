#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
class StepData_Field;
class Interface_EntityIterator;

//! Describes a list of fields, in a general way
//! This basic class is for a null size list
//! Subclasses are for 1, N (fixed) or Dynamic sizes
class StepData_FieldList
{
public:
  DEFINE_STANDARD_ALLOC

  //! Destructor is virtual
  Standard_EXPORT virtual ~StepData_FieldList();

  //! Creates a FieldList of 0 Field
  Standard_EXPORT StepData_FieldList();

  //! Returns the count of fields. Here, returns 0
  Standard_EXPORT virtual int NbFields() const;

  //! Returns the field n0 <num> between 1 and NbFields (read only)
  Standard_EXPORT virtual const StepData_Field& Field(const int num) const;

  //! Returns the field n0 <num> between 1 and NbFields, in order to
  //! modify its content
  Standard_EXPORT virtual StepData_Field& CField(const int num);

  //! Fills an iterator with the entities shared by <me>
  Standard_EXPORT void FillShared(Interface_EntityIterator& iter) const;
};
