// Created on: 1993-04-07
// Created by: Laurent BUCHARD
// Copyright (c) 1993-1999 Matra Datavision
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

#include <IntCurveSurface_TheInterferenceOfHInter.hpp>

#include <IntCurveSurface_ThePolygonOfHInter.hpp>
#include <IntCurveSurface_ThePolygonToolOfHInter.hpp>
#include <IntCurveSurface_ThePolyhedronOfHInter.hpp>
#include <IntCurveSurface_ThePolyhedronToolOfHInter.hpp>
#include <gp_Lin.hpp>
#include <Bnd_BoundSortBox.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>

#define Polygon3d IntCurveSurface_ThePolygonOfHInter
#define Polygon3d_hxx <IntCurveSurface_ThePolygonOfHInter.hpp>
#define ToolPolygon3d IntCurveSurface_ThePolygonToolOfHInter
#define ToolPolygon3d_hxx <IntCurveSurface_ThePolygonToolOfHInter.hpp>
#define Polyhedron IntCurveSurface_ThePolyhedronOfHInter
#define Polyhedron_hxx <IntCurveSurface_ThePolyhedronOfHInter.hpp>
#define ToolPolyh IntCurveSurface_ThePolyhedronToolOfHInter
#define ToolPolyh_hxx <IntCurveSurface_ThePolyhedronToolOfHInter.hpp>
#define Intf_InterferencePolygonPolyhedron IntCurveSurface_TheInterferenceOfHInter
#define Intf_InterferencePolygonPolyhedron_hxx <IntCurveSurface_TheInterferenceOfHInter.hpp>
#include <Intf_InterferencePolygonPolyhedron.hpp>
