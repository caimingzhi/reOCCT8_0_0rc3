// Created on: 1993-12-06
// Created by: Jacques GOUSSARD
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

#include <BRepBlend_AppSurf.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <Blend_AppFunction.hpp>
#include <BRepBlend_Line.hpp>

#define TheSectionGenerator Blend_AppFunction
#define TheSectionGenerator_hxx <Blend_AppFunction.hpp>
#define Handle_TheLine occ::handle<BRepBlend_Line>
#define TheLine BRepBlend_Line
#define TheLine_hxx <BRepBlend_Line.hpp>
#define AppBlend_AppSurf BRepBlend_AppSurf
#define AppBlend_AppSurf_hxx <BRepBlend_AppSurf.hpp>
#include <AppBlend_AppSurf.hpp>
