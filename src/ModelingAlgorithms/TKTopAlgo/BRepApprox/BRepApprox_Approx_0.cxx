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

#include <BRepApprox_Approx.hpp>

#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepApprox_SurfaceTool.hpp>
#include <IntSurf_Quadric.hpp>
#include <IntSurf_QuadricTool.hpp>
#include <BRepApprox_ApproxLine.hpp>
#include <BRepApprox_ThePrmPrmSvSurfacesOfApprox.hpp>
#include <BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#include <BRepApprox_TheImpPrmSvSurfacesOfApprox.hpp>
#include <BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox.hpp>
#include <BRepApprox_TheMultiLineOfApprox.hpp>
#include <BRepApprox_TheMultiLineToolOfApprox.hpp>
#include <BRepApprox_TheComputeLineOfApprox.hpp>
#include <BRepApprox_MyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_MyGradientbisOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_TheComputeLineBezierOfApprox.hpp>
#include <BRepApprox_MyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>

#define ThePSurface BRepAdaptor_Surface
#define ThePSurface_hxx <BRepAdaptor_Surface.hpp>
#define ThePSurfaceTool BRepApprox_SurfaceTool
#define ThePSurfaceTool_hxx <BRepApprox_SurfaceTool.hpp>
#define TheISurface IntSurf_Quadric
#define TheISurface_hxx <IntSurf_Quadric.hpp>
#define TheISurfaceTool IntSurf_QuadricTool
#define TheISurfaceTool_hxx <IntSurf_QuadricTool.hpp>
#define Handle_TheWLine occ::handle<BRepApprox_ApproxLine>
#define TheWLine BRepApprox_ApproxLine
#define TheWLine_hxx <BRepApprox_ApproxLine.hpp>
#define ApproxInt_ThePrmPrmSvSurfaces BRepApprox_ThePrmPrmSvSurfacesOfApprox
#define ApproxInt_ThePrmPrmSvSurfaces_hxx <BRepApprox_ThePrmPrmSvSurfacesOfApprox.hpp>
#define ApproxInt_TheInt2SOfThePrmPrmSvSurfaces BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox
#define ApproxInt_TheInt2SOfThePrmPrmSvSurfaces_hxx                                                \
  <BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#define ApproxInt_TheInt2SOfThePrmPrmSvSurfaces BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox
#define ApproxInt_TheInt2SOfThePrmPrmSvSurfaces_hxx                                                \
  <BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#define ApproxInt_TheImpPrmSvSurfaces BRepApprox_TheImpPrmSvSurfacesOfApprox
#define ApproxInt_TheImpPrmSvSurfaces_hxx <BRepApprox_TheImpPrmSvSurfacesOfApprox.hpp>
#define ApproxInt_TheZerImpFuncOfTheImpPrmSvSurfaces                                               \
  BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox
#define ApproxInt_TheZerImpFuncOfTheImpPrmSvSurfaces_hxx                                           \
  <BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox.hpp>
#define ApproxInt_TheZerImpFuncOfTheImpPrmSvSurfaces                                               \
  BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox
#define ApproxInt_TheZerImpFuncOfTheImpPrmSvSurfaces_hxx                                           \
  <BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox.hpp>
#define ApproxInt_TheMultiLine BRepApprox_TheMultiLineOfApprox
#define ApproxInt_TheMultiLine_hxx <BRepApprox_TheMultiLineOfApprox.hpp>
#define ApproxInt_TheMultiLineTool BRepApprox_TheMultiLineToolOfApprox
#define ApproxInt_TheMultiLineTool_hxx <BRepApprox_TheMultiLineToolOfApprox.hpp>
#define ApproxInt_TheComputeLine BRepApprox_TheComputeLineOfApprox
#define ApproxInt_TheComputeLine_hxx <BRepApprox_TheComputeLineOfApprox.hpp>
#define ApproxInt_MyBSplGradientOfTheComputeLine BRepApprox_MyBSplGradientOfTheComputeLineOfApprox
#define ApproxInt_MyBSplGradientOfTheComputeLine_hxx                                               \
  <BRepApprox_MyBSplGradientOfTheComputeLineOfApprox.hpp>
#define ApproxInt_MyGradientbisOfTheComputeLine BRepApprox_MyGradientbisOfTheComputeLineOfApprox
#define ApproxInt_MyGradientbisOfTheComputeLine_hxx                                                \
  <BRepApprox_MyGradientbisOfTheComputeLineOfApprox.hpp>
#define ApproxInt_MyBSplGradientOfTheComputeLine BRepApprox_MyBSplGradientOfTheComputeLineOfApprox
#define ApproxInt_MyBSplGradientOfTheComputeLine_hxx                                               \
  <BRepApprox_MyBSplGradientOfTheComputeLineOfApprox.hpp>
#define ApproxInt_MyGradientbisOfTheComputeLine BRepApprox_MyGradientbisOfTheComputeLineOfApprox
#define ApproxInt_MyGradientbisOfTheComputeLine_hxx                                                \
  <BRepApprox_MyGradientbisOfTheComputeLineOfApprox.hpp>
#define ApproxInt_TheComputeLineBezier BRepApprox_TheComputeLineBezierOfApprox
#define ApproxInt_TheComputeLineBezier_hxx <BRepApprox_TheComputeLineBezierOfApprox.hpp>
#define ApproxInt_MyGradientOfTheComputeLineBezier                                                 \
  BRepApprox_MyGradientOfTheComputeLineBezierOfApprox
#define ApproxInt_MyGradientOfTheComputeLineBezier_hxx                                             \
  <BRepApprox_MyGradientOfTheComputeLineBezierOfApprox.hpp>
#define ApproxInt_MyGradientOfTheComputeLineBezier                                                 \
  BRepApprox_MyGradientOfTheComputeLineBezierOfApprox
#define ApproxInt_MyGradientOfTheComputeLineBezier_hxx                                             \
  <BRepApprox_MyGradientOfTheComputeLineBezierOfApprox.hpp>
#define ApproxInt_Approx BRepApprox_Approx
#define ApproxInt_Approx_hxx <BRepApprox_Approx.hpp>
#include <ApproxInt_Approx.hpp>
