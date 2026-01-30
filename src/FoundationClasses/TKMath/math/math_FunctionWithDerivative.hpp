// Created on: 1991-05-13
// Created by: Laurent Painnot
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

#ifndef _math_FunctionWithDerivative_HeaderFile
#define _math_FunctionWithDerivative_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_Function.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>

//! This abstract class describes the virtual functions associated with
//! a function of a single variable for which the first derivative is
//! available.
class math_FunctionWithDerivative : public math_Function
{
public:
  DEFINE_STANDARD_ALLOC

  //! Computes the value <F>of the function for the variable <X>.
  //! Returns True if the calculation were successfully done,
  //! False otherwise.
  Standard_EXPORT bool Value(const double X, double& F) override = 0;

  //! Computes the derivative <D> of the function
  //! for the variable <X>.
  //! Returns True if the calculation were successfully done,
  //! False otherwise.
  Standard_EXPORT virtual bool Derivative(const double X, double& D) = 0;

  //! Computes the value <F> and the derivative <D> of the
  //! function for the variable <X>.
  //! Returns True if the calculation were successfully done,
  //! False otherwise.
  Standard_EXPORT virtual bool Values(const double X, double& F, double& D) = 0;
  Standard_EXPORT ~math_FunctionWithDerivative() override;
};

#endif // _math_FunctionWithDerivative_HeaderFile
