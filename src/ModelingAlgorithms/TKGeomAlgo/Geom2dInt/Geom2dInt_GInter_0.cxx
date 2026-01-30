// Created on: 1992-06-04
// Created by: Jacques GOUSSARD
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

#include <Geom2dInt_GInter.hpp>

#include <Standard_ConstructionError.hpp>
#include <Adaptor2d_Curve2d.hpp>
#include <Geom2dInt_Geom2dCurveTool.hpp>
#include <Geom2dInt_TheProjPCurOfGInter.hpp>
#include <Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter.hpp>
#include <Geom2dInt_TheLocateExtPCOfTheProjPCurOfGInter.hpp>
#include <Geom2dInt_TheIntConicCurveOfGInter.hpp>
#include <Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter.hpp>
#include <Geom2dInt_IntConicCurveOfGInter.hpp>
#include <Geom2dInt_TheIntPCurvePCurveOfGInter.hpp>
#include <Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter.hpp>
#include <Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter.hpp>
#include <Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter.hpp>
#include <IntRes2d_Domain.hpp>

#define TheCurve Adaptor2d_Curve2d
#define TheCurve_hxx <Adaptor2d_Curve2d.hpp>
#define TheCurveTool Geom2dInt_Geom2dCurveTool
#define TheCurveTool_hxx <Geom2dInt_Geom2dCurveTool.hpp>
#define IntCurve_TheProjPCur Geom2dInt_TheProjPCurOfGInter
#define IntCurve_TheProjPCur_hxx <Geom2dInt_TheProjPCurOfGInter.hpp>
#define IntCurve_TheCurveLocatorOfTheProjPCur Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter
#define IntCurve_TheCurveLocatorOfTheProjPCur_hxx                                                  \
  <Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter.hpp>
#define IntCurve_TheLocateExtPCOfTheProjPCur Geom2dInt_TheLocateExtPCOfTheProjPCurOfGInter
#define IntCurve_TheLocateExtPCOfTheProjPCur_hxx                                                   \
  <Geom2dInt_TheLocateExtPCOfTheProjPCurOfGInter.hpp>
#define IntCurve_TheCurveLocatorOfTheProjPCur Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter
#define IntCurve_TheCurveLocatorOfTheProjPCur_hxx                                                  \
  <Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter.hpp>
#define IntCurve_TheLocateExtPCOfTheProjPCur Geom2dInt_TheLocateExtPCOfTheProjPCurOfGInter
#define IntCurve_TheLocateExtPCOfTheProjPCur_hxx                                                   \
  <Geom2dInt_TheLocateExtPCOfTheProjPCurOfGInter.hpp>
#define IntCurve_TheIntConicCurve Geom2dInt_TheIntConicCurveOfGInter
#define IntCurve_TheIntConicCurve_hxx <Geom2dInt_TheIntConicCurveOfGInter.hpp>
#define IntCurve_TheIntersectorOfTheIntConicCurve Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter
#define IntCurve_TheIntersectorOfTheIntConicCurve_hxx                                              \
  <Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter.hpp>
#define IntCurve_TheIntersectorOfTheIntConicCurve Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter
#define IntCurve_TheIntersectorOfTheIntConicCurve_hxx                                              \
  <Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter.hpp>
#define IntCurve_IntConicCurve Geom2dInt_IntConicCurveOfGInter
#define IntCurve_IntConicCurve_hxx <Geom2dInt_IntConicCurveOfGInter.hpp>
#define IntCurve_TheIntPCurvePCurve Geom2dInt_TheIntPCurvePCurveOfGInter
#define IntCurve_TheIntPCurvePCurve_hxx <Geom2dInt_TheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_ThePolygon2dOfTheIntPCurvePCurve Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter
#define IntCurve_ThePolygon2dOfTheIntPCurvePCurve_hxx                                              \
  <Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve                                         \
  Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter
#define IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve_hxx                                     \
  <Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve                                        \
  Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter
#define IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve_hxx                                    \
  <Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_ThePolygon2dOfTheIntPCurvePCurve Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter
#define IntCurve_ThePolygon2dOfTheIntPCurvePCurve_hxx                                              \
  <Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve                                         \
  Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter
#define IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve_hxx                                     \
  <Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve                                        \
  Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter
#define IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve_hxx                                    \
  <Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_IntCurveCurveGen Geom2dInt_GInter
#define IntCurve_IntCurveCurveGen_hxx <Geom2dInt_GInter.hpp>
#include <IntCurve_IntCurveCurveGen.hpp>
