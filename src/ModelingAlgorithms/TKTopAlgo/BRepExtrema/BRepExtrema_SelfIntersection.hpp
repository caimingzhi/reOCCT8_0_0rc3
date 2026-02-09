#pragma once

#include <BRepExtrema_OverlapTool.hpp>

#include <TopoDS.hpp>

class BRepExtrema_SelfIntersection : public BRepExtrema_ElementFilter
{
  friend class BRepExtrema_OverlapTool;

public:
  Standard_EXPORT BRepExtrema_SelfIntersection(const double theTolerance = 0.0);

  Standard_EXPORT BRepExtrema_SelfIntersection(const TopoDS_Shape& theShape,
                                               const double        theTolerance = 0.0);

public:
  double Tolerance() const { return myTolerance; }

  void SetTolerance(const double theTolerance) { myTolerance = theTolerance; }

  Standard_EXPORT bool LoadShape(const TopoDS_Shape& theShape);

  Standard_EXPORT void Perform();

  bool IsDone() const { return myOverlapTool.IsDone(); }

  const NCollection_DataMap<int, TColStd_PackedMapOfInteger>& OverlapElements() const
  {
    return myOverlapTool.OverlapSubShapes1();
  }

  const TopoDS_Face& GetSubShape(const int theID) const
  {
    return TopoDS::Face(myFaceList.Value(theID));
  }

  const occ::handle<BRepExtrema_TriangleSet>& ElementSet() const { return myElementSet; }

#ifdef OVERLAP_TOOL_OUTPUT_TRIANGLES

  const TColStd_PackedMapOfInteger& OverlapTriangles() const
  {
    return myOverlapTool.OverlapTriangles1();
  }
#endif

protected:
  Standard_EXPORT BRepExtrema_ElementFilter::FilterResult PreCheckElements(
    const int theIndex1,
    const int theIndex2) override;

  Standard_EXPORT BRepExtrema_ElementFilter::FilterResult isRegularSharedVertex(
    const BVH_Vec3d& theSharedVert,
    const BVH_Vec3d& theTrng1Vtxs1,
    const BVH_Vec3d& theTrng1Vtxs2,
    const BVH_Vec3d& theTrng2Vtxs1,
    const BVH_Vec3d& theTrng2Vtxs2);

  Standard_EXPORT BRepExtrema_ElementFilter::FilterResult isRegularSharedEdge(
    const BVH_Vec3d& theTrng1Vtxs0,
    const BVH_Vec3d& theTrng1Vtxs1,
    const BVH_Vec3d& theTrng1Vtxs2,
    const BVH_Vec3d& theTrng2Vtxs2);

private:
  double myTolerance;

  bool myIsInit;

  NCollection_Vector<TopoDS_Shape> myFaceList;

  occ::handle<BRepExtrema_TriangleSet> myElementSet;

  BRepExtrema_OverlapTool myOverlapTool;
};
