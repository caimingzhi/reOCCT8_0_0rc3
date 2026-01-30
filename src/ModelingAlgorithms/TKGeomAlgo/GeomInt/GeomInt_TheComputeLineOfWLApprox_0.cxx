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

#include <GeomInt_TheComputeLineOfWLApprox.hpp>

#include <GeomInt_TheMultiLineOfWLApprox.hpp>
#include <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#include <GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_MyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>
#include <AppParCurves_MultiCurve.hpp>

#define MultiLine GeomInt_TheMultiLineOfWLApprox
#define MultiLine_hxx <GeomInt_TheMultiLineOfWLApprox.hpp>
#define LineTool GeomInt_TheMultiLineToolOfWLApprox
#define LineTool_hxx <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#define Approx_MyBSplGradient GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox
#define Approx_MyBSplGradient_hxx <GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#define Approx_BSpParLeastSquareOfMyBSplGradient                                                   \
  GeomInt_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfWLApprox
#define Approx_BSpParLeastSquareOfMyBSplGradient_hxx                                               \
  <GeomInt_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#define Approx_BSpParFunctionOfMyBSplGradient                                                      \
  GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox
#define Approx_BSpParFunctionOfMyBSplGradient_hxx                                                  \
  <GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#define Approx_BSpGradient_BFGSOfMyBSplGradient                                                    \
  GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox
#define Approx_BSpGradient_BFGSOfMyBSplGradient_hxx                                                \
  <GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#define Approx_BSpParLeastSquareOfMyBSplGradient                                                   \
  GeomInt_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfWLApprox
#define Approx_BSpParLeastSquareOfMyBSplGradient_hxx                                               \
  <GeomInt_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#define Approx_BSpParFunctionOfMyBSplGradient                                                      \
  GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox
#define Approx_BSpParFunctionOfMyBSplGradient_hxx                                                  \
  <GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#define Approx_BSpGradient_BFGSOfMyBSplGradient                                                    \
  GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox
#define Approx_BSpGradient_BFGSOfMyBSplGradient_hxx                                                \
  <GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#define Approx_MyGradientbis GeomInt_MyGradientbisOfTheComputeLineOfWLApprox
#define Approx_MyGradientbis_hxx <GeomInt_MyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define Approx_ParLeastSquareOfMyGradientbis                                                       \
  GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox
#define Approx_ParLeastSquareOfMyGradientbis_hxx                                                   \
  <GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define Approx_ResConstraintOfMyGradientbis                                                        \
  GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox
#define Approx_ResConstraintOfMyGradientbis_hxx                                                    \
  <GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define Approx_ParFunctionOfMyGradientbis                                                          \
  GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox
#define Approx_ParFunctionOfMyGradientbis_hxx                                                      \
  <GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define Approx_Gradient_BFGSOfMyGradientbis                                                        \
  GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox
#define Approx_Gradient_BFGSOfMyGradientbis_hxx                                                    \
  <GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define Approx_ParLeastSquareOfMyGradientbis                                                       \
  GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox
#define Approx_ParLeastSquareOfMyGradientbis_hxx                                                   \
  <GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define Approx_ResConstraintOfMyGradientbis                                                        \
  GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox
#define Approx_ResConstraintOfMyGradientbis_hxx                                                    \
  <GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define Approx_ParFunctionOfMyGradientbis                                                          \
  GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox
#define Approx_ParFunctionOfMyGradientbis_hxx                                                      \
  <GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define Approx_Gradient_BFGSOfMyGradientbis                                                        \
  GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox
#define Approx_Gradient_BFGSOfMyGradientbis_hxx                                                    \
  <GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define Approx_BSplComputeLine GeomInt_TheComputeLineOfWLApprox
#define Approx_BSplComputeLine_hxx <GeomInt_TheComputeLineOfWLApprox.hpp>
#include <Approx_BSplComputeLine.hpp>
