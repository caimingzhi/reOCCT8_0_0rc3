#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
class math_Function;

//! Given two distinct initial points, BracketMinimum
//! implements the computation of three points (a, b, c) which
//! bracket the minimum of the function and verify A less than
//! B, B less than C and F(B) less than F(A), F(B) less than F(C).
//!
//! The algorithm supports conditional optimization. By default no limits are
//! applied to the parameter change. The method SetLimits defines the allowed range.
//! If no minimum is found in limits then IsDone() will return false. The user
//! is in charge of providing A and B to be in limits.
class math_BracketMinimum
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor preparing A and B parameters only. It does not perform the job.
  math_BracketMinimum(const double A, const double B);

  //! Given two initial values this class computes a
  //! bracketing triplet of abscissae Ax, Bx, Cx
  //! (such that Bx is between Ax and Cx, F(Bx) is
  //! less than both F(Bx) and F(Cx)) the Brent minimization is done
  //! on the function F.
  Standard_EXPORT math_BracketMinimum(math_Function& F, const double A, const double B);

  //! Given two initial values this class computes a
  //! bracketing triplet of abscissae Ax, Bx, Cx
  //! (such that Bx is between Ax and Cx, F(Bx) is
  //! less than both F(Bx) and F(Cx)) the Brent minimization is done
  //! on the function F.
  //! This constructor has to be used if F(A) is known.
  Standard_EXPORT math_BracketMinimum(math_Function& F,
                                      const double   A,
                                      const double   B,
                                      const double   FA);

  //! Given two initial values this class computes a
  //! bracketing triplet of abscissae Ax, Bx, Cx
  //! (such that Bx is between Ax and Cx, F(Bx) is
  //! less than both F(Bx) and F(Cx)) the Brent minimization is done
  //! on the function F.
  //! This constructor has to be used if F(A) and F(B) are known.
  Standard_EXPORT math_BracketMinimum(math_Function& F,
                                      const double   A,
                                      const double   B,
                                      const double   FA,
                                      const double   FB);

  //! Set limits of the parameter. By default no limits are applied to the parameter change.
  //! If no minimum is found in limits then IsDone() will return false. The user
  //! is in charge of providing A and B to be in limits.
  void SetLimits(const double theLeft, const double theRight);

  //! Set function value at A
  void SetFA(const double theValue);

  //! Set function value at B
  void SetFB(const double theValue);

  //! The method performing the job. It is called automatically by constructors with the function.
  Standard_EXPORT void Perform(math_Function& F);

  //! Returns true if the computations are successful, otherwise returns false.
  bool IsDone() const;

  //! Returns the bracketed triplet of abscissae.
  //! Exceptions
  //! StdFail_NotDone if the algorithm fails (and IsDone returns false).
  Standard_EXPORT void Values(double& A, double& B, double& C) const;

  //! returns the bracketed triplet function values.
  //! Exceptions
  //! StdFail_NotDone if the algorithm fails (and IsDone returns false).
  Standard_EXPORT void FunctionValues(double& FA, double& FB, double& FC) const;

  //! Prints on the stream o information on the current state
  //! of the object.
  //! Is used to redefine the operator <<.
  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  //! Limit the given value to become within the range [myLeft, myRight].
  double Limited(const double theValue) const;

  //! Limit the value of C (see Limited) and compute the function in it.
  //! If C occurs to be between A and B then swap parameters and function
  //! values of B and C.
  //! Return false in the case of C becomes equal to B or function calculation
  //! failure.
  bool LimitAndMayBeSwap(math_Function& F,
                         const double   theA,
                         double&        theB,
                         double&        theFB,
                         double&        theC,
                         double&        theFC) const;

private:
  bool   Done;
  double Ax;
  double Bx;
  double Cx;
  double FAx;
  double FBx;
  double FCx;
  double myLeft;
  double myRight;
  bool   myIsLimited;
  bool   myFA;
  bool   myFB;
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

// math_BracketMinimum_1.hpp

#include <Precision.hpp>

inline math_BracketMinimum::math_BracketMinimum(const double A, const double B)
    : Done(false),
      Ax(A),
      Bx(B),
      Cx(0.),
      FAx(0.),
      FBx(0.),
      FCx(0.),
      myLeft(-Precision::Infinite()),
      myRight(Precision::Infinite()),
      myIsLimited(false),
      myFA(false),
      myFB(false)
{
}

inline bool math_BracketMinimum::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_BracketMinimum& Br)
{
  Br.Dump(o);
  return o;
}

inline void math_BracketMinimum::SetLimits(const double theLeft, const double theRight)
{
  myLeft      = theLeft;
  myRight     = theRight;
  myIsLimited = true;
}

inline void math_BracketMinimum::SetFA(const double theValue)
{
  FAx  = theValue;
  myFA = true;
}

inline void math_BracketMinimum::SetFB(const double theValue)
{
  FBx  = theValue;
  myFB = true;
}

inline double math_BracketMinimum::Limited(const double theValue) const
{
  return theValue < myLeft ? myLeft : theValue > myRight ? myRight : theValue;
}
