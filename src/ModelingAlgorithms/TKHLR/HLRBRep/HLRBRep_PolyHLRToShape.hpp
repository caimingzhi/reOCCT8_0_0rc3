#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
// Created on: 1992-08-21
// Created by: Christophe MARION
// Copyright (c) 1992-1999 Matra Datavision
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


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt2d.hpp>
#include <TopoDS_Shape.hpp>

//! Contains the colors of a shape.
class HLRBRep_BiPnt2D
{
public:
  DEFINE_STANDARD_ALLOC

  HLRBRep_BiPnt2D()
      : myRg1Line(false),
        myRgNLine(false),
        myOutLine(false),
        myIntLine(false)
  {
  }

  HLRBRep_BiPnt2D(const double        x1,
                  const double        y1,
                  const double        x2,
                  const double        y2,
                  const TopoDS_Shape& S,
                  const bool          reg1,
                  const bool          regn,
                  const bool          outl,
                  const bool          intl)
      : myP1(x1, y1),
        myP2(x2, y2),
        myShape(S),
        myRg1Line(reg1),
        myRgNLine(regn),
        myOutLine(outl),
        myIntLine(intl)
  {
  }

  HLRBRep_BiPnt2D(const gp_XY&        thePoint1,
                  const gp_XY&        thePoint2,
                  const TopoDS_Shape& S,
                  const bool          reg1,
                  const bool          regn,
                  const bool          outl,
                  const bool          intl)
      : myP1(thePoint1),
        myP2(thePoint2),
        myShape(S),
        myRg1Line(reg1),
        myRgNLine(regn),
        myOutLine(outl),
        myIntLine(intl)
  {
  }

  const gp_Pnt2d& P1() const { return myP1; }

  const gp_Pnt2d& P2() const { return myP2; }

  const TopoDS_Shape& Shape() const { return myShape; }

  void Shape(const TopoDS_Shape& S) { myShape = S; }

  bool Rg1Line() const { return myRg1Line; }

  void Rg1Line(const bool B) { myRg1Line = B; }

  bool RgNLine() const { return myRgNLine; }

  void RgNLine(const bool B) { myRgNLine = B; }

  bool OutLine() const { return myOutLine; }

  void OutLine(const bool B) { myOutLine = B; }

  bool IntLine() const { return myIntLine; }

  void IntLine(const bool B) { myIntLine = B; }

private:
  gp_Pnt2d     myP1;
  gp_Pnt2d     myP2;
  TopoDS_Shape myShape;
  bool         myRg1Line;
  bool         myRgNLine;
  bool         myOutLine;
  bool         myIntLine;
};


#include <NCollection_List.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
class HLRBRep_PolyAlgo;
class TopoDS_Shape;

//! A framework for filtering the computation
//! results of an HLRBRep_Algo algorithm by extraction.
//! From the results calculated by the algorithm on
//! a shape, a filter returns the type of edge you
//! want to identify. You can choose any of the following types of output:
//! -   visible sharp edges
//! -   hidden sharp edges
//! -   visible smooth edges
//! -   hidden smooth edges
//! -   visible sewn edges
//! -   hidden sewn edges
//! -   visible outline edges
//! -   hidden outline edges.
//! -   visible isoparameters and
//! -   hidden isoparameters.
//! Sharp edges present a C0 continuity (non G1).
//! Smooth edges present a G1 continuity (non G2).
//! Sewn edges present a C2 continuity.
//! The result is composed of 2D edges in the
//! projection plane of the view which the
//! algorithm has worked with. These 2D edges
//! are not included in the data structure of the visualized shape.
//! In order to obtain a complete image, you must
//! combine the shapes given by each of the chosen filters.
//! The construction of the shape does not call a
//! new computation of the algorithm, but only
//! reads its internal results.
class HLRBRep_PolyHLRToShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a framework for filtering the results
  //! of the HLRBRep_Algo algorithm, A.
  //! Use the extraction filters to obtain the results you want for A.
  Standard_EXPORT HLRBRep_PolyHLRToShape();

  Standard_EXPORT void Update(const occ::handle<HLRBRep_PolyAlgo>& A);

  void Show();

  void Hide();

  TopoDS_Shape VCompound();

  TopoDS_Shape VCompound(const TopoDS_Shape& S);

  //! Sets the extraction filter for visible smooth edges.
  TopoDS_Shape Rg1LineVCompound();

  TopoDS_Shape Rg1LineVCompound(const TopoDS_Shape& S);

  //! Sets the extraction filter for visible sewn edges.
  TopoDS_Shape RgNLineVCompound();

  TopoDS_Shape RgNLineVCompound(const TopoDS_Shape& S);

  TopoDS_Shape OutLineVCompound();

  //! Sets the extraction filter for visible outlines.
  TopoDS_Shape OutLineVCompound(const TopoDS_Shape& S);

  TopoDS_Shape HCompound();

  TopoDS_Shape HCompound(const TopoDS_Shape& S);

  TopoDS_Shape Rg1LineHCompound();

  //! Sets the extraction filter for hidden smooth edges.
  TopoDS_Shape Rg1LineHCompound(const TopoDS_Shape& S);

  TopoDS_Shape RgNLineHCompound();

  //! Sets the extraction filter for hidden sewn edges.
  TopoDS_Shape RgNLineHCompound(const TopoDS_Shape& S);

  TopoDS_Shape OutLineHCompound();

  //! Sets the extraction filter for hidden outlines.
  //! Hidden outlines occur, for instance, in tori. In
  //! this case, the inner outlines of the torus seen on its side are hidden.
  TopoDS_Shape OutLineHCompound(const TopoDS_Shape& S);

private:
  Standard_EXPORT TopoDS_Shape InternalCompound(const int           typ,
                                                const bool          visible,
                                                const TopoDS_Shape& S);

  occ::handle<HLRBRep_PolyAlgo>     myAlgo;
  NCollection_List<HLRBRep_BiPnt2D> myBiPntVis;
  NCollection_List<HLRBRep_BiPnt2D> myBiPntHid;
  bool                              myHideMode;
};
// Created on: 1993-11-02
// Created by: Christophe MARION
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

#include <TopoDS_Shape.hpp>

//=================================================================================================

inline void HLRBRep_PolyHLRToShape::Show()
{
  myHideMode = false;
}

//=================================================================================================

inline void HLRBRep_PolyHLRToShape::Hide()
{
  myHideMode = true;
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::VCompound()
{
  return InternalCompound(4, true, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::VCompound(const TopoDS_Shape& S)
{
  return InternalCompound(4, true, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::Rg1LineVCompound()
{
  return InternalCompound(2, true, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::Rg1LineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(2, true, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::RgNLineVCompound()
{
  return InternalCompound(3, true, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::RgNLineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(3, true, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::OutLineVCompound()
{
  return InternalCompound(1, true, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::OutLineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(1, true, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::HCompound()
{
  return InternalCompound(4, false, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::HCompound(const TopoDS_Shape& S)
{
  return InternalCompound(4, false, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::Rg1LineHCompound()
{
  return InternalCompound(2, false, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::Rg1LineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(2, false, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::RgNLineHCompound()
{
  return InternalCompound(3, false, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::RgNLineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(3, false, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::OutLineHCompound()
{
  return InternalCompound(1, false, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_PolyHLRToShape::OutLineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(1, false, S);
}


