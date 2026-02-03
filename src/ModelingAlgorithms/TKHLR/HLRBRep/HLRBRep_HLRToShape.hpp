// Created on: 1993-10-11
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

#ifndef _HLRBRep_HLRToShape_HeaderFile
#define _HLRBRep_HLRToShape_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <HLRBRep_TypeOfResultingEdge.hpp>
class HLRBRep_Algo;
class TopoDS_Shape;
class HLRBRep_Data;
class HLRBRep_EdgeData;

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
//! The methods of this shape are almost identic to those of the HLRBrep_PolyHLRToShape class.
class HLRBRep_HLRToShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a framework for filtering the
  //! results of the HLRBRep_Algo algorithm, A.
  //! Use the extraction filters to obtain the results you want for A.
  Standard_EXPORT HLRBRep_HLRToShape(const occ::handle<HLRBRep_Algo>& A);

  //! Return visible sharp edges (of C0-continuity).
  TopoDS_Shape VCompound();

  //! Return visible sharp edges (of C0-continuity) of specified shape.
  TopoDS_Shape VCompound(const TopoDS_Shape& S);

  //! Return visible smooth edges (G1-continuity between two surfaces).
  TopoDS_Shape Rg1LineVCompound();

  //! Return visible smooth edges (G1-continuity between two surfaces) of specified shape.
  TopoDS_Shape Rg1LineVCompound(const TopoDS_Shape& S);

  //! Return visible sewn edges (of CN-continuity on one surface).
  TopoDS_Shape RgNLineVCompound();

  //! Return visible sewn edges (of CN-continuity on one surface) of specified shape.
  TopoDS_Shape RgNLineVCompound(const TopoDS_Shape& S);

  //! Return visible outline edges ("silhouette").
  TopoDS_Shape OutLineVCompound();

  //! Return visible outline edges ("silhouette").
  TopoDS_Shape OutLineVCompound3d();

  //! Return visible outline edges ("silhouette") of specified shape.
  TopoDS_Shape OutLineVCompound(const TopoDS_Shape& S);

  //! Return visible isoparameters.
  TopoDS_Shape IsoLineVCompound();

  //! Return visible isoparameters of specified shape.
  TopoDS_Shape IsoLineVCompound(const TopoDS_Shape& S);

  //! Return hidden sharp edges (of C0-continuity).
  TopoDS_Shape HCompound();

  //! Return hidden sharp edges (of C0-continuity) of specified shape.
  TopoDS_Shape HCompound(const TopoDS_Shape& S);

  //! Return hidden smooth edges (G1-continuity between two surfaces).
  TopoDS_Shape Rg1LineHCompound();

  //! Return hidden smooth edges (G1-continuity between two surfaces) of specified shape.
  TopoDS_Shape Rg1LineHCompound(const TopoDS_Shape& S);

  //! Return hidden sewn edges (of CN-continuity on one surface).
  TopoDS_Shape RgNLineHCompound();

  //! Return hidden sewn edges (of CN-continuity on one surface) of specified shape.
  TopoDS_Shape RgNLineHCompound(const TopoDS_Shape& S);

  //! Return hidden outline edges ("silhouette").
  TopoDS_Shape OutLineHCompound();

  //! Return hidden outline edges ("silhouette") of specified shape.
  TopoDS_Shape OutLineHCompound(const TopoDS_Shape& S);

  //! Return hidden isoparameters.
  TopoDS_Shape IsoLineHCompound();

  //! Return hidden isoparameters of specified shape.
  TopoDS_Shape IsoLineHCompound(const TopoDS_Shape& S);

  //! Returns compound of resulting edges
  //! of required type and visibility,
  //! taking into account the kind of space
  //! (2d or 3d)
  TopoDS_Shape CompoundOfEdges(const HLRBRep_TypeOfResultingEdge type,
                               const bool                        visible,
                               const bool                        In3d);

  //! For specified shape
  //! returns compound of resulting edges
  //! of required type and visibility,
  //! taking into account the kind of space
  //! (2d or 3d)
  TopoDS_Shape CompoundOfEdges(const TopoDS_Shape&               S,
                               const HLRBRep_TypeOfResultingEdge type,
                               const bool                        visible,
                               const bool                        In3d);

private:
  Standard_EXPORT TopoDS_Shape InternalCompound(const int           typ,
                                                const bool          visible,
                                                const TopoDS_Shape& S,
                                                const bool          In3d = false);

  Standard_EXPORT void DrawFace(const bool                 visible,
                                const int                  typ,
                                const int                  iface,
                                occ::handle<HLRBRep_Data>& DS,
                                TopoDS_Shape&              Result,
                                bool&                      added,
                                const bool                 In3d = false) const;

  Standard_EXPORT void DrawEdge(const bool        visible,
                                const bool        inFace,
                                const int         typ,
                                HLRBRep_EdgeData& ed,
                                TopoDS_Shape&     Result,
                                bool&             added,
                                const bool        In3d = false) const;

  occ::handle<HLRBRep_Algo> myAlgo;
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

inline TopoDS_Shape HLRBRep_HLRToShape::VCompound()
{
  return InternalCompound(5, true, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::VCompound(const TopoDS_Shape& S)
{
  return InternalCompound(5, true, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::Rg1LineVCompound()
{
  return InternalCompound(3, true, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::Rg1LineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(3, true, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::RgNLineVCompound()
{
  return InternalCompound(4, true, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::RgNLineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(4, true, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::OutLineVCompound()
{
  return InternalCompound(2, true, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::OutLineVCompound3d()
{
  return InternalCompound(2, true, TopoDS_Shape(), true);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::OutLineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(2, true, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::IsoLineVCompound()
{
  return InternalCompound(1, true, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::IsoLineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(1, true, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::HCompound()
{
  return InternalCompound(5, false, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::HCompound(const TopoDS_Shape& S)
{
  return InternalCompound(5, false, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::Rg1LineHCompound()
{
  return InternalCompound(3, false, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::Rg1LineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(3, false, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::RgNLineHCompound()
{
  return InternalCompound(4, false, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::RgNLineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(4, false, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::OutLineHCompound()
{
  return InternalCompound(2, false, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::OutLineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(2, false, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::IsoLineHCompound()
{
  return InternalCompound(1, false, TopoDS_Shape());
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::IsoLineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(1, false, S);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::CompoundOfEdges(const HLRBRep_TypeOfResultingEdge type,
                                                        const bool                        visible,
                                                        const bool                        In3d)
{
  return InternalCompound(type, visible, TopoDS_Shape(), In3d);
}

//=================================================================================================

inline TopoDS_Shape HLRBRep_HLRToShape::CompoundOfEdges(const TopoDS_Shape&               S,
                                                        const HLRBRep_TypeOfResultingEdge type,
                                                        const bool                        visible,
                                                        const bool                        In3d)
{
  return InternalCompound(type, visible, S, In3d);
}


#endif // _HLRBRep_HLRToShape_HeaderFile
