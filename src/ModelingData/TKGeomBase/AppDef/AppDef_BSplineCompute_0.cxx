// Created on: 1991-12-02
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

#include <AppDef_BSplineCompute.hpp>

#include <AppDef_MultiLine.hpp>
#include <AppDef_MyLineTool.hpp>
#include <AppDef_MyBSplGradientOfBSplineCompute.hpp>
#include <AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute.hpp>
#include <AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute.hpp>
#include <AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute.hpp>
#include <AppDef_MyGradientbisOfBSplineCompute.hpp>
#include <AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute.hpp>
#include <AppDef_ResConstraintOfMyGradientbisOfBSplineCompute.hpp>
#include <AppDef_ParFunctionOfMyGradientbisOfBSplineCompute.hpp>
#include <AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>
#include <AppParCurves_MultiCurve.hpp>

#define MultiLine AppDef_MultiLine
#define MultiLine_hxx <AppDef_MultiLine.hpp>
#define LineTool AppDef_MyLineTool
#define LineTool_hxx <AppDef_MyLineTool.hpp>
#define Approx_MyBSplGradient AppDef_MyBSplGradientOfBSplineCompute
#define Approx_MyBSplGradient_hxx <AppDef_MyBSplGradientOfBSplineCompute.hpp>
#define Approx_BSpParLeastSquareOfMyBSplGradient                                                   \
  AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute
#define Approx_BSpParLeastSquareOfMyBSplGradient_hxx                                               \
  <AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute.hpp>
#define Approx_BSpParFunctionOfMyBSplGradient AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute
#define Approx_BSpParFunctionOfMyBSplGradient_hxx                                                  \
  <AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute.hpp>
#define Approx_BSpGradient_BFGSOfMyBSplGradient                                                    \
  AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute
#define Approx_BSpGradient_BFGSOfMyBSplGradient_hxx                                                \
  <AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute.hpp>
#define Approx_BSpParLeastSquareOfMyBSplGradient                                                   \
  AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute
#define Approx_BSpParLeastSquareOfMyBSplGradient_hxx                                               \
  <AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute.hpp>
#define Approx_BSpParFunctionOfMyBSplGradient AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute
#define Approx_BSpParFunctionOfMyBSplGradient_hxx                                                  \
  <AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute.hpp>
#define Approx_BSpGradient_BFGSOfMyBSplGradient                                                    \
  AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute
#define Approx_BSpGradient_BFGSOfMyBSplGradient_hxx                                                \
  <AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute.hpp>
#define Approx_MyGradientbis AppDef_MyGradientbisOfBSplineCompute
#define Approx_MyGradientbis_hxx <AppDef_MyGradientbisOfBSplineCompute.hpp>
#define Approx_ParLeastSquareOfMyGradientbis AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute
#define Approx_ParLeastSquareOfMyGradientbis_hxx                                                   \
  <AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_ResConstraintOfMyGradientbis AppDef_ResConstraintOfMyGradientbisOfBSplineCompute
#define Approx_ResConstraintOfMyGradientbis_hxx                                                    \
  <AppDef_ResConstraintOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_ParFunctionOfMyGradientbis AppDef_ParFunctionOfMyGradientbisOfBSplineCompute
#define Approx_ParFunctionOfMyGradientbis_hxx                                                      \
  <AppDef_ParFunctionOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_Gradient_BFGSOfMyGradientbis AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute
#define Approx_Gradient_BFGSOfMyGradientbis_hxx                                                    \
  <AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_ParLeastSquareOfMyGradientbis AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute
#define Approx_ParLeastSquareOfMyGradientbis_hxx                                                   \
  <AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_ResConstraintOfMyGradientbis AppDef_ResConstraintOfMyGradientbisOfBSplineCompute
#define Approx_ResConstraintOfMyGradientbis_hxx                                                    \
  <AppDef_ResConstraintOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_ParFunctionOfMyGradientbis AppDef_ParFunctionOfMyGradientbisOfBSplineCompute
#define Approx_ParFunctionOfMyGradientbis_hxx                                                      \
  <AppDef_ParFunctionOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_Gradient_BFGSOfMyGradientbis AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute
#define Approx_Gradient_BFGSOfMyGradientbis_hxx                                                    \
  <AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_BSplComputeLine AppDef_BSplineCompute
#define Approx_BSplComputeLine_hxx <AppDef_BSplineCompute.hpp>
#include <Approx_BSplComputeLine.hpp>
