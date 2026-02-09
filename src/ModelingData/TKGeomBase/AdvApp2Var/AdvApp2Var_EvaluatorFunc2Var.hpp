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

class AdvApp2Var_EvaluatorFunc2Var
{
public:
  AdvApp2Var_EvaluatorFunc2Var() = default;

  virtual ~AdvApp2Var_EvaluatorFunc2Var() = default;

  virtual void Evaluate(int*    theDimension,
                        double* theUStartEnd,
                        double* theVStartEnd,
                        int*    theFavorIso,
                        double* theConstParam,
                        int*    theNbParams,
                        double* theParameters,
                        int*    theUOrder,
                        int*    theVOrder,
                        double* theResult,
                        int*    theErrorCode) const = 0;

  void operator()(int*    theDimension,
                  double* theUStartEnd,
                  double* theVStartEnd,
                  int*    theFavorIso,
                  double* theConstParam,
                  int*    theNbParams,
                  double* theParameters,
                  int*    theUOrder,
                  int*    theVOrder,
                  double* theResult,
                  int*    theErrorCode) const
  {
    Evaluate(theDimension,
             theUStartEnd,
             theVStartEnd,
             theFavorIso,
             theConstParam,
             theNbParams,
             theParameters,
             theUOrder,
             theVOrder,
             theResult,
             theErrorCode);
  }

private:
  AdvApp2Var_EvaluatorFunc2Var(const AdvApp2Var_EvaluatorFunc2Var&) = default;

  void operator=(const AdvApp2Var_EvaluatorFunc2Var&) {}
};
