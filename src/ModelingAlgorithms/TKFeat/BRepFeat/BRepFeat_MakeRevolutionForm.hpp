#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Ax1.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <BRepFeat_RibSlot.hpp>
#include <Standard_Integer.hpp>
class Geom_Plane;
class TopoDS_Shape;
class TopoDS_Wire;
class TopoDS_Edge;
class TopoDS_Face;
class gp_Pnt;

//! MakeRevolutionForm Generates a surface of
//! revolution in the feature as it slides along a
//! revolved face in the basis shape.
//! The semantics of mechanical features is built
//! around giving thickness to a contour. This
//! thickness can either be unilateral - on one side
//! of the contour - or bilateral - on both sides. As
//! in the semantics of form features, the thickness
//! is defined by construction of shapes in specific contexts.
//! The development contexts differ, however,in
//! case of mechanical features. Here they include extrusion:
//! -   to a limiting face of the basis shape
//! -   to or from a limiting plane
//! -   to a height.
class BRepFeat_MakeRevolutionForm : public BRepFeat_RibSlot
{
public:
  DEFINE_STANDARD_ALLOC

  //! initializes the linear form class.
  BRepFeat_MakeRevolutionForm();

  //! a contour W, a shape Sbase and a plane P are initialized to serve as
  //! the basic elements in the construction of the rib or groove. The axis Axis of the
  //! revolved surface in the basis shape defines the feature's axis of revolution.
  //! Height1 and Height2 may be used as limits to the construction of the feature.
  //! Fuse offers a choice between:
  //! -   removing matter with a Boolean cut using the setting 0 in case of the groove
  //! -   adding matter with Boolean fusion using the setting 1 in case of the rib.
  BRepFeat_MakeRevolutionForm(const TopoDS_Shape&            Sbase,
                              const TopoDS_Wire&             W,
                              const occ::handle<Geom_Plane>& Plane,
                              const gp_Ax1&                  Axis,
                              const double                   Height1,
                              const double                   Height2,
                              const int                      Fuse,
                              bool&                          Sliding);

  //! Initializes this construction algorithm
  //! A contour W, a shape Sbase and a plane P are initialized to serve as the basic elements
  //! in the construction of the rib or groove. The axis Axis of the revolved surface in the basis
  //! shape defines the feature's axis of revolution. Height1 and Height2 may be
  //! used as limits to the construction of the feature.
  //! Fuse offers a choice between:
  //! -   removing matter with a Boolean cut using the setting 0 in case of the groove
  //! -   adding matter with Boolean fusion using the setting 1 in case of the rib.
  Standard_EXPORT void Init(const TopoDS_Shape&            Sbase,
                            const TopoDS_Wire&             W,
                            const occ::handle<Geom_Plane>& Plane,
                            const gp_Ax1&                  Axis,
                            const double                   Height1,
                            const double                   Height2,
                            const int                      Fuse,
                            bool&                          Sliding);

  //! Indicates that the edge <E> will slide on the face
  //! <OnFace>. Raises ConstructionError if the face does not belong to the
  //! basis shape, or the edge to the prismed shape.
  Standard_EXPORT void Add(const TopoDS_Edge& E, const TopoDS_Face& OnFace);

  //! Performs a prism from the wire to the plane
  //! along the basis shape S. Reconstructs the feature topologically.
  Standard_EXPORT void Perform();

  Standard_EXPORT bool Propagate(NCollection_List<TopoDS_Shape>& L,
                                 const TopoDS_Face&              F,
                                 const gp_Pnt&                   FPoint,
                                 const gp_Pnt&                   LPoint,
                                 bool&                           falseside);

private:
  gp_Ax1                  myAxe;
  double                  myHeight1;
  double                  myHeight2;
  bool                    mySliding;
  occ::handle<Geom_Plane> myPln;
  double                  myBnd;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                 mySlface;
  NCollection_List<TopoDS_Shape> myListOfEdges;
  double                         myTol;
  double                         myAngle1;
  double                         myAngle2;
};
// Created on: 1997-10-17
// Created by: Olga KOULECHOVA
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

//=================================================================================================

inline BRepFeat_MakeRevolutionForm::BRepFeat_MakeRevolutionForm()
    : myHeight1(0.0),
      myHeight2(0.0),
      mySliding(false),
      myBnd(0.0),
      myTol(0.0),
      myAngle1(RealLast()),
      myAngle2(RealLast())
{
}

//=================================================================================================

inline BRepFeat_MakeRevolutionForm::BRepFeat_MakeRevolutionForm(const TopoDS_Shape& Sbase,
                                                                const TopoDS_Wire&  W,
                                                                const occ::handle<Geom_Plane>& P,
                                                                const gp_Ax1&                  Axis,
                                                                const double                   H1,
                                                                const double                   H2,
                                                                const int                      Fuse,
                                                                bool& Sliding)

{
  Init(Sbase, W, P, Axis, H1, H2, Fuse, Sliding);
}


