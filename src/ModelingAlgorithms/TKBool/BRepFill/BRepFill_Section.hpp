#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Wire.hpp>
#include <TopoDS_Vertex.hpp>

//! To store section definition
class BRepFill_Section
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_Section();

  Standard_EXPORT BRepFill_Section(const TopoDS_Shape&  Profile,
                                   const TopoDS_Vertex& V,
                                   const bool           WithContact,
                                   const bool           WithCorrection);

  Standard_EXPORT void Set(const bool IsLaw);

  const TopoDS_Shape& OriginalShape() const;

  const TopoDS_Wire& Wire() const;

  const TopoDS_Vertex& Vertex() const;

  Standard_EXPORT TopoDS_Shape ModifiedShape(const TopoDS_Shape& theShape) const;

  bool IsLaw() const;

  bool IsPunctual() const;

  bool WithContact() const;

  bool WithCorrection() const;

private:
  TopoDS_Shape  myOriginalShape;
  TopoDS_Wire   wire;
  TopoDS_Vertex vertex;
  bool          islaw;
  bool          ispunctual;
  bool          contact;
  bool          correction;
};
// Created on: 1998-07-22
// Created by: Philippe MANGIN
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

inline const TopoDS_Shape& BRepFill_Section::OriginalShape() const
{
  return myOriginalShape;
}

inline const TopoDS_Wire& BRepFill_Section::Wire() const
{
  return wire;
}

inline const TopoDS_Vertex& BRepFill_Section::Vertex() const
{
  return vertex;
}

inline bool BRepFill_Section::IsLaw() const
{
  return islaw;
}

inline bool BRepFill_Section::IsPunctual() const
{
  return ispunctual;
}

inline bool BRepFill_Section::WithContact() const
{
  return contact;
}

inline bool BRepFill_Section::WithCorrection() const
{
  return correction;
}


