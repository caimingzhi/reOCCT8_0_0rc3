#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>

class math_Function
{
public:
  DEFINE_STANDARD_ALLOC

  virtual ~math_Function() = default;

  Standard_EXPORT virtual bool Value(const double X, double& F) = 0;

  Standard_EXPORT virtual int GetStateNumber();
};
