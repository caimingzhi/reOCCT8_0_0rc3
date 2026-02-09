#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Vector.hpp>

class math_FunctionSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual int NbVariables() const = 0;

  Standard_EXPORT virtual int NbEquations() const = 0;

  Standard_EXPORT virtual bool Value(const math_Vector& X, math_Vector& F) = 0;

  Standard_EXPORT virtual int GetStateNumber();
  Standard_EXPORT virtual ~math_FunctionSet();
};
