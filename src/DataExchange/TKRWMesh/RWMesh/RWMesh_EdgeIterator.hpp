#pragma once

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

class RWMesh_EdgeIterator : public RWMesh_ShapeIterator
{
public:
  Standard_EXPORT RWMesh_EdgeIterator(const TDF_Label&       theLabel,
                                      const TopLoc_Location& theLocation,
                                      const bool             theToMapColors = false,
                                      const XCAFPrs_Style&   theStyle       = XCAFPrs_Style());

  Standard_EXPORT RWMesh_EdgeIterator(const TopoDS_Shape&  theShape,
                                      const XCAFPrs_Style& theStyle = XCAFPrs_Style());

  bool More() const override { return !myPolygon3D.IsNull(); }

  Standard_EXPORT void Next() override;

  const TopoDS_Edge& Edge() const { return myEdge; }

  const TopoDS_Shape& Shape() const override { return myEdge; }

  const occ::handle<Poly_Polygon3D>& Polygon3D() const { return myPolygon3D; }

  bool IsEmpty() const override { return myPolygon3D.IsNull() || myPolygon3D->NbNodes() < 1; }

public:
  int ElemLower() const override { return 1; }

  int ElemUpper() const override { return myPolygon3D->NbNodes(); }

public:
  int NbNodes() const override { return !myPolygon3D.IsNull() ? myPolygon3D->NbNodes() : 0; }

  int NodeLower() const override { return 1; }

  int NodeUpper() const override { return myPolygon3D->NbNodes(); }

public:
  gp_Pnt node(const int theNode) const override { return myPolygon3D->Nodes().Value(theNode); }

private:
  void resetEdge()
  {
    myPolygon3D.Nullify();
    myEdge.Nullify();
    resetShape();
  }

  void initEdge();

private:
  TopoDS_Edge                 myEdge;
  occ::handle<Poly_Polygon3D> myPolygon3D;
};
