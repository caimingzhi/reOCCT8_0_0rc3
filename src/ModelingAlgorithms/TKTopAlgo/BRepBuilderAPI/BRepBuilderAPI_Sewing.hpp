#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt.hpp>

#include <Message_ProgressRange.hpp>

class BRepTools_ReShape;
class TopoDS_Edge;
class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class Geom2d_Curve;
class Geom_Curve;

class BRepBuilderAPI_Sewing : public Standard_Transient
{

public:
  Standard_EXPORT BRepBuilderAPI_Sewing(const double tolerance = 1.0e-06,
                                        const bool   option1   = true,
                                        const bool   option2   = true,
                                        const bool   option3   = true,
                                        const bool   option4   = false);

  Standard_EXPORT void Init(const double tolerance = 1.0e-06,
                            const bool   option1   = true,
                            const bool   option2   = true,
                            const bool   option3   = true,
                            const bool   option4   = false);

  Standard_EXPORT void Load(const TopoDS_Shape& shape);

  Standard_EXPORT void Add(const TopoDS_Shape& shape);

  Standard_EXPORT void Perform(const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT const TopoDS_Shape& SewedShape() const;

  Standard_EXPORT void SetContext(const occ::handle<BRepTools_ReShape>& theContext);

  Standard_EXPORT const occ::handle<BRepTools_ReShape>& GetContext() const;

  Standard_EXPORT int NbFreeEdges() const;

  Standard_EXPORT const TopoDS_Edge& FreeEdge(const int index) const;

  Standard_EXPORT int NbMultipleEdges() const;

  Standard_EXPORT const TopoDS_Edge& MultipleEdge(const int index) const;

  Standard_EXPORT int NbContigousEdges() const;

  Standard_EXPORT const TopoDS_Edge& ContigousEdge(const int index) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& ContigousEdgeCouple(const int index) const;

  Standard_EXPORT bool IsSectionBound(const TopoDS_Edge& section) const;

  Standard_EXPORT const TopoDS_Edge& SectionToBoundary(const TopoDS_Edge& section) const;

  Standard_EXPORT int NbDegeneratedShapes() const;

  Standard_EXPORT const TopoDS_Shape& DegeneratedShape(const int index) const;

  Standard_EXPORT bool IsDegenerated(const TopoDS_Shape& shape) const;

  Standard_EXPORT bool IsModified(const TopoDS_Shape& shape) const;

  Standard_EXPORT const TopoDS_Shape& Modified(const TopoDS_Shape& shape) const;

  Standard_EXPORT bool IsModifiedSubShape(const TopoDS_Shape& shape) const;

  Standard_EXPORT TopoDS_Shape ModifiedSubShape(const TopoDS_Shape& shape) const;

  Standard_EXPORT void Dump() const;

  Standard_EXPORT int NbDeletedFaces() const;

  Standard_EXPORT const TopoDS_Face& DeletedFace(const int index) const;

  Standard_EXPORT TopoDS_Face WhichFace(const TopoDS_Edge& theEdg, const int index = 1) const;

  bool SameParameterMode() const;

  void SetSameParameterMode(const bool SameParameterMode);

  double Tolerance() const;

  void SetTolerance(const double theToler);

  double MinTolerance() const;

  void SetMinTolerance(const double theMinToler);

  double MaxTolerance() const;

  void SetMaxTolerance(const double theMaxToler);

  bool FaceMode() const;

  void SetFaceMode(const bool theFaceMode);

  bool FloatingEdgesMode() const;

  void SetFloatingEdgesMode(const bool theFloatingEdgesMode);

  bool LocalTolerancesMode() const;

  void SetLocalTolerancesMode(const bool theLocalTolerancesMode);

  void SetNonManifoldMode(const bool theNonManifoldMode);

  bool NonManifoldMode() const;

  DEFINE_STANDARD_RTTIEXT(BRepBuilderAPI_Sewing, Standard_Transient)

protected:
  Standard_EXPORT void Cutting(const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void Merging(const bool                   passage,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool IsMergedClosed(const TopoDS_Edge& Edge1,
                                      const TopoDS_Edge& Edge2,
                                      const TopoDS_Face& fase) const;

  Standard_EXPORT bool FindCandidates(NCollection_Sequence<TopoDS_Shape>& seqSections,
                                      NCollection_IndexedMap<int>&        mapReference,
                                      NCollection_Sequence<int>&          seqCandidates,
                                      NCollection_Sequence<bool>&         seqOrientations);

  Standard_EXPORT void AnalysisNearestEdges(const NCollection_Sequence<TopoDS_Shape>& sequenceSec,
                                            NCollection_Sequence<int>&  seqIndCandidate,
                                            NCollection_Sequence<bool>& seqOrientations,
                                            const bool                  evalDist = true);

  Standard_EXPORT bool MergedNearestEdges(const TopoDS_Shape&                 edge,
                                          NCollection_Sequence<TopoDS_Shape>& SeqMergedEdge,
                                          NCollection_Sequence<bool>&         SeqMergedOri);

  Standard_EXPORT void EdgeProcessing(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void EdgeRegularity(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void CreateOutputInformations();

  Standard_EXPORT virtual bool IsUClosedSurface(const occ::handle<Geom_Surface>& surf,
                                                const TopoDS_Shape&              theEdge,
                                                const TopLoc_Location&           theloc) const;

  Standard_EXPORT virtual bool IsVClosedSurface(const occ::handle<Geom_Surface>& surf,
                                                const TopoDS_Shape&              theEdge,
                                                const TopLoc_Location&           theloc) const;

  Standard_EXPORT virtual void FaceAnalysis(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT virtual void FindFreeBoundaries();

  Standard_EXPORT virtual void VerticesAssembling(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT virtual void CreateSewedShape();

  Standard_EXPORT virtual void GetFreeWires(
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MapFreeEdges,
    NCollection_Sequence<TopoDS_Shape>&                            seqWires);

  Standard_EXPORT virtual void EvaluateAngulars(NCollection_Sequence<TopoDS_Shape>& sequenceSec,
                                                NCollection_Array1<bool>&           secForward,
                                                NCollection_Array1<double>&         tabAng,
                                                const int                           indRef) const;

  Standard_EXPORT virtual void EvaluateDistances(NCollection_Sequence<TopoDS_Shape>& sequenceSec,
                                                 NCollection_Array1<bool>&           secForward,
                                                 NCollection_Array1<double>&         tabAng,
                                                 NCollection_Array1<double>&         arrLen,
                                                 NCollection_Array1<double>&         tabMinDist,
                                                 const int                           indRef) const;

  Standard_EXPORT virtual occ::handle<Geom2d_Curve> SameRange(
    const occ::handle<Geom2d_Curve>& CurvePtr,
    const double                     FirstOnCurve,
    const double                     LastOnCurve,
    const double                     RequestedFirst,
    const double                     RequestedLast) const;

  Standard_EXPORT virtual void SameParameter(const TopoDS_Edge& edge) const;

  Standard_EXPORT virtual TopoDS_Edge SameParameterEdge(
    const TopoDS_Shape&                                     edge,
    const NCollection_Sequence<TopoDS_Shape>&               seqEdges,
    const NCollection_Sequence<bool>&                       seqForward,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& mapMerged,
    const occ::handle<BRepTools_ReShape>&                   locReShape);

  Standard_EXPORT virtual TopoDS_Edge SameParameterEdge(
    const TopoDS_Edge&                    edge1,
    const TopoDS_Edge&                    edge2,
    const NCollection_List<TopoDS_Shape>& listFaces1,
    const NCollection_List<TopoDS_Shape>& listFaces2,
    const bool                            secForward,
    int&                                  whichSec,
    const bool                            firstCall = true);

  Standard_EXPORT void ProjectPointsOnCurve(const NCollection_Array1<gp_Pnt>& arrPnt,
                                            const occ::handle<Geom_Curve>&    Crv,
                                            const double                      first,
                                            const double                      last,
                                            NCollection_Array1<double>&       arrDist,
                                            NCollection_Array1<double>&       arrPara,
                                            NCollection_Array1<gp_Pnt>&       arrProj,
                                            const bool                        isConsiderEnds) const;

  Standard_EXPORT virtual void CreateCuttingNodes(
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MapVert,
    const TopoDS_Shape&                                                  bound,
    const TopoDS_Shape&                                                  vfirst,
    const TopoDS_Shape&                                                  vlast,
    const NCollection_Array1<double>&                                    arrDist,
    const NCollection_Array1<double>&                                    arrPara,
    const NCollection_Array1<gp_Pnt>&                                    arrPnt,
    NCollection_Sequence<TopoDS_Shape>&                                  seqNode,
    NCollection_Sequence<double>&                                        seqPara);

  Standard_EXPORT virtual void CreateSections(const TopoDS_Shape&                       bound,
                                              const NCollection_Sequence<TopoDS_Shape>& seqNode,
                                              const NCollection_Sequence<double>&       seqPara,
                                              NCollection_List<TopoDS_Shape>&           listEdge);

  Standard_EXPORT virtual void SameParameterShape();

  double                                                                          myTolerance;
  bool                                                                            mySewing;
  bool                                                                            myAnalysis;
  bool                                                                            myCutting;
  bool                                                                            myNonmanifold;
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myOldShapes;
  TopoDS_Shape                                                                    mySewedShape;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>                   myDegenerated;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>                   myFreeEdges;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>                   myMultipleEdges;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                           myContigousEdges;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myContigSecBound;
  int                                                                      myNbShapes;
  int                                                                      myNbVertices;
  int                                                                      myNbEdges;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myBoundFaces;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                                  myBoundSections;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>        mySectionBound;
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myVertexNode;
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myVertexNodeFree;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myNodeSections;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                myCuttingNode;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myLittleFace;
  TopoDS_Shape                                                  myShape;
  occ::handle<BRepTools_ReShape>                                myReShape;

private:
  bool                                                   myFaceMode;
  bool                                                   myFloatingEdgesMode;
  bool                                                   mySameParameterMode;
  bool                                                   myLocalToleranceMode;
  double                                                 myMinTolerance;
  double                                                 myMaxTolerance;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMergedEdges;
};

inline void BRepBuilderAPI_Sewing::SetMaxTolerance(const double theMaxToler)
{
  myMaxTolerance = theMaxToler;
}

inline double BRepBuilderAPI_Sewing::MaxTolerance() const
{
  return myMaxTolerance;
}

inline double BRepBuilderAPI_Sewing::Tolerance() const
{
  return myTolerance;
}

inline void BRepBuilderAPI_Sewing::SetTolerance(const double theToler)
{
  myTolerance = theToler;
}

inline void BRepBuilderAPI_Sewing::SetMinTolerance(const double theMinToler)
{
  myMinTolerance = theMinToler;
}

inline double BRepBuilderAPI_Sewing::MinTolerance() const
{
  return myMinTolerance;
}

inline void BRepBuilderAPI_Sewing::SetFaceMode(const bool theFaceMode)
{
  myFaceMode = theFaceMode;
}

inline bool BRepBuilderAPI_Sewing::FaceMode() const
{
  return myFaceMode;
}

inline void BRepBuilderAPI_Sewing::SetFloatingEdgesMode(const bool theFloatingEdgesMode)
{
  myFloatingEdgesMode = theFloatingEdgesMode;
}

inline bool BRepBuilderAPI_Sewing::FloatingEdgesMode() const
{
  return myFloatingEdgesMode;
}

inline bool BRepBuilderAPI_Sewing::SameParameterMode() const
{
  return mySameParameterMode;
}

inline void BRepBuilderAPI_Sewing::SetSameParameterMode(const bool SameParameterMode)
{
  mySameParameterMode = SameParameterMode;
}

inline void BRepBuilderAPI_Sewing::SetLocalTolerancesMode(const bool theLocalTolerancesMode)
{
  myLocalToleranceMode = theLocalTolerancesMode;
}

inline bool BRepBuilderAPI_Sewing::LocalTolerancesMode() const
{
  return myLocalToleranceMode;
}

inline void BRepBuilderAPI_Sewing::SetNonManifoldMode(const bool theNonManifoldMode)
{
  myNonmanifold = theNonManifoldMode;
}

inline bool BRepBuilderAPI_Sewing::NonManifoldMode() const
{
  return myNonmanifold;
}
