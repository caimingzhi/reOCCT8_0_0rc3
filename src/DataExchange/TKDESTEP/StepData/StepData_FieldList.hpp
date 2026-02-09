#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
class StepData_Field;
class Interface_EntityIterator;

class StepData_FieldList
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual ~StepData_FieldList();

  Standard_EXPORT StepData_FieldList();

  Standard_EXPORT virtual int NbFields() const;

  Standard_EXPORT virtual const StepData_Field& Field(const int num) const;

  Standard_EXPORT virtual StepData_Field& CField(const int num);

  Standard_EXPORT void FillShared(Interface_EntityIterator& iter) const;
};
