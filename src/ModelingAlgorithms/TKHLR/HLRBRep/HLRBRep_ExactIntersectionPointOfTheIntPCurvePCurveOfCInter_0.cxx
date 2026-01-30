// Created on: 1992-10-14
// Created by: Christophe MARION
// Copyright (c) 1992-1999 Matra Datavision
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

#include <HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter.hpp>

#include <HLRBRep_CurveTool.hpp>
#include <HLRBRep_TheProjPCurOfCInter.hpp>
#include <HLRBRep_TheIntPCurvePCurveOfCInter.hpp>
#include <HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter.hpp>
#include <HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter.hpp>

#define TheCurve HLRBRep_CurvePtr
#define TheCurve_hxx <HLRBRep_TypeDef.hpp>
#define TheCurveTool HLRBRep_CurveTool
#define TheCurveTool_hxx <HLRBRep_CurveTool.hpp>
#define TheProjPCur HLRBRep_TheProjPCurOfCInter
#define TheProjPCur_hxx <HLRBRep_TheProjPCurOfCInter.hpp>
#define IntCurve_ThePolygon2d HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter
#define IntCurve_ThePolygon2d_hxx <HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter.hpp>
#define IntCurve_TheDistBetweenPCurves HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter
#define IntCurve_TheDistBetweenPCurves_hxx                                                         \
  <HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter.hpp>
#define IntCurve_ExactIntersectionPoint HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter
#define IntCurve_ExactIntersectionPoint_hxx                                                        \
  <HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter.hpp>
#define IntCurve_IntPolyPolyGen HLRBRep_TheIntPCurvePCurveOfCInter
#define IntCurve_IntPolyPolyGen_hxx <HLRBRep_TheIntPCurvePCurveOfCInter.hpp>
#include <IntCurve_ExactIntersectionPoint.hpp>
