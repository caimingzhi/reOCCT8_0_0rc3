// Created on: 1993-10-22
// Created by: Laurent BOURESCHE
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

#ifndef _ChFiDS_Map_HeaderFile
#define _ChFiDS_Map_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <Standard_Boolean.hpp>
class TopoDS_Shape;

//! Encapsulation of IndexedDataMapOfShapeListOfShape.
class ChFiDS_Map
{
public:
  DEFINE_STANDARD_ALLOC

  //! Create an empty Map
  Standard_EXPORT ChFiDS_Map();

  //! Fills the map with the subshapes of type T1 as keys
  //! and the list of ancestors of type T2 as items.
  Standard_EXPORT void Fill(const TopoDS_Shape&    S,
                            const TopAbs_ShapeEnum T1,
                            const TopAbs_ShapeEnum T2);

  Standard_EXPORT bool Contains(const TopoDS_Shape& S) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& FindFromKey(const TopoDS_Shape& S) const;

  const NCollection_List<TopoDS_Shape>& operator()(const TopoDS_Shape& S) const
  {
    return FindFromKey(S);
  }

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& FindFromIndex(const int I) const;

  const NCollection_List<TopoDS_Shape>& operator()(const int I) const { return FindFromIndex(I); }

private:
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myMap;
};

#endif // _ChFiDS_Map_HeaderFile
