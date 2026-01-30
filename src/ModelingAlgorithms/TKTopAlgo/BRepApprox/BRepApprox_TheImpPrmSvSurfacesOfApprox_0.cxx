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

#include <BRepApprox_TheImpPrmSvSurfacesOfApprox.hpp>

#include <BRepAdaptor_Surface.hpp>
#include <BRepApprox_SurfaceTool.hpp>
#include <IntSurf_Quadric.hpp>
#include <IntSurf_QuadricTool.hpp>
#include <BRepApprox_ApproxLine.hpp>
#include <BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>

#define ThePSurface BRepAdaptor_Surface
#define ThePSurface_hxx <BRepAdaptor_Surface.hpp>
#define ThePSurfaceTool BRepApprox_SurfaceTool
#define ThePSurfaceTool_hxx <BRepApprox_SurfaceTool.hpp>
#define TheISurface IntSurf_Quadric
#define TheISurface_hxx <IntSurf_Quadric.hpp>
#define TheISurfaceTool IntSurf_QuadricTool
#define TheISurfaceTool_hxx <IntSurf_QuadricTool.hpp>
#define Handle_TheLine occ::handle<BRepApprox_ApproxLine>
#define TheLine BRepApprox_ApproxLine
#define TheLine_hxx <BRepApprox_ApproxLine.hpp>
#define ApproxInt_TheZerImpFunc BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox
#define ApproxInt_TheZerImpFunc_hxx <BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox.hpp>
#define ApproxInt_ImpPrmSvSurfaces BRepApprox_TheImpPrmSvSurfacesOfApprox
#define ApproxInt_ImpPrmSvSurfaces_hxx <BRepApprox_TheImpPrmSvSurfacesOfApprox.hpp>
#include <ApproxInt_ImpPrmSvSurfaces.hpp>
