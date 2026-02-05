#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_OStream.hpp>

//! This class implements the solutions of the equation
//! a*std::cos(x)*std::cos(x) + 2*b*std::cos(x)*Sin(x) + c*std::cos(x) + d*Sin(x) + e
//! The degree of this equation can be 4, 3 or 2.
class math_TrigonometricFunctionRoots
{
public:
  DEFINE_STANDARD_ALLOC

  //! Given coefficients a, b, c, d , e, this constructor
  //! performs the resolution of the equation above.
  //! The solutions must be contained in [InfBound, SupBound].
  //! InfBound and SupBound can be set by default to 0 and 2*PI.
  Standard_EXPORT math_TrigonometricFunctionRoots(const double A,
                                                  const double B,
                                                  const double C,
                                                  const double D,
                                                  const double E,
                                                  const double InfBound,
                                                  const double SupBound);

  //! Given the two coefficients d and e, it performs
  //! the resolution of d*sin(x) + e = 0.
  //! The solutions must be contained in [InfBound, SupBound].
  //! InfBound and SupBound can be set by default to 0 and 2*PI.
  Standard_EXPORT math_TrigonometricFunctionRoots(const double D,
                                                  const double E,
                                                  const double InfBound,
                                                  const double SupBound);

  //! Given the three coefficients c, d and e, it performs
  //! the resolution of c*std::cos(x) + d*sin(x) + e = 0.
  //! The solutions must be contained in [InfBound, SupBound].
  //! InfBound and SupBound can be set by default to 0 and 2*PI.
  Standard_EXPORT math_TrigonometricFunctionRoots(const double C,
                                                  const double D,
                                                  const double E,
                                                  const double InfBound,
                                                  const double SupBound);

  //! Returns true if the computations are successful, otherwise returns false.
  bool IsDone() const;

  //! Returns true if there is an infinity of roots, otherwise returns false.
  bool InfiniteRoots() const;

  //! Returns the solution of range Index.
  //! An exception is raised if NotDone.
  //! An exception is raised if Index>NbSolutions.
  //! An exception is raised if there is an infinity of solutions.
  double Value(const int Index) const;

  //! Returns the number of solutions found.
  //! An exception is raised if NotDone.
  //! An exception is raised if there is an infinity of solutions.
  int NbSolutions() const;

  //! Prints information on the current state of the object.
  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  //! is used by the constructors above.
  Standard_EXPORT void Perform(const double A,
                               const double B,
                               const double C,
                               const double D,
                               const double E,
                               const double InfBound,
                               const double SupBound);

private:
  int                        NbSol;
  NCollection_Array1<double> Sol;
  bool                       InfiniteStatus;
  bool                       Done;
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

// math_TrigonometricFunctionRoots_1.hpp

#include <StdFail_InfiniteSolutions.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>

inline bool math_TrigonometricFunctionRoots::InfiniteRoots() const
{
  return InfiniteStatus;
}

inline bool math_TrigonometricFunctionRoots::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_TrigonometricFunctionRoots& T)
{
  T.Dump(o);
  return o;
}

inline double math_TrigonometricFunctionRoots::Value(const int Index) const
{
  StdFail_InfiniteSolutions_Raise_if(InfiniteStatus, " ");
  StdFail_NotDone_Raise_if(!Done, " ");
  Standard_OutOfRange_Raise_if(Index > NbSol, " ");
  return Sol(Index);
}

inline int math_TrigonometricFunctionRoots::NbSolutions() const
{
  StdFail_InfiniteSolutions_Raise_if(InfiniteStatus, " ");
  StdFail_NotDone_Raise_if(!Done, " ");
  return NbSol;
}
