// Created on: 1993-02-05
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

#include <Contap_TheIWalking.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>
#include <IntSurf_PathPoint.hpp>
#include <IntSurf_PathPointTool.hpp>
#include <IntSurf_InteriorPoint.hpp>
#include <IntSurf_InteriorPointTool.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <Contap_SurfFunction.hpp>
#include <Contap_TheIWLineOfTheIWalking.hpp>
#include <NCollection_Sequence.hpp>
#include <IntSurf_PntOn2S.hpp>

#define ThePointOfPath IntSurf_PathPoint
#define ThePointOfPath_hxx <IntSurf_PathPoint.hpp>
#define ThePointOfPathTool IntSurf_PathPointTool
#define ThePointOfPathTool_hxx <IntSurf_PathPointTool.hpp>
#define ThePOPIterator NCollection_Sequence<IntSurf_PathPoint>
#define ThePOPIterator_hxx <NCollection_Sequence<IntSurf_PathPoint>.hxx>
#define ThePointOfLoop IntSurf_InteriorPoint
#define ThePointOfLoop_hxx <IntSurf_InteriorPoint.hpp>
#define ThePointOfLoopTool IntSurf_InteriorPointTool
#define ThePointOfLoopTool_hxx <IntSurf_InteriorPointTool.hpp>
#define ThePOLIterator NCollection_Sequence<IntSurf_InteriorPoint>
#define ThePOLIterator_hxx <NCollection_Sequence<IntSurf_InteriorPoint>.hxx>
#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define TheIWFunction Contap_SurfFunction
#define TheIWFunction_hxx <Contap_SurfFunction.hpp>
#define IntWalk_TheIWLine Contap_TheIWLineOfTheIWalking
#define IntWalk_TheIWLine_hxx <Contap_TheIWLineOfTheIWalking.hpp>
#define IntWalk_SequenceOfIWLine NCollection_Sequence<occ::handle<Contap_TheIWLineOfTheIWalking>>
#define IntWalk_SequenceOfIWLine_hxx                                                               \
  <NCollection_Sequence<occ::handle<Contap_TheIWLineOfTheIWalking>>.hxx>
#define Handle_IntWalk_TheIWLine occ::handle<Contap_TheIWLineOfTheIWalking>
#define IntWalk_IWalking Contap_TheIWalking
#define IntWalk_IWalking_hxx <Contap_TheIWalking.hpp>
#include <IntWalk_IWalking.hpp>
