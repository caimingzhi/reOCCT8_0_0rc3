#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
class math_FunctionWithDerivative;

//! This class implements the computation of a root of a function of
//! a single variable which is near an initial guess using a minimization
//! algorithm.Knowledge of the derivative is required. The
//! algorithm used is the same as in
class math_FunctionRoot
{
public:
  DEFINE_STANDARD_ALLOC

  //! The Newton-Raphson method is done to find the root of the function F
  //! from the initial guess Guess.The tolerance required on
  //! the root is given by Tolerance. Iterations are stopped if
  //! the expected solution does not stay in the range A..B.
  //! The solution is found when abs(Xi - Xi-1) <= Tolerance;
  //! The maximum number of iterations allowed is given by NbIterations.
  Standard_EXPORT math_FunctionRoot(math_FunctionWithDerivative& F,
                                    const double                 Guess,
                                    const double                 Tolerance,
                                    const int                    NbIterations = 100);

  //! The Newton-Raphson method is done to find the root of the function F
  //! from the initial guess Guess.
  //! The tolerance required on the root is given by Tolerance.
  //! Iterations are stopped if the expected solution does not stay in the
  //! range A..B
  //! The solution is found when abs(Xi - Xi-1) <= Tolerance;
  //! The maximum number of iterations allowed is given by NbIterations.
  Standard_EXPORT math_FunctionRoot(math_FunctionWithDerivative& F,
                                    const double                 Guess,
                                    const double                 Tolerance,
                                    const double                 A,
                                    const double                 B,
                                    const int                    NbIterations = 100);

  //! Returns true if the computations are successful, otherwise returns false.
  bool IsDone() const;

  //! returns the value of the root.
  //! Exception NotDone is raised if the root was not found.
  double Root() const;

  //! returns the value of the derivative at the root.
  //! Exception NotDone is raised if the root was not found.
  double Derivative() const;

  //! returns the value of the function at the root.
  //! Exception NotDone is raised if the root was not found.
  double Value() const;

  //! returns the number of iterations really done on the
  //! computation of the Root.
  //! Exception NotDone is raised if the root was not found.
  int NbIterations() const;

  //! Prints on the stream o information on the current state
  //! of the object.
  //! Is used to redefine the operator <<.
  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool   Done;
  double TheRoot;
  double TheError{};
  double TheDerivative;
  int    NbIter;
};
// Copyright (c) 1997-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <StdFail_NotDone.hpp>

inline bool math_FunctionRoot::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_FunctionRoot& F)
{
  F.Dump(o);
  return o;
}

inline double math_FunctionRoot::Root() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheRoot;
}

inline double math_FunctionRoot::Derivative() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheDerivative;
}

inline double math_FunctionRoot::Value() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheError;
}

inline int math_FunctionRoot::NbIterations() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return NbIter;
}


