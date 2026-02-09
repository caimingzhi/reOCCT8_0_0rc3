#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRep_ShapeIntersector.hpp>
#include <TopOpeBRep_ShapeIntersector2d.hpp>
#include <TopOpeBRep_FacesFiller.hpp>
#include <TopOpeBRep_EdgesFiller.hpp>
#include <TopOpeBRep_FaceEdgeFiller.hpp>
#include <TopOpeBRepTool_PShapeClassifier.hpp>
class TopoDS_Shape;
class TopOpeBRepDS_HDataStructure;
class TopoDS_Face;

class TopOpeBRep_DSFiller
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_DSFiller();

  Standard_EXPORT ~TopOpeBRep_DSFiller();

  Standard_EXPORT TopOpeBRepTool_PShapeClassifier PShapeClassifier() const;

  Standard_EXPORT void Insert(const TopoDS_Shape&                             S1,
                              const TopoDS_Shape&                             S2,
                              const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                              const bool                                      orientFORWARD = true);

  Standard_EXPORT void InsertIntersection(const TopoDS_Shape&                             S1,
                                          const TopoDS_Shape&                             S2,
                                          const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                                          const bool orientFORWARD = true);

  Standard_EXPORT void Complete(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT void Insert2d(const TopoDS_Shape&                             S1,
                                const TopoDS_Shape&                             S2,
                                const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT void InsertIntersection2d(const TopoDS_Shape&                             S1,
                                            const TopoDS_Shape&                             S2,
                                            const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT bool IsMadeOf1d(const TopoDS_Shape& S) const;

  Standard_EXPORT bool IsContext1d(const TopoDS_Shape& S) const;

  Standard_EXPORT void Insert1d(const TopoDS_Shape&                             S1,
                                const TopoDS_Shape&                             S2,
                                const TopoDS_Face&                              F1,
                                const TopoDS_Face&                              F2,
                                const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                                const bool orientFORWARD = false);

  Standard_EXPORT TopOpeBRep_ShapeIntersector& ChangeShapeIntersector();

  Standard_EXPORT TopOpeBRep_ShapeIntersector2d& ChangeShapeIntersector2d();

  Standard_EXPORT TopOpeBRep_FacesFiller& ChangeFacesFiller();

  Standard_EXPORT TopOpeBRep_EdgesFiller& ChangeEdgesFiller();

  Standard_EXPORT TopOpeBRep_FaceEdgeFiller& ChangeFaceEdgeFiller();

  Standard_EXPORT void GapFiller(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS) const;

  Standard_EXPORT void CompleteDS(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS) const;

  Standard_EXPORT void Filter(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS) const;

  Standard_EXPORT void Reducer(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS) const;

  Standard_EXPORT void RemoveUnsharedGeometry(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT void Checker(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS) const;

  Standard_EXPORT void CompleteDS2d(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS) const;

private:
  Standard_EXPORT bool CheckInsert(const TopoDS_Shape& S1, const TopoDS_Shape& S2) const;

  Standard_EXPORT bool ClearShapeSameDomain(const TopoDS_Shape&                             S1,
                                            const TopoDS_Shape&                             S2,
                                            const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  TopOpeBRep_ShapeIntersector     myShapeIntersector;
  TopOpeBRep_ShapeIntersector2d   myShapeIntersector2d;
  TopOpeBRep_FacesFiller          myFacesFiller;
  TopOpeBRep_EdgesFiller          myEdgesFiller;
  TopOpeBRep_FaceEdgeFiller       myFaceEdgeFiller;
  TopOpeBRepTool_PShapeClassifier myPShapeClassifier;
};
