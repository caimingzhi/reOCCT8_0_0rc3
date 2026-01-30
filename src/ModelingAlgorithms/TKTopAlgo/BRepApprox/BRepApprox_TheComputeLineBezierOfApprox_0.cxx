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

#include <BRepApprox_TheComputeLineBezierOfApprox.hpp>

#include <BRepApprox_TheMultiLineOfApprox.hpp>
#include <BRepApprox_TheMultiLineToolOfApprox.hpp>
#include <BRepApprox_MyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <AppParCurves_MultiCurve.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>

#define MultiLine BRepApprox_TheMultiLineOfApprox
#define MultiLine_hxx <BRepApprox_TheMultiLineOfApprox.hpp>
#define LineTool BRepApprox_TheMultiLineToolOfApprox
#define LineTool_hxx <BRepApprox_TheMultiLineToolOfApprox.hpp>
#define Approx_MyGradient BRepApprox_MyGradientOfTheComputeLineBezierOfApprox
#define Approx_MyGradient_hxx <BRepApprox_MyGradientOfTheComputeLineBezierOfApprox.hpp>
#define Approx_ParLeastSquareOfMyGradient                                                          \
  BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox
#define Approx_ParLeastSquareOfMyGradient_hxx                                                      \
  <BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#define Approx_ResConstraintOfMyGradient                                                           \
  BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox
#define Approx_ResConstraintOfMyGradient_hxx                                                       \
  <BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#define Approx_ParFunctionOfMyGradient                                                             \
  BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox
#define Approx_ParFunctionOfMyGradient_hxx                                                         \
  <BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#define Approx_Gradient_BFGSOfMyGradient                                                           \
  BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox
#define Approx_Gradient_BFGSOfMyGradient_hxx                                                       \
  <BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#define Approx_ParLeastSquareOfMyGradient                                                          \
  BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox
#define Approx_ParLeastSquareOfMyGradient_hxx                                                      \
  <BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#define Approx_ResConstraintOfMyGradient                                                           \
  BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox
#define Approx_ResConstraintOfMyGradient_hxx                                                       \
  <BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#define Approx_ParFunctionOfMyGradient                                                             \
  BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox
#define Approx_ParFunctionOfMyGradient_hxx                                                         \
  <BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#define Approx_Gradient_BFGSOfMyGradient                                                           \
  BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox
#define Approx_Gradient_BFGSOfMyGradient_hxx                                                       \
  <BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#define Approx_ComputeLine BRepApprox_TheComputeLineBezierOfApprox
#define Approx_ComputeLine_hxx <BRepApprox_TheComputeLineBezierOfApprox.hpp>
#include <Approx_ComputeLine.hpp>
