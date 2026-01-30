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

#include <GeomInt_ThePrmPrmSvSurfacesOfWLApprox.hpp>

#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <IntPatch_WLine.hpp>
#include <GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>
#include <GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define Handle_TheLine occ::handle<IntPatch_WLine>
#define TheLine IntPatch_WLine
#define TheLine_hxx <IntPatch_WLine.hpp>
#define ApproxInt_TheInt2S GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox
#define ApproxInt_TheInt2S_hxx <GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>
#define ApproxInt_TheFunctionOfTheInt2S GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox
#define ApproxInt_TheFunctionOfTheInt2S_hxx                                                        \
  <GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>
#define ApproxInt_TheFunctionOfTheInt2S GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox
#define ApproxInt_TheFunctionOfTheInt2S_hxx                                                        \
  <GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>
#define ApproxInt_PrmPrmSvSurfaces GeomInt_ThePrmPrmSvSurfacesOfWLApprox
#define ApproxInt_PrmPrmSvSurfaces_hxx <GeomInt_ThePrmPrmSvSurfacesOfWLApprox.hpp>
#include <ApproxInt_PrmPrmSvSurfaces.hpp>
