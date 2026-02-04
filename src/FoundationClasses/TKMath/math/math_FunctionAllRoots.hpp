#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class math_FunctionWithDerivative;
class math_FunctionSample;

//! This algorithm uses a sample of the function to find
//! all intervals on which the function is null, and afterwards
//! uses the FunctionRoots algorithm to find the points
//! where the function is null outside the "null intervals".
//! Knowledge of the derivative is required.
class math_FunctionAllRoots
{
public:
  DEFINE_STANDARD_ALLOC

  //! The algorithm uses the sample to find intervals on which
  //! the function is null. An interval is found if, for at least
  //! two consecutive points of the sample, Ui and Ui+1, we get
  //! |F(Ui)|<=EpsNul and |F(Ui+1)|<=EpsNul. The real bounds of
  //! an interval are computed with the FunctionRoots.
  //! algorithm.
  //! Between two intervals, the roots of the function F are
  //! calculated using the FunctionRoots algorithm.
  Standard_EXPORT math_FunctionAllRoots(math_FunctionWithDerivative& F,
                                        const math_FunctionSample&   S,
                                        const double                 EpsX,
                                        const double                 EpsF,
                                        const double                 EpsNul);

  //! Returns True if the computation has been done successfully.
  bool IsDone() const;

  //! Returns the number of intervals on which the function
  //! is Null.
  //! An exception is raised if IsDone returns False.
  int NbIntervals() const;

  //! Returns the interval of parameter of range Index.
  //! An exception is raised if IsDone returns False;
  //! An exception is raised if Index<=0 or Index >Nbintervals.
  void GetInterval(const int Index, double& A, double& B) const;

  //! returns the State Number associated to the interval Index.
  //! An exception is raised if IsDone returns False;
  //! An exception is raised if Index<=0 or Index >Nbintervals.
  void GetIntervalState(const int Index, int& IFirst, int& ILast) const;

  //! returns the number of points where the function is Null.
  //! An exception is raised if IsDone returns False.
  int NbPoints() const;

  //! Returns the parameter of the point of range Index.
  //! An exception is raised if IsDone returns False;
  //! An exception is raised if Index<=0 or Index >NbPoints.
  double GetPoint(const int Index) const;

  //! returns the State Number associated to the point Index.
  //! An exception is raised if IsDone returns False;
  //! An exception is raised if Index<=0 or Index >Nbintervals.
  int GetPointState(const int Index) const;

  //! Prints on the stream o information on the current state
  //! of the object.
  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool                         done;
  NCollection_Sequence<double> pdeb;
  NCollection_Sequence<double> pfin;
  NCollection_Sequence<double> piso;
  NCollection_Sequence<int>    ideb;
  NCollection_Sequence<int>    ifin;
  NCollection_Sequence<int>    iiso;
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

inline bool math_FunctionAllRoots::IsDone() const
{
  return done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_FunctionAllRoots& F)
{
  F.Dump(o);
  return o;
}

inline int math_FunctionAllRoots::NbIntervals() const
{
  StdFail_NotDone_Raise_if(!done, " ");
  return pdeb.Length();
}

inline void math_FunctionAllRoots::GetInterval(const int Index, double& A, double& B) const
{
  StdFail_NotDone_Raise_if(!done, " ");
  A = pdeb.Value(Index);
  B = pfin.Value(Index);
}

inline void math_FunctionAllRoots::GetIntervalState(const int Index, int& IFirst, int& ILast) const
{
  StdFail_NotDone_Raise_if(!done, " ");
  IFirst = ideb.Value(Index);
  ILast  = ifin.Value(Index);
}

inline int math_FunctionAllRoots::NbPoints() const
{
  StdFail_NotDone_Raise_if(!done, " ");
  return piso.Length();
}

inline double math_FunctionAllRoots::GetPoint(const int Index) const
{
  StdFail_NotDone_Raise_if(!done, " ");
  return piso.Value(Index);
}

inline int math_FunctionAllRoots::GetPointState(const int Index) const
{
  StdFail_NotDone_Raise_if(!done, " ");
  return iiso.Value(Index);
}


