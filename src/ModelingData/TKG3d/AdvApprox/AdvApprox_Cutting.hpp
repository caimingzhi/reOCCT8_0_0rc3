#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>

class AdvApprox_Cutting
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual ~AdvApprox_Cutting();

  Standard_EXPORT virtual bool Value(const double a,
                                     const double b,
                                     double&      cuttingvalue) const = 0;
};
