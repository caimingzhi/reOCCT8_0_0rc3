#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Vector.hpp>

//! Describes the virtual functions associated with a multiple variable function.
class math_MultipleVarFunction
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the number of variables of the function
  Standard_EXPORT virtual int NbVariables() const = 0;

  //! Computes the values of the Functions <F> for the
  //! variable <X>.
  //! returns True if the computation was done successfully,
  //! otherwise false.
  Standard_EXPORT virtual bool Value(const math_Vector& X, double& F) = 0;

  //! return the state of the function corresponding to the latestt
  //! call of any methods associated to the function. This
  //! function is called by each of the algorithms described
  //! later which define the function Integer
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
  Standard_EXPORT virtual ~math_MultipleVarFunction();
};
