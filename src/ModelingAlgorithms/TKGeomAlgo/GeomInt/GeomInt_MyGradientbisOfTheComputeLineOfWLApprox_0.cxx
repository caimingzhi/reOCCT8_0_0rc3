// Created on: 1995-01-27
// Created by: Jacques GOUSSARD
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

#include <GeomInt_MyGradientbisOfTheComputeLineOfWLApprox.hpp>

#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <GeomInt_TheMultiLineOfWLApprox.hpp>
#include <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#include <GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <AppParCurves_MultiCurve.hpp>

#define MultiLine GeomInt_TheMultiLineOfWLApprox
#define MultiLine_hxx <GeomInt_TheMultiLineOfWLApprox.hpp>
#define ToolLine GeomInt_TheMultiLineToolOfWLApprox
#define ToolLine_hxx <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#define AppParCurves_ParLeastSquare GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox
#define AppParCurves_ParLeastSquare_hxx                                                            \
  <GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define AppParCurves_ResConstraint GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox
#define AppParCurves_ResConstraint_hxx                                                             \
  <GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define AppParCurves_ParFunction GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox
#define AppParCurves_ParFunction_hxx                                                               \
  <GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define AppParCurves_Gradient_BFGS GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox
#define AppParCurves_Gradient_BFGS_hxx                                                             \
  <GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define AppParCurves_Gradient GeomInt_MyGradientbisOfTheComputeLineOfWLApprox
#define AppParCurves_Gradient_hxx <GeomInt_MyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <AppParCurves_Gradient.hpp>
