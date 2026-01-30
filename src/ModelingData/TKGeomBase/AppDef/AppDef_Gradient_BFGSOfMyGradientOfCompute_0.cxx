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

#include <AppDef_Gradient_BFGSOfMyGradientOfCompute.hpp>

#include <AppDef_MultiLine.hpp>
#include <AppDef_MyLineTool.hpp>
#include <AppDef_MyGradientOfCompute.hpp>
#include <AppDef_ParLeastSquareOfMyGradientOfCompute.hpp>
#include <AppDef_ResConstraintOfMyGradientOfCompute.hpp>
#include <AppDef_ParFunctionOfMyGradientOfCompute.hpp>
#include <math_MultipleVarFunctionWithGradient.hpp>

AppDef_Gradient_BFGSOfMyGradientOfCompute::AppDef_Gradient_BFGSOfMyGradientOfCompute(
  math_MultipleVarFunctionWithGradient& F,
  const math_Vector&                    StartingPoint,
  const double                          Tolerance3d,
  const double                          Tolerance2d,
  const double                          Eps,
  const int                             NbIterations)
    : math_BFGS(F.NbVariables(), Eps, NbIterations, Eps),
      myTol3d(Tolerance3d),
      myTol2d(Tolerance2d)
{
  Perform(F, StartingPoint);
}

bool AppDef_Gradient_BFGSOfMyGradientOfCompute::IsSolutionReached(
  math_MultipleVarFunctionWithGradient& F) const
{
  AppDef_ParFunctionOfMyGradientOfCompute* F1 = (AppDef_ParFunctionOfMyGradientOfCompute*)&F;
  bool                                     Result, Result2;

  Result        = (2.0 * fabs(TheMinimum - PreviousMinimum)
            <= 1.e-10 * (fabs(TheMinimum) + fabs(PreviousMinimum)) + 1.e-12);
  double MErr3d = F1->MaxError3d();
  double MErr2d = F1->MaxError2d();

  Result2 = ((MErr3d <= myTol3d) && (MErr2d <= myTol2d));
  return (Result || Result2);
}
