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

#ifndef _CPnts_MyGaussFunction_HeaderFile
#define _CPnts_MyGaussFunction_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <CPnts_RealFunction.hpp>
#include <math_Function.hpp>
#include <Standard_Real.hpp>

//! for implementation, compute values for Gauss
class CPnts_MyGaussFunction : public math_Function
{
public:
  DEFINE_STANDARD_ALLOC

  CPnts_MyGaussFunction();

  //! F is a pointer on a function D is a client data
  //!
  //! Each value is computed with F(D)
  Standard_EXPORT void Init(const CPnts_RealFunction& F, void* const D);

  Standard_EXPORT bool Value(const double X, double& F) override;

private:
  CPnts_RealFunction myFunction;
  void*              myData;
};

#include <CPnts_MyGaussFunction_1.hpp>

#endif // _CPnts_MyGaussFunction_HeaderFile
