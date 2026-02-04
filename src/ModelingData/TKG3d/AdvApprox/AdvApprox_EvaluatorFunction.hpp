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

// abv 01.04.2009: the C function pointer converted to a virtual class
// in order to get rid of usage of static functions and static data

//! Interface for a class implementing a function to be approximated
//! by AdvApprox_ApproxAFunction
class AdvApprox_EvaluatorFunction
{
public:
  //! Empty constructor
  AdvApprox_EvaluatorFunction() = default;

  //! Destructor should be declared as virtual
  virtual ~AdvApprox_EvaluatorFunction() = default;

  //! Function evaluation method to be defined by descendant
  virtual void Evaluate(int*    Dimension,
                        double  StartEnd[2],
                        double* Parameter,
                        int*    DerivativeRequest,
                        double* Result, // [Dimension]
                        int*    ErrorCode) = 0;

  //! Shortcut for function-call style usage
  void operator()(int*    Dimension,
                  double  StartEnd[2],
                  double* Parameter,
                  int*    DerivativeRequest,
                  double* Result, // [Dimension]
                  int*    ErrorCode)
  {
    Evaluate(Dimension, StartEnd, Parameter, DerivativeRequest, Result, ErrorCode);
  }

private:
  //! Copy constructor is declared private to forbid copying
  AdvApprox_EvaluatorFunction(const AdvApprox_EvaluatorFunction&) = default;

  //! Assignment operator is declared private to forbid copying
  void operator=(const AdvApprox_EvaluatorFunction&) {}
};

