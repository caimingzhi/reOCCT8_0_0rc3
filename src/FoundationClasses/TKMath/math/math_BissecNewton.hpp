// Created on: 1991-03-14
// Created by: Laurent PAINNOT
// Copyright (c) 1991-1999 Matra Datavision
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

#ifndef _math_BissecNewton_HeaderFile
#define _math_BissecNewton_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Status.hpp>
#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
class math_FunctionWithDerivative;

//! This class implements a combination of Newton-Raphson and bissection
//! methods to find the root of the function between two bounds.
//! Knowledge of the derivative is required.
class math_BissecNewton
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor.
  //! @param theXTolerance - algorithm tolerance.
  Standard_EXPORT math_BissecNewton(const double theXTolerance);

  //! A combination of Newton-Raphson and bissection methods is done to find
  //! the root of the function F between the bounds Bound1 and Bound2
  //! on the function F.
  //! The tolerance required on the root is given by TolX.
  //! The solution is found when:
  //! abs(Xi - Xi-1) <= TolX and F(Xi) * F(Xi-1) <= 0
  //! The maximum number of iterations allowed is given by NbIterations.
  Standard_EXPORT void Perform(math_FunctionWithDerivative& F,
                               const double                 Bound1,
                               const double                 Bound2,
                               const int                    NbIterations = 100);

  //! This method is called at the end of each iteration to check if the
  //! solution has been found.
  //! It can be redefined in a sub-class to implement a specific test to
  //! stop the iterations.
  virtual bool IsSolutionReached(math_FunctionWithDerivative& theFunction);

  //! Tests is the root has been successfully found.
  bool IsDone() const;

  //! returns the value of the root.
  //! Exception NotDone is raised if the minimum was not found.
  double Root() const;

  //! returns the value of the derivative at the root.
  //! Exception NotDone is raised if the minimum was not found.
  double Derivative() const;

  //! returns the value of the function at the root.
  //! Exception NotDone is raised if the minimum was not found.
  double Value() const;

  //! Prints on the stream o information on the current state
  //! of the object.
  //! Is used to redefine the operator <<.
  Standard_EXPORT void Dump(Standard_OStream& o) const;

  //! Destructor
  Standard_EXPORT virtual ~math_BissecNewton();

protected:
  math_Status TheStatus;
  double      XTol;
  double      x;
  double      dx;
  double      f;
  double      df;

private:
  bool Done;
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

inline bool math_BissecNewton::IsSolutionReached(math_FunctionWithDerivative&)
{
  return std::abs(dx) <= XTol;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_BissecNewton& Bi)
{
  Bi.Dump(o);
  return o;
}

inline bool math_BissecNewton::IsDone() const
{
  return Done;
}

inline double math_BissecNewton::Root() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return x;
}

inline double math_BissecNewton::Derivative() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return df;
}

inline double math_BissecNewton::Value() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return f;
}


#endif // _math_BissecNewton_HeaderFile
