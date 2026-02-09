#pragma once

#include <BRepExtrema_TriangleSet.hpp>
#include <BRepExtrema_ElementFilter.hpp>
#include <NCollection_DataMap.hpp>
#include <TColStd_PackedMapOfInteger.hpp>
#include <BVH_Traverse.hpp>

class BRepExtrema_OverlapTool : public BVH_PairTraverse<double, 3>
{
public:
  BRepExtrema_OverlapTool();

  BRepExtrema_OverlapTool(const occ::handle<BRepExtrema_TriangleSet>& theSet1,
                          const occ::handle<BRepExtrema_TriangleSet>& theSet2);

public:
  void LoadTriangleSets(const occ::handle<BRepExtrema_TriangleSet>& theSet1,
                        const occ::handle<BRepExtrema_TriangleSet>& theSet2);

  void Perform(const double theTolerance = 0.0);

  bool IsDone() const { return myIsDone; }

  void MarkDirty() { myIsDone = false; }

  const NCollection_DataMap<int, TColStd_PackedMapOfInteger>& OverlapSubShapes1() const
  {
    return myOverlapSubShapes1;
  }

  const NCollection_DataMap<int, TColStd_PackedMapOfInteger>& OverlapSubShapes2() const
  {
    return myOverlapSubShapes2;
  }

#ifdef OVERLAP_TOOL_OUTPUT_TRIANGLES

  const TColStd_PackedMapOfInteger& OverlapTriangles1() const { return myOverlapTriangles1; }

  const TColStd_PackedMapOfInteger& OverlapTriangles2() const { return myOverlapTriangles2; }
#endif

  void SetElementFilter(BRepExtrema_ElementFilter* theFilter) { myFilter = theFilter; }

public:
  Standard_EXPORT bool RejectNode(const BVH_Vec3d& theCornerMin1,
                                  const BVH_Vec3d& theCornerMax1,
                                  const BVH_Vec3d& theCornerMin2,
                                  const BVH_Vec3d& theCornerMax2,
                                  double&) const override;

  Standard_EXPORT bool Accept(const int theLeaf1, const int theLeaf2) override;

protected:
  void intersectTrianglesExact(const int theTrgIdx1, const int theTrgIdx2);

  void intersectTrianglesToler(const int theTrgIdx1, const int theTrgIdx2, const double theToler);

private:
  occ::handle<BRepExtrema_TriangleSet> mySet1;

  occ::handle<BRepExtrema_TriangleSet> mySet2;

  BRepExtrema_ElementFilter* myFilter;

  NCollection_DataMap<int, TColStd_PackedMapOfInteger> myOverlapSubShapes1;

  NCollection_DataMap<int, TColStd_PackedMapOfInteger> myOverlapSubShapes2;

#ifdef OVERLAP_TOOL_OUTPUT_TRIANGLES

  TColStd_PackedMapOfInteger myOverlapTriangles1;

  TColStd_PackedMapOfInteger myOverlapTriangles2;
#endif

  bool myIsDone;

  double myTolerance;
};
