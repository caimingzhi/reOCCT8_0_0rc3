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

#include <HLRBRep_TheExactInterCSurf.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <HLRBRep_SurfaceTool.hpp>
#include <gp_Lin.hpp>
#include <HLRBRep_LineTool.hpp>
#include <HLRBRep_TheCSFunctionOfInterCSurf.hpp>
#include <math_FunctionSetRoot.hpp>
#include <gp_Pnt.hpp>
#include <HLRBRep_Surface.hpp>

// Use typedef instead of #define for correct const semantics with pointers
typedef HLRBRep_Surface* ThePSurface;
#define ThePSurface_hxx <HLRBRep_Surface.hpp>
#define ThePSurfaceTool HLRBRep_SurfaceTool
#define ThePSurfaceTool_hxx <HLRBRep_SurfaceTool.hpp>
#define TheCurve gp_Lin
#define TheCurve_hxx <gp_Lin.hpp>
#define TheCurveTool HLRBRep_LineTool
#define TheCurveTool_hxx <HLRBRep_LineTool.hpp>
#define TheFunction HLRBRep_TheCSFunctionOfInterCSurf
#define TheFunction_hxx <HLRBRep_TheCSFunctionOfInterCSurf.hpp>
#define IntImp_IntCS HLRBRep_TheExactInterCSurf
#define IntImp_IntCS_hxx <HLRBRep_TheExactInterCSurf.hpp>
#include <IntImp_IntCS.hpp>
