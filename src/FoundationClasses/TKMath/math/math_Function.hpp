#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>

//! This abstract class describes the virtual functions
//! associated with a Function of a single variable.
class math_Function
{
public:
  DEFINE_STANDARD_ALLOC

  //! Virtual destructor, for safe inheritance
  virtual ~math_Function() = default;

  //! Computes the value of the function <F> for a given value of
  //! variable <X>.
  //! returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT virtual bool Value(const double X, double& F) = 0;

  //! returns the state of the function corresponding to the
  //! latest call of any methods associated with the function.
  //! This function is called by each of the algorithms
  //! described later which defined the function Integer
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
};

