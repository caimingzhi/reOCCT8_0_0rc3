#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class math_FunctionWithDerivative;

//! This class implements an algorithm which finds all the real roots of
//! a function with derivative within a given range.
//! Knowledge of the derivative is required.
class math_FunctionRoots
{
public:
  DEFINE_STANDARD_ALLOC

  //! Calculates all the real roots of a function F-K within the range
  //! A..B. without conditions on A and B
  //! A solution X is found when
  //! abs(Xi - Xi-1) <= Epsx and abs(F(Xi)-K) <= EpsF.
  //! The function is considered as null between A and B if
  //! abs(F-K) <= EpsNull within this range.
  Standard_EXPORT math_FunctionRoots(math_FunctionWithDerivative& F,
                                     const double                 A,
                                     const double                 B,
                                     const int                    NbSample,
                                     const double                 EpsX    = 0.0,
                                     const double                 EpsF    = 0.0,
                                     const double                 EpsNull = 0.0,
                                     const double                 K       = 0.0);

  //! Returns true if the computations are successful, otherwise returns false.
  bool IsDone() const;

  //! returns true if the function is considered as null between A and B.
  //! Exceptions
  //! StdFail_NotDone if the algorithm fails (and IsDone returns false).
  bool IsAllNull() const;

  //! Returns the number of solutions found.
  //! Exceptions
  //! StdFail_NotDone if the algorithm fails (and IsDone returns false).
  int NbSolutions() const;

  //! Returns the Nth value of the root of function F.
  //! Exceptions
  //! StdFail_NotDone if the algorithm fails (and IsDone returns false).
  double Value(const int Nieme) const;

  //! returns the StateNumber of the Nieme root.
  //! Exception RangeError is raised if Nieme is < 1
  //! or Nieme > NbSolutions.
  int StateNumber(const int Nieme) const;

  //! Prints on the stream o information on the current state
  //! of the object.
  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool                         Done;
  bool                         AllNull;
  NCollection_Sequence<double> Sol;
  NCollection_Sequence<int>    NbStateSol;
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
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>

inline bool math_FunctionRoots::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_FunctionRoots& F)
{
  F.Dump(o);
  return o;
}

inline bool math_FunctionRoots::IsAllNull() const
{

  StdFail_NotDone_Raise_if(!Done, " ");
  return AllNull;
}

inline int math_FunctionRoots::NbSolutions() const
{

  StdFail_NotDone_Raise_if(!Done, " ");
  return Sol.Length();
}

inline double math_FunctionRoots::Value(const int Nieme) const
{

  StdFail_NotDone_Raise_if(!Done, " ");
  return Sol.Value(Nieme);
}

inline int math_FunctionRoots::StateNumber(const int Nieme) const
{

  StdFail_NotDone_Raise_if(!Done, " ");
  return NbStateSol.Value(Nieme);
}


