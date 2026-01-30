// Created on: 1995-06-06
// Created by: Jean Yves LEBEY
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

#include <BRepApprox_MyGradientbisOfTheComputeLineOfApprox.hpp>

#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <BRepApprox_TheMultiLineOfApprox.hpp>
#include <BRepApprox_TheMultiLineToolOfApprox.hpp>
#include <BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <AppParCurves_MultiCurve.hpp>

#define MultiLine BRepApprox_TheMultiLineOfApprox
#define MultiLine_hxx <BRepApprox_TheMultiLineOfApprox.hpp>
#define ToolLine BRepApprox_TheMultiLineToolOfApprox
#define ToolLine_hxx <BRepApprox_TheMultiLineToolOfApprox.hpp>
#define AppParCurves_ParLeastSquare BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox
#define AppParCurves_ParLeastSquare_hxx                                                            \
  <BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define AppParCurves_ResConstraint BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox
#define AppParCurves_ResConstraint_hxx                                                             \
  <BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define AppParCurves_ParFunction BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox
#define AppParCurves_ParFunction_hxx                                                               \
  <BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define AppParCurves_Gradient_BFGS BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox
#define AppParCurves_Gradient_BFGS_hxx                                                             \
  <BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define AppParCurves_Gradient BRepApprox_MyGradientbisOfTheComputeLineOfApprox
#define AppParCurves_Gradient_hxx <BRepApprox_MyGradientbisOfTheComputeLineOfApprox.hpp>
#include <AppParCurves_Gradient.hpp>
