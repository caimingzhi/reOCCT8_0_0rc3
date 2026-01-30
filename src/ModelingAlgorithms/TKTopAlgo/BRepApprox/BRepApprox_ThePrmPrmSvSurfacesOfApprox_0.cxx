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

#include <BRepApprox_ThePrmPrmSvSurfacesOfApprox.hpp>

#include <BRepAdaptor_Surface.hpp>
#include <BRepApprox_SurfaceTool.hpp>
#include <BRepApprox_ApproxLine.hpp>
#include <BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#include <BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>

#define ThePSurface BRepAdaptor_Surface
#define ThePSurface_hxx <BRepAdaptor_Surface.hpp>
#define ThePSurfaceTool BRepApprox_SurfaceTool
#define ThePSurfaceTool_hxx <BRepApprox_SurfaceTool.hpp>
#define Handle_TheLine occ::handle<BRepApprox_ApproxLine>
#define TheLine BRepApprox_ApproxLine
#define TheLine_hxx <BRepApprox_ApproxLine.hpp>
#define ApproxInt_TheInt2S BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox
#define ApproxInt_TheInt2S_hxx <BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#define ApproxInt_TheFunctionOfTheInt2S                                                            \
  BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox
#define ApproxInt_TheFunctionOfTheInt2S_hxx                                                        \
  <BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#define ApproxInt_TheFunctionOfTheInt2S                                                            \
  BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox
#define ApproxInt_TheFunctionOfTheInt2S_hxx                                                        \
  <BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#define ApproxInt_PrmPrmSvSurfaces BRepApprox_ThePrmPrmSvSurfacesOfApprox
#define ApproxInt_PrmPrmSvSurfaces_hxx <BRepApprox_ThePrmPrmSvSurfacesOfApprox.hpp>
#include <ApproxInt_PrmPrmSvSurfaces.hpp>
