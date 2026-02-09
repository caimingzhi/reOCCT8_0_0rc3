#pragma once

#include <NCollection_DataMap.hpp>
#include <Poly_Polygon3D.hpp>
#include <RWMesh_ShapeIterator.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Vertex.hpp>
#include <XCAFPrs_Style.hpp>
#include <gp_Trsf.hpp>

#include <algorithm>

class TDF_Label;

class RWMesh_VertexIterator : public RWMesh_ShapeIterator
{
public:
  Standard_EXPORT RWMesh_VertexIterator(const TDF_Label&       theLabel,
                                        const TopLoc_Location& theLocation,
                                        const bool             theToMapColors = false,
                                        const XCAFPrs_Style&   theStyle       = XCAFPrs_Style());

  Standard_EXPORT RWMesh_VertexIterator(const TopoDS_Shape&  theShape,
                                        const XCAFPrs_Style& theStyle = XCAFPrs_Style());

  bool More() const override { return !myVertex.IsNull(); }

  Standard_EXPORT void Next() override;

  const TopoDS_Vertex& Vertex() const { return myVertex; }

  const TopoDS_Shape& Shape() const override { return myVertex; }

  const gp_Pnt& Point() const { return myPoint; }

  bool IsEmpty() const override { return myVertex.IsNull(); }

public:
  int ElemLower() const override { return 1; }

  int ElemUpper() const override { return 1; }

public:
  int NbNodes() const override { return 1; }

  int NodeLower() const override { return 1; }

  int NodeUpper() const override { return 1; }

public:
  gp_Pnt node(const int) const override { return myPoint; }

private:
  void resetVertex()
  {
    myVertex.Nullify();
    resetShape();
  }

  void initVertex();

private:
  TopoDS_Vertex myVertex;
  gp_Pnt        myPoint;
};
