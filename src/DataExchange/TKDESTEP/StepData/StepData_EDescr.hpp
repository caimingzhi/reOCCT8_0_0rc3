#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepData_Described;

class StepData_EDescr : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool Matches(const char* steptype) const = 0;

  Standard_EXPORT virtual bool IsComplex() const = 0;

  Standard_EXPORT virtual occ::handle<StepData_Described> NewEntity() const = 0;

  DEFINE_STANDARD_RTTIEXT(StepData_EDescr, Standard_Transient)
};
