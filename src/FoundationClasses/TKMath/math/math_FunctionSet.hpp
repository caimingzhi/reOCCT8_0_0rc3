#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Vector.hpp>

//! This abstract class describes the virtual functions associated to
//! a set on N Functions of M independent variables.
class math_FunctionSet
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the number of variables of the function.
  Standard_EXPORT virtual int NbVariables() const = 0;

  //! Returns the number of equations of the function.
  Standard_EXPORT virtual int NbEquations() const = 0;

  //! Computes the values <F> of the functions for the
  //! variable <X>.
  //! returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT virtual bool Value(const math_Vector& X, math_Vector& F) = 0;

  //! Returns the state of the function corresponding to the
  //! latestcall of any methods associated with the function.
  //! This function is called by each of the algorithms
  //! described later which define the function Integer
  //! Algorithm::StateNumber(). The algorithm has the
  //! responsibility to call this function when it has found
  //! a solution (i.e. a root or a minimum) and has to maintain
  //! the association between the solution found and this
  //! StateNumber.
  //! Byu default, this method returns 0 (which means for the
  //! algorithm: no state has been saved). It is the
  //! responsibility of the programmer to decide if he needs
  //! to save the current state of the function and to return
  //! an Integer that allows retrieval of the state.
  Standard_EXPORT virtual int GetStateNumber();
  Standard_EXPORT virtual ~math_FunctionSet();
};
