// Created on: 1991-07-19
// Created by: Isabelle GRIGNON
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

#ifndef _CPnts_MyRootFunction_HeaderFile
#define _CPnts_MyRootFunction_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <CPnts_MyGaussFunction.hpp>
#include <Standard_Real.hpp>
#include <math_FunctionWithDerivative.hpp>
#include <CPnts_RealFunction.hpp>

//! Implements a function for the Newton algorithm to find the
//! solution of Integral(F) = L
//! (compute Length and Derivative of the curve for Newton)
class CPnts_MyRootFunction : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  CPnts_MyRootFunction();

  //! F is a pointer on a function D is a client data
  //! Order is the order of integration to use
  Standard_EXPORT void Init(const CPnts_RealFunction& F, void* const D, const int Order);

  //! We want to solve Integral(X0,X,F(X,D)) = L
  Standard_EXPORT void Init(const double X0, const double L);

  //! We want to solve Integral(X0,X,F(X,D)) = L
  //! with given tolerance
  Standard_EXPORT void Init(const double X0, const double L, const double Tol);

  //! This is Integral(X0,X,F(X,D)) - L
  Standard_EXPORT bool Value(const double X, double& F) override;

  //! This is F(X,D)
  Standard_EXPORT bool Derivative(const double X, double& Df) override;

  Standard_EXPORT bool Values(const double X, double& F, double& Df) override;

private:
  CPnts_MyGaussFunction myFunction;
  double                myX0;
  double                myL;
  int                   myOrder;
  double                myTol;
};
// Created on: 1995-05-04
// Created by: Modelistation
// Copyright (c) 1995-1999 Matra Datavision
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

inline CPnts_MyRootFunction::CPnts_MyRootFunction()
    : myX0(0.),
      myL(0.),
      myOrder(0),
      myTol(0.)
{
}


#endif // _CPnts_MyRootFunction_HeaderFile
