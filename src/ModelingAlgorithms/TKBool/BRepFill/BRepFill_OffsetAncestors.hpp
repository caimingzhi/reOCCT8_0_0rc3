// Created on: 1995-09-01
// Created by: Bruno DUMORTIER
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

#ifndef _BRepFill_OffsetAncestors_HeaderFile
#define _BRepFill_OffsetAncestors_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class BRepFill_OffsetWire;
class TopoDS_Edge;
class TopoDS_Shape;

//! this class is used to find the generating shapes
//! of an OffsetWire.
class BRepFill_OffsetAncestors
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_OffsetAncestors();

  Standard_EXPORT BRepFill_OffsetAncestors(BRepFill_OffsetWire& Paral);

  Standard_EXPORT void Perform(BRepFill_OffsetWire& Paral);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool HasAncestor(const TopoDS_Edge& S1) const;

  //! may return a Null Shape if S1 is not a subShape
  //! of <Paral>;
  //! if Perform is not done.
  Standard_EXPORT const TopoDS_Shape& Ancestor(const TopoDS_Edge& S1) const;

private:
  bool                                                                     myIsPerform;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
};

#endif // _BRepFill_OffsetAncestors_HeaderFile
