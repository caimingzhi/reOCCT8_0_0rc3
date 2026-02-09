#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_Factors.hpp>

#include <Standard_Boolean.hpp>

class GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT bool IsDone() const;

protected:
  bool done;
};
