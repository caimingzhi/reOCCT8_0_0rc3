#pragma once

#include <BRepExtrema_TriangleSet.hpp>
#include <BRepExtrema_ElementFilter.hpp>
#include <NCollection_DataMap.hpp>
#include <TColStd_PackedMapOfInteger.hpp>
#include <BVH_Traverse.hpp>

//! Enables storing of individual overlapped triangles (useful for debug).
// #define OVERLAP_TOOL_OUTPUT_TRIANGLES

//! Tool class for for detection of overlapping of two BVH primitive sets.
//! This tool is not intended to be used independently, and is integrated
//! in other classes, implementing algorithms based on shape tessellation
//! (BRepExtrema_ShapeProximity and BRepExtrema_SelfIntersection).
//!
//! Note that input element sets may correspond to different shapes or to
//! the same shape. In first case, tessellations of two given shapes will
//! be tested for intersection (or overlapping, if tolerance is not zero).
//! In second case, tessellation of single shape will be tested for self-
//! intersections. Please note that algorithm results are approximate and
//! depend greatly on the quality of input tessellation(s).
class BRepExtrema_OverlapTool : public BVH_PairTraverse<double, 3>
{
public:
  //! Creates new uninitialized overlap tool.
  BRepExtrema_OverlapTool();

  //! Creates new overlap tool for the given element sets.
  BRepExtrema_OverlapTool(const occ::handle<BRepExtrema_TriangleSet>& theSet1,
                          const occ::handle<BRepExtrema_TriangleSet>& theSet2);

public:
  //! Loads the given element sets into the overlap tool.
  void LoadTriangleSets(const occ::handle<BRepExtrema_TriangleSet>& theSet1,
                        const occ::handle<BRepExtrema_TriangleSet>& theSet2);

  //! Performs searching of overlapped mesh elements.
  void Perform(const double theTolerance = 0.0);

  //! Is overlap test completed?
  bool IsDone() const { return myIsDone; }

  //! Marks test results as outdated.
  void MarkDirty() { myIsDone = false; }

  //! Returns set of overlapped sub-shapes of 1st shape (currently only faces are detected).
  const NCollection_DataMap<int, TColStd_PackedMapOfInteger>& OverlapSubShapes1() const
  {
    return myOverlapSubShapes1;
  }

  //! Returns set of overlapped sub-shapes of 2nd shape (currently only faces are detected).
  const NCollection_DataMap<int, TColStd_PackedMapOfInteger>& OverlapSubShapes2() const
  {
    return myOverlapSubShapes2;
  }

#ifdef OVERLAP_TOOL_OUTPUT_TRIANGLES
  //! Returns set of overlapped triangles from the 1st shape (for debug).
  const TColStd_PackedMapOfInteger& OverlapTriangles1() const { return myOverlapTriangles1; }

  //! Returns set of overlapped triangles from the 2nd shape (for debug).
  const TColStd_PackedMapOfInteger& OverlapTriangles2() const { return myOverlapTriangles2; }
#endif

  //! Sets filtering tool for preliminary checking pairs of mesh elements.
  void SetElementFilter(BRepExtrema_ElementFilter* theFilter) { myFilter = theFilter; }

public: //! @name Reject/Accept implementations
  //! Defines the rules for node rejection by bounding box
  Standard_EXPORT bool RejectNode(const BVH_Vec3d& theCornerMin1,
                                  const BVH_Vec3d& theCornerMax1,
                                  const BVH_Vec3d& theCornerMin2,
                                  const BVH_Vec3d& theCornerMax2,
                                  double&) const override;
  //! Defines the rules for leaf acceptance
  Standard_EXPORT bool Accept(const int theLeaf1, const int theLeaf2) override;

protected:
  //! Performs narrow-phase of overlap test (exact intersection).
  void intersectTrianglesExact(const int theTrgIdx1, const int theTrgIdx2);

  //! Performs narrow-phase of overlap test (intersection with non-zero tolerance).
  void intersectTrianglesToler(const int theTrgIdx1, const int theTrgIdx2, const double theToler);

private:
  //! Set of all mesh elements (triangles) of the 1st shape.
  occ::handle<BRepExtrema_TriangleSet> mySet1;
  //! Set of all mesh elements (triangles) of the 2nd shape.
  occ::handle<BRepExtrema_TriangleSet> mySet2;

  //! Filter for preliminary checking pairs of mesh elements.
  BRepExtrema_ElementFilter* myFilter;

  //! Resulted set of overlapped sub-shapes of 1st shape (only faces).
  NCollection_DataMap<int, TColStd_PackedMapOfInteger> myOverlapSubShapes1;
  //! Resulted set of overlapped sub-shapes of 2nd shape (only faces).
  NCollection_DataMap<int, TColStd_PackedMapOfInteger> myOverlapSubShapes2;

#ifdef OVERLAP_TOOL_OUTPUT_TRIANGLES
  //! Set of overlapped elements from the 1st shape (only triangles).
  TColStd_PackedMapOfInteger myOverlapTriangles1;
  //! Set of overlapped elements from the 2nd shape (only triangles).
  TColStd_PackedMapOfInteger myOverlapTriangles2;
#endif

  //! Is overlap test test completed?
  bool myIsDone;

  double myTolerance;
};
