#pragma once

#include <BVH_PrimitiveSet3d.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>

class BRepExtrema_TriangleSet : public BVH_PrimitiveSet3d
{
public:
  Standard_EXPORT BRepExtrema_TriangleSet();

  Standard_EXPORT BRepExtrema_TriangleSet(const NCollection_Vector<TopoDS_Shape>& theFaces);

  Standard_EXPORT ~BRepExtrema_TriangleSet() override;

public:
  Standard_EXPORT int Size() const override;

  Standard_EXPORT BVH_Box<double, 3> Box(const int theIndex) const override;

  using BVH_PrimitiveSet3d::Box;

  Standard_EXPORT double Center(const int theIndex, const int theAxis) const override;

  Standard_EXPORT void Swap(const int theIndex1, const int theIndex2) override;

public:
  Standard_EXPORT void Clear();

  Standard_EXPORT bool Init(const NCollection_Vector<TopoDS_Shape>& theShapes);

  Standard_EXPORT const BVH_Array3d& GetVertices() const { return myVertexArray; }

  Standard_EXPORT void GetVertices(const int  theIndex,
                                   BVH_Vec3d& theVertex1,
                                   BVH_Vec3d& theVertex2,
                                   BVH_Vec3d& theVertex3) const;

  Standard_EXPORT void GetVtxIndices(const int                theIndex,
                                     NCollection_Array1<int>& theVtxIndices) const;

  Standard_EXPORT int GetFaceID(const int theIndex) const;

  Standard_EXPORT int GetShapeIDOfVtx(const int theIndex) const;

  Standard_EXPORT int GetVtxIdxInShape(const int theIndex) const;

  Standard_EXPORT int GetTrgIdxInShape(const int theIndex) const;

private:
  bool initFace(const TopoDS_Face& theFace, const int theIndex);

  bool initEdge(const TopoDS_Edge& theEdge, const int theIndex);

  void initNodes(const NCollection_Array1<gp_Pnt>& theNodes,
                 const gp_Trsf&                    theTrsf,
                 const int                         theIndex);

protected:
  BVH_Array4i myTriangles;

  BVH_Array3d myVertexArray;

  NCollection_Vector<int> myShapeIdxOfVtxVec;

  NCollection_Vector<int> myNumVtxInShapeVec;

  NCollection_Vector<int> myNumTrgInShapeVec;

  NCollection_DataMap<int, int> myTrgIdxMap;

public:
  DEFINE_STANDARD_RTTIEXT(BRepExtrema_TriangleSet, BVH_PrimitiveSet3d)
};
