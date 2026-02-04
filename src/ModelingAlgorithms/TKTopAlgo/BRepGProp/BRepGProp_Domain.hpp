#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopExp_Explorer.hpp>
#include <Standard_Boolean.hpp>
class TopoDS_Face;
class TopoDS_Edge;

//! Arc iterator. Returns only Forward and Reversed edges from
//! the face in an undigested order.
class BRepGProp_Domain
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  BRepGProp_Domain();

  //! Constructor. Initializes the domain with the face.
  BRepGProp_Domain(const TopoDS_Face& F);

  //! Initializes the domain with the face.
  void Init(const TopoDS_Face& F);

  //! Returns True if there is another arc of curve in the list.
  bool More();

  //! Initializes the exploration with the face already set.
  void Init();

  //! Returns the current edge.
  const TopoDS_Edge& Value();

  //! Sets the index of the arc iterator to the next arc of
  //! curve.
  Standard_EXPORT void Next();

private:
  TopExp_Explorer myExplorer;
};
// Created on: 2005-12-13
// Created by: Sergey KHROMOV
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

#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>

//=================================================================================================

inline BRepGProp_Domain::BRepGProp_Domain() = default;

//=======================================================================
// function : BRepGProp_Domain
// purpose  : Constructor. Initializes the domain with the face.
//=======================================================================

inline BRepGProp_Domain::BRepGProp_Domain(const TopoDS_Face& F)
    : myExplorer(F.Oriented(TopAbs_FORWARD), TopAbs_EDGE)
{
}

//=======================================================================
// function : Init
// purpose  : Initializes the domain with the face.
//=======================================================================

inline void BRepGProp_Domain::Init(const TopoDS_Face& F)
{
  myExplorer.Init(F.Oriented(TopAbs_FORWARD), TopAbs_EDGE);
}

//=======================================================================
// function : More
// purpose  : Returns True if there is another arc of curve in the list.
//=======================================================================

inline bool BRepGProp_Domain::More()
{
  return myExplorer.More();
}

//=======================================================================
// function : Init
// purpose  : Initializes the exploration with the face already set.
//=======================================================================

inline void BRepGProp_Domain::Init()
{
  myExplorer.ReInit();
}

//=======================================================================
// function : Value
// purpose  : Returns the current edge.
//=======================================================================

inline const TopoDS_Edge& BRepGProp_Domain::Value()
{
  return TopoDS::Edge(myExplorer.Current());
}


