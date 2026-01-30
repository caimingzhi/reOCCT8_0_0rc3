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

#include <BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_ConstructionError.hpp>
#include <StdFail_UndefinedDerivative.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepApprox_SurfaceTool.hpp>
#include <BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#include <math_FunctionSetRoot.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>

#define ThePSurface BRepAdaptor_Surface
#define ThePSurface_hxx <BRepAdaptor_Surface.hpp>
#define ThePSurfaceTool BRepApprox_SurfaceTool
#define ThePSurfaceTool_hxx <BRepApprox_SurfaceTool.hpp>
#define IntImp_TheFunction BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox
#define IntImp_TheFunction_hxx <BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#define IntImp_Int2S BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox
#define IntImp_Int2S_hxx <BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#include <IntImp_Int2S.hpp>
