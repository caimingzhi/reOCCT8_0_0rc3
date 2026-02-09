#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IGESData_DefType.hpp>

class IGESData_DefSwitch
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESData_DefSwitch();

  Standard_EXPORT void SetVoid();

  Standard_EXPORT void SetReference();

  Standard_EXPORT void SetRank(const int val);

  Standard_EXPORT IGESData_DefType DefType() const;

  Standard_EXPORT int Value() const;

private:
  int theval;
};
