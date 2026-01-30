// Created on: 2000-08-11
// Created by: Andrey BETENEV
// Copyright (c) 2000-2014 OPEN CASCADE SAS
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

#ifndef _XCAFPrs_HeaderFile
#define _XCAFPrs_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <XCAFPrs_Style.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Boolean.hpp>
class TDF_Label;
class TopLoc_Location;

//! Presentation (visualiation, selection etc.) tools for
//! DECAF documents
class XCAFPrs
{
public:
  DEFINE_STANDARD_ALLOC

  //! Collect styles defined for shape on label L
  //! and its components and subshapes and fills a map of
  //! shape - style correspondence
  //! The location <loc> is for internal use, it
  //! should be Null location for external call
  Standard_EXPORT static void CollectStyleSettings(
    const TDF_Label&                                                                  L,
    const TopLoc_Location&                                                            loc,
    NCollection_IndexedDataMap<TopoDS_Shape, XCAFPrs_Style, TopTools_ShapeMapHasher>& settings,
    const Quantity_ColorRGBA& theLayerColor = Quantity_ColorRGBA(Quantity_NOC_WHITE));

  //! Set ViewNameMode for indicate display names or not.
  Standard_EXPORT static void SetViewNameMode(const bool viewNameMode);

  Standard_EXPORT static bool GetViewNameMode();
};

#endif // _XCAFPrs_HeaderFile
