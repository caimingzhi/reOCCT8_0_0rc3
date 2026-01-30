// Copyright (c) 2025 OPEN CASCADE SAS
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

#ifndef _RWMesh_EdgeIterator_HeaderFile
#define _RWMesh_EdgeIterator_HeaderFile

#include <NCollection_DataMap.hpp>
#include <Poly_Polygon3D.hpp>
#include <RWMesh_ShapeIterator.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Edge.hpp>
#include <XCAFPrs_Style.hpp>
#include <gp_Trsf.hpp>

#include <algorithm>

class TDF_Label;

//! Auxiliary class to iterate through edges.
//! Provides functionality to iterate through the edges of a shape.
//! It inherits from `RWMesh_ShapeIterator` and implements
//! methods to access and manipulate edge data.
class RWMesh_EdgeIterator : public RWMesh_ShapeIterator
{
public:
  //! Main constructor.
  //! @param[in] theLabel The label of the shape.
  //! @param[in] theLocation The location of the shape.
  //! @param[in] theToMapColors Flag to indicate if colors should be mapped.
  //! @param[in] theStyle The style of the shape.
  Standard_EXPORT RWMesh_EdgeIterator(const TDF_Label&       theLabel,
                                      const TopLoc_Location& theLocation,
                                      const bool             theToMapColors = false,
                                      const XCAFPrs_Style&   theStyle       = XCAFPrs_Style());

  //! Auxiliary constructor.
  //! @param[in] theShape The shape to iterate.
  //! @param[in] theStyle The style of the shape.
  Standard_EXPORT RWMesh_EdgeIterator(const TopoDS_Shape&  theShape,
                                      const XCAFPrs_Style& theStyle = XCAFPrs_Style());

  //! Return true if iterator points to the valid triangulation.
  bool More() const override { return !myPolygon3D.IsNull(); }

  //! Find next value.
  Standard_EXPORT void Next() override;

  //! Return current edge.
  const TopoDS_Edge& Edge() const { return myEdge; }

  //! Return current edge.
  const TopoDS_Shape& Shape() const override { return myEdge; }

  //! Return current edge data.
  const occ::handle<Poly_Polygon3D>& Polygon3D() const { return myPolygon3D; }

  //! Return true if geometry data is defined.
  bool IsEmpty() const override { return myPolygon3D.IsNull() || myPolygon3D->NbNodes() < 1; }

public:
  //! Lower element index in current triangulation.
  int ElemLower() const override { return 1; }

  //! Upper element index in current triangulation.
  int ElemUpper() const override { return myPolygon3D->NbNodes(); }

public:
  //! Return number of nodes for the current edge.
  int NbNodes() const override { return !myPolygon3D.IsNull() ? myPolygon3D->NbNodes() : 0; }

  //! Lower node index in current triangulation.
  int NodeLower() const override { return 1; }

  //! Upper node index in current triangulation.
  int NodeUpper() const override { return myPolygon3D->NbNodes(); }

public:
  //! Return the node with specified index with applied transformation.
  gp_Pnt node(const int theNode) const override { return myPolygon3D->Nodes().Value(theNode); }

private:
  //! Reset information for current edge.
  void resetEdge()
  {
    myPolygon3D.Nullify();
    myEdge.Nullify();
    resetShape();
  }

  //! Initialize edge properties.
  void initEdge();

private:
  TopoDS_Edge                 myEdge;      //!< current edge
  occ::handle<Poly_Polygon3D> myPolygon3D; //!< geometry of current edge
};

#endif // _RWMesh_EdgeIterator_HeaderFile
