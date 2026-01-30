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

#include <Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter.hpp>

#include <Standard_OutOfRange.hpp>
#include <Adaptor2d_Curve2d.hpp>
#include <Geom2dInt_Geom2dCurveTool.hpp>
#include <IntRes2d_Domain.hpp>
#include <Bnd_Box2d.hpp>
#include <gp_Pnt2d.hpp>

#define TheCurve Adaptor2d_Curve2d
#define TheCurve_hxx <Adaptor2d_Curve2d.hpp>
#define TheCurveTool Geom2dInt_Geom2dCurveTool
#define TheCurveTool_hxx <Geom2dInt_Geom2dCurveTool.hpp>
#define IntCurve_Polygon2dGen Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter
#define IntCurve_Polygon2dGen_hxx <Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter.hpp>
#include <IntCurve_Polygon2dGen.hpp>
