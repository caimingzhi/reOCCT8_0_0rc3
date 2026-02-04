#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_Vector.hpp>
#include <Standard_Integer.hpp>
#include <math_Status.hpp>
#include <math_Matrix.hpp>
#include <Standard_OStream.hpp>
class math_MultipleVarFunction;

//! This class implements the Powell method to find the minimum of
//! function of multiple variables (the gradient does not have to be known).
class math_Powell
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor. Initialize new entity.
  Standard_EXPORT math_Powell(const math_MultipleVarFunction& theFunction,
                              const double                    theTolerance,
                              const int                       theNbIterations = 200,
                              const double                    theZEPS         = 1.0e-12);

  //! Destructor
  Standard_EXPORT virtual ~math_Powell();

  //! Computes Powell minimization on the function F given
  //! theStartingPoint, and an initial matrix theStartingDirection
  //! whose columns contain the initial set of directions.
  //! The solution F = Fi is found when:
  //! 2.0 * abs(Fi - Fi-1) =< Tolerance * (abs(Fi) + abs(Fi-1) + ZEPS).
  Standard_EXPORT void Perform(math_MultipleVarFunction& theFunction,
                               const math_Vector&        theStartingPoint,
                               const math_Matrix&        theStartingDirections);

  //! Solution F = Fi is found when:
  //! 2.0 * abs(Fi - Fi-1) <= Tolerance * (abs(Fi) + abs(Fi-1)) + ZEPS.
  //! The maximum number of iterations allowed is given by NbIterations.
  virtual bool IsSolutionReached(math_MultipleVarFunction& theFunction);

  //! Returns true if the computations are successful, otherwise returns false.
  bool IsDone() const;

  //! returns the location vector of the minimum.
  //! Exception NotDone is raised if the minimum was not found.
  const math_Vector& Location() const;

  //! outputs the location vector of the minimum in Loc.
  //! Exception NotDone is raised if the minimum was not found.
  //! Exception DimensionError is raised if the range of Loc is not
  //! equal to the range of the StartingPoint.
  void Location(math_Vector& Loc) const;

  //! Returns the value of the minimum.
  //! Exception NotDone is raised if the minimum was not found.
  double Minimum() const;

  //! Returns the number of iterations really done during the
  //! computation of the minimum.
  //! Exception NotDone is raised if the minimum was not found.
  int NbIterations() const;

  //! Prints information on the current state of the object.
  //! Is used to redefine the operator <<.
  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  math_Vector TheLocation;
  double      TheMinimum;
  double      TheLocationError;
  double      PreviousMinimum;
  double      XTol;
  double      EPSZ;

private:
  bool        Done;
  int         Iter;
  math_Status TheStatus;
  math_Matrix TheDirections;
  int         State;
  int         Itermax;
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
#include <math_Vector.hpp>

inline bool math_Powell::IsSolutionReached(math_MultipleVarFunction&)
{
  return 2.0 * fabs(PreviousMinimum - TheMinimum)
         <= XTol * (fabs(PreviousMinimum) + fabs(TheMinimum) + EPSZ);
}

inline bool math_Powell::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_Powell& P)
{
  P.Dump(o);
  return o;
}

inline const math_Vector& math_Powell::Location() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheLocation;
}

inline void math_Powell::Location(math_Vector& Loc) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Loc = TheLocation;
}

inline double math_Powell::Minimum() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return TheMinimum;
}

inline int math_Powell::NbIterations() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Iter;
}


