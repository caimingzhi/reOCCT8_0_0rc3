// Created on: 1998-11-13
// Created by: Jean-Michel BOULCOURT
// Copyright (c) 1998-1999 Matra Datavision
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

#ifndef _BRepProj_Projection_HeaderFile
#define _BRepProj_Projection_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopoDS_Compound.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Wire.hpp>
class gp_Dir;
class gp_Pnt;

//! The Projection class provides conical and
//! cylindrical projections of Edge or Wire on
//! a Shape from TopoDS. The result will be a Edge
//! or Wire from TopoDS.
class BRepProj_Projection
{
public:
  DEFINE_STANDARD_ALLOC

  //! Makes a Cylindrical projection of Wire om Shape
  Standard_EXPORT BRepProj_Projection(const TopoDS_Shape& Wire,
                                      const TopoDS_Shape& Shape,
                                      const gp_Dir&       D);

  //! Makes a Conical projection of Wire om Shape
  Standard_EXPORT BRepProj_Projection(const TopoDS_Shape& Wire,
                                      const TopoDS_Shape& Shape,
                                      const gp_Pnt&       P);

  //! returns False if the section failed
  bool IsDone() const;

  //! Resets the iterator by resulting wires.
  void Init();

  //! Returns True if there is a current result wire
  bool More() const;

  //! Move to the next result wire.
  void Next();

  //! Returns the current result wire.
  TopoDS_Wire Current() const;

  //! Returns the complete result as compound of wires.
  TopoDS_Compound Shape() const;

private:
  //! Performs section of theShape by theTool
  //! and stores result in the fields.
  Standard_EXPORT void BuildSection(const TopoDS_Shape& Shape, const TopoDS_Shape& Tool);

  bool                                             myIsDone;
  TopoDS_Shape                                     myLsh;
  TopoDS_Compound                                  myShape;
  occ::handle<NCollection_HSequence<TopoDS_Shape>> mySection;
  int                                              myItr;
};
// Copyright (c) 1998-1999 Matra Datavision
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
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

inline bool BRepProj_Projection::IsDone() const
{
  return myIsDone;
}

inline TopoDS_Compound BRepProj_Projection::Shape() const
{
  return myShape;
}

inline void BRepProj_Projection::Init()
{
  myItr = 1;
}

inline bool BRepProj_Projection::More() const
{
  return myItr > 0 && !mySection.IsNull() && myItr <= mySection->Length();
}

inline void BRepProj_Projection::Next()
{
  myItr++;
}

inline TopoDS_Wire BRepProj_Projection::Current() const
{
  return TopoDS::Wire(mySection->Value(myItr));
}


#endif // _BRepProj_Projection_HeaderFile
