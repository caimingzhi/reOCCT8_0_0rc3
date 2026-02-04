#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>

#include <TopTools_ShapeMapHasher.hpp>

#include <NCollection_Map.hpp>
#include <Standard_Boolean.hpp>
class Standard_NoMoreObject;
class Standard_NoSuchObject;
class TNaming_ShapesSet;
class TopoDS_Shape;

class TNaming_IteratorOnShapesSet
{
public:
  DEFINE_STANDARD_ALLOC

  TNaming_IteratorOnShapesSet();

  TNaming_IteratorOnShapesSet(const TNaming_ShapesSet& S);

  //! Initialize the iteration
  void Init(const TNaming_ShapesSet& S);

  //! Returns True if there is a current Item in
  //! the iteration.
  bool More() const;

  //! Move to the next Item
  void Next();

  const TopoDS_Shape& Value() const;

private:
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator myIt;
};
// Created on: 1997-05-06
// Created by: Yves FRICAUD
// Copyright (c) 1997-1999 Matra Datavision
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

#include <TNaming_ShapesSet.hpp>

//=================================================================================================

inline TNaming_IteratorOnShapesSet::TNaming_IteratorOnShapesSet() = default;

//=================================================================================================

inline TNaming_IteratorOnShapesSet::TNaming_IteratorOnShapesSet(const TNaming_ShapesSet& S)
{
  Init(S);
}

//=================================================================================================

inline void TNaming_IteratorOnShapesSet::Init(const TNaming_ShapesSet& S)
{
  myIt.Initialize(S.Map());
}

//=================================================================================================

inline bool TNaming_IteratorOnShapesSet::More() const
{
  return (myIt.More());
}

//=================================================================================================

inline void TNaming_IteratorOnShapesSet::Next()
{
  myIt.Next();
}

//=================================================================================================

inline const TopoDS_Shape& TNaming_IteratorOnShapesSet::Value() const
{
  return myIt.Key();
}


