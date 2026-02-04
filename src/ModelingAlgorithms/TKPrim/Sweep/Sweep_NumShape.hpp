#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_ShapeEnum.hpp>
#include <Standard_Boolean.hpp>
#include <TopAbs_Orientation.hpp>

//! Gives a simple indexed representation of a
//! Directing Edge topology.
class Sweep_NumShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a dummy indexed edge.
  Standard_EXPORT Sweep_NumShape();

  //! Creates a new simple indexed edge.
  //!
  //! For an Edge : Index is the number of vertices (0,
  //! 1 or 2),Type is TopAbs_EDGE, Closed is true if it
  //! is a closed edge, BegInf is true if the Edge is
  //! infinite at the beginning, EndInf is true if the
  //! edge is infinite at the end.
  //!
  //! For a Vertex : Index is the index of the vertex in
  //! the edge (1 or 2), Type is TopAbsVERTEX, all the
  //! other fields have no meanning.
  Standard_EXPORT Sweep_NumShape(const int              Index,
                                 const TopAbs_ShapeEnum Type,
                                 const bool             Closed = false,
                                 const bool             BegInf = false,
                                 const bool             EndInf = false);

  //! Reinitialize a simple indexed edge.
  //!
  //! For an Edge : Index is the number of vertices (0,
  //! 1 or 2),Type is TopAbs_EDGE, Closed is true if it
  //! is a closed edge, BegInf is true if the Edge is
  //! infinite at the beginning, EndInf is true if the
  //! edge is infinite at the end.
  //!
  //! For a Vertex : Index is the index of the vertex in
  //! the edge (1 or 2), Type is TopAbsVERTEX, Closed is
  //! true if it is the vertex of a closed edge, all the
  //! other fields have no meanning.
  Standard_EXPORT void Init(const int              Index,
                            const TopAbs_ShapeEnum Type,
                            const bool             Closed = false,
                            const bool             BegInf = false,
                            const bool             EndInf = false);

  int Index() const;

  TopAbs_ShapeEnum Type() const;

  bool Closed() const;

  bool BegInfinite() const;

  bool EndInfinite() const;

  Standard_EXPORT TopAbs_Orientation Orientation() const;

private:
  TopAbs_ShapeEnum myType;
  int              myIndex;
  bool             myClosed;
  bool             myBegInf;
  bool             myEndInf;
};
// Created on: 1993-02-03
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

//=================================================================================================

inline int Sweep_NumShape::Index() const
{
  return myIndex;
}

//=================================================================================================

inline TopAbs_ShapeEnum Sweep_NumShape::Type() const
{
  return myType;
}

//=================================================================================================

inline bool Sweep_NumShape::Closed() const
{
  return myClosed;
}

//=================================================================================================

inline bool Sweep_NumShape::BegInfinite() const
{
  return myBegInf;
}

//=================================================================================================

inline bool Sweep_NumShape::EndInfinite() const
{
  return myEndInf;
}


