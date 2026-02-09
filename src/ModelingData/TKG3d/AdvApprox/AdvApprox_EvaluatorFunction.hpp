#pragma once

#include <stddef.h>

#include <stdlib.h>

#include <Standard_Macro.hpp>

#include <Standard_Boolean.hpp>

#include <Standard_Integer.hpp>

#include <Standard_Real.hpp>

#include <Standard_Character.hpp>

#include <Standard_ExtCharacter.hpp>

#include <Standard_CString.hpp>

class AdvApprox_EvaluatorFunction
{
public:
  AdvApprox_EvaluatorFunction() = default;

  virtual ~AdvApprox_EvaluatorFunction() = default;

  virtual void Evaluate(int*    Dimension,
                        double  StartEnd[2],
                        double* Parameter,
                        int*    DerivativeRequest,
                        double* Result,
                        int*    ErrorCode) = 0;

  void operator()(int*    Dimension,
                  double  StartEnd[2],
                  double* Parameter,
                  int*    DerivativeRequest,
                  double* Result,
                  int*    ErrorCode)
  {
    Evaluate(Dimension, StartEnd, Parameter, DerivativeRequest, Result, ErrorCode);
  }

private:
  AdvApprox_EvaluatorFunction(const AdvApprox_EvaluatorFunction&) = default;

  void operator=(const AdvApprox_EvaluatorFunction&) {}
};
