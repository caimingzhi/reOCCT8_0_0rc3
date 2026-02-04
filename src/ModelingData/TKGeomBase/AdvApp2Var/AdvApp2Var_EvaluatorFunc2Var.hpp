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

// History - the C function pointer converted to a virtual class
// in order to get rid of usage of static functions and static data
class AdvApp2Var_EvaluatorFunc2Var
{
public:
  //! Empty constructor
  AdvApp2Var_EvaluatorFunc2Var() = default;

  //! Destructor should be declared as virtual
  virtual ~AdvApp2Var_EvaluatorFunc2Var() = default;

  //! Function evaluation method to be defined by descendant
  virtual void Evaluate(int*    theDimension,
                        double* theUStartEnd,  //!< First and last parameters in U
                        double* theVStartEnd,  //!< First and last parameters in V
                        int*    theFavorIso,   //!< Choice of constante, 1 for U, 2 for V
                        double* theConstParam, //!< Value of constant parameter
                        int*    theNbParams,   //!< Number of parameters N
                        double* theParameters, //!< Values of parameters,
                        int*    theUOrder,     //!< Derivative Request in U
                        int*    theVOrder,     //!< Derivative Request in V
                        double* theResult,     //!< Result[Dimension,N]
                        int*    theErrorCode) const = 0;

  //! Shortcut for function-call style usage
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
  //! Copy constructor is declared private to forbid copying
  AdvApp2Var_EvaluatorFunc2Var(const AdvApp2Var_EvaluatorFunc2Var&) = default;

  //! Assignment operator is declared private to forbid copying
  void operator=(const AdvApp2Var_EvaluatorFunc2Var&) {}
};

