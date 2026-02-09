#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

class IGESData_IGESType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESData_IGESType();

  Standard_EXPORT IGESData_IGESType(const int atype, const int aform);

  Standard_EXPORT int Type() const;

  Standard_EXPORT int Form() const;

  Standard_EXPORT bool IsEqual(const IGESData_IGESType& another) const;

  bool operator==(const IGESData_IGESType& another) const { return IsEqual(another); }

  Standard_EXPORT void Nullify();

private:
  int thetype;
  int theform;
};
