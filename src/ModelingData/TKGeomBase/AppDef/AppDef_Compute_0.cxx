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

#include <AppDef_Compute.hpp>

#include <AppDef_MultiLine.hpp>
#include <AppDef_MyLineTool.hpp>
#include <AppDef_MyGradientOfCompute.hpp>
#include <AppDef_ParLeastSquareOfMyGradientOfCompute.hpp>
#include <AppDef_ResConstraintOfMyGradientOfCompute.hpp>
#include <AppDef_ParFunctionOfMyGradientOfCompute.hpp>
#include <AppDef_Gradient_BFGSOfMyGradientOfCompute.hpp>
#include <AppParCurves_MultiCurve.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>

#define MultiLine AppDef_MultiLine
#define MultiLine_hxx <AppDef_MultiLine.hpp>
#define LineTool AppDef_MyLineTool
#define LineTool_hxx <AppDef_MyLineTool.hpp>
#define Approx_MyGradient AppDef_MyGradientOfCompute
#define Approx_MyGradient_hxx <AppDef_MyGradientOfCompute.hpp>
#define Approx_ParLeastSquareOfMyGradient AppDef_ParLeastSquareOfMyGradientOfCompute
#define Approx_ParLeastSquareOfMyGradient_hxx <AppDef_ParLeastSquareOfMyGradientOfCompute.hpp>
#define Approx_ResConstraintOfMyGradient AppDef_ResConstraintOfMyGradientOfCompute
#define Approx_ResConstraintOfMyGradient_hxx <AppDef_ResConstraintOfMyGradientOfCompute.hpp>
#define Approx_ParFunctionOfMyGradient AppDef_ParFunctionOfMyGradientOfCompute
#define Approx_ParFunctionOfMyGradient_hxx <AppDef_ParFunctionOfMyGradientOfCompute.hpp>
#define Approx_Gradient_BFGSOfMyGradient AppDef_Gradient_BFGSOfMyGradientOfCompute
#define Approx_Gradient_BFGSOfMyGradient_hxx <AppDef_Gradient_BFGSOfMyGradientOfCompute.hpp>
#define Approx_ParLeastSquareOfMyGradient AppDef_ParLeastSquareOfMyGradientOfCompute
#define Approx_ParLeastSquareOfMyGradient_hxx <AppDef_ParLeastSquareOfMyGradientOfCompute.hpp>
#define Approx_ResConstraintOfMyGradient AppDef_ResConstraintOfMyGradientOfCompute
#define Approx_ResConstraintOfMyGradient_hxx <AppDef_ResConstraintOfMyGradientOfCompute.hpp>
#define Approx_ParFunctionOfMyGradient AppDef_ParFunctionOfMyGradientOfCompute
#define Approx_ParFunctionOfMyGradient_hxx <AppDef_ParFunctionOfMyGradientOfCompute.hpp>
#define Approx_Gradient_BFGSOfMyGradient AppDef_Gradient_BFGSOfMyGradientOfCompute
#define Approx_Gradient_BFGSOfMyGradient_hxx <AppDef_Gradient_BFGSOfMyGradientOfCompute.hpp>
#define Approx_ComputeLine AppDef_Compute
#define Approx_ComputeLine_hxx <AppDef_Compute.hpp>
#include <Approx_ComputeLine.hpp>
