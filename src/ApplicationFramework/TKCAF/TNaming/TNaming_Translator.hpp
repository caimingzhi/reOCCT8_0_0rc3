// Created on: 1999-06-30
// Created by: Sergey ZARITCHNY
// Copyright (c) 1999 Matra Datavision
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

#ifndef _TNaming_Translator_HeaderFile
#define _TNaming_Translator_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopoDS_Shape;

//! only for Shape Copy test - to move in DNaming
class TNaming_Translator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TNaming_Translator();

  Standard_EXPORT void Add(const TopoDS_Shape& aShape);

  Standard_EXPORT void Perform();

  Standard_EXPORT bool IsDone() const;

  //! returns copied shape
  Standard_EXPORT const TopoDS_Shape Copied(const TopoDS_Shape& aShape) const;

  //! returns DataMap of results; (shape <-> copied shape)
  Standard_EXPORT const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                        Copied() const;

  Standard_EXPORT void DumpMap(const bool isWrite = false) const;

private:
  bool myIsDone;
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>
                                                                           myMap;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myDataMapOfResults;
};

#endif // _TNaming_Translator_HeaderFile
