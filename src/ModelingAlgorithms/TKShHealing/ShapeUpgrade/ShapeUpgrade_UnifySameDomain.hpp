#pragma once

#include <BRepTools_History.hpp>
#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Sequence.hpp>
#include <Geom_Plane.hpp>
#include <Precision.hpp>
class ShapeBuild_ReShape;

class ShapeUpgrade_UnifySameDomain : public Standard_Transient
{

public:
  typedef NCollection_DataMap<TopoDS_Shape, occ::handle<Geom_Plane>, TopTools_ShapeMapHasher>
    DataMapOfFacePlane;
  typedef NCollection_DataMap<TopoDS_Shape,
                              NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>,
                              TopTools_ShapeMapHasher>
    DataMapOfShapeMapOfShape;

  Standard_EXPORT ShapeUpgrade_UnifySameDomain();

  Standard_EXPORT ShapeUpgrade_UnifySameDomain(const TopoDS_Shape& aShape,
                                               const bool          UnifyEdges     = true,
                                               const bool          UnifyFaces     = true,
                                               const bool          ConcatBSplines = false);

  Standard_EXPORT void Initialize(const TopoDS_Shape& aShape,
                                  const bool          UnifyEdges     = true,
                                  const bool          UnifyFaces     = true,
                                  const bool          ConcatBSplines = false);

  Standard_EXPORT void AllowInternalEdges(const bool theValue);

  Standard_EXPORT void KeepShape(const TopoDS_Shape& theShape);

  Standard_EXPORT void KeepShapes(
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theShapes);

  Standard_EXPORT void SetSafeInputMode(bool theValue);

  void SetLinearTolerance(const double theValue) { myLinTol = theValue; }

  void SetAngularTolerance(const double theValue)
  {
    myAngTol = (theValue < Precision::Angular() ? Precision::Angular() : theValue);
  }

  Standard_EXPORT void Build();

  const TopoDS_Shape& Shape() const { return myShape; }

  const occ::handle<BRepTools_History>& History() const { return myHistory; }

  occ::handle<BRepTools_History>& History() { return myHistory; }

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_UnifySameDomain, Standard_Transient)

protected:
  struct SubSequenceOfEdges;

protected:
  Standard_EXPORT void UnifyFaces();

  Standard_EXPORT void UnifyEdges();

  void IntUnifyFaces(const TopoDS_Shape&                                        theInpShape,
                     const NCollection_IndexedDataMap<TopoDS_Shape,
                                                      NCollection_List<TopoDS_Shape>,
                                                      TopTools_ShapeMapHasher>& theGMapEdgeFaces,
                     const DataMapOfShapeMapOfShape&                            theGMapFaceShells,
                     const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theFreeBoundMap);

  bool MergeEdges(NCollection_Sequence<TopoDS_Shape>&                           SeqEdges,
                  const NCollection_IndexedDataMap<TopoDS_Shape,
                                                   NCollection_List<TopoDS_Shape>,
                                                   TopTools_ShapeMapHasher>&    theVFmap,
                  NCollection_Sequence<SubSequenceOfEdges>&                     SeqOfSubSeqOfEdges,
                  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& NonMergVrt);

  bool MergeSeq(NCollection_Sequence<TopoDS_Shape>&                           SeqEdges,
                const NCollection_IndexedDataMap<TopoDS_Shape,
                                                 NCollection_List<TopoDS_Shape>,
                                                 TopTools_ShapeMapHasher>&    theVFmap,
                const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& nonMergVert);

  bool MergeSubSeq(const NCollection_Sequence<TopoDS_Shape>&                  theChain,
                   const NCollection_IndexedDataMap<TopoDS_Shape,
                                                    NCollection_List<TopoDS_Shape>,
                                                    TopTools_ShapeMapHasher>& theVFmap,
                   TopoDS_Edge&                                               OutEdge);

  void UnionPCurves(const NCollection_Sequence<TopoDS_Shape>& theChain, TopoDS_Edge& theEdge);

  Standard_EXPORT void FillHistory();

private:
  static void generateSubSeq(
    const NCollection_Sequence<TopoDS_Shape>&                     anInpEdgeSeq,
    NCollection_Sequence<SubSequenceOfEdges>&                     SeqOfSubSeqOfEdges,
    bool                                                          IsClosed,
    double                                                        theAngTol,
    double                                                        theLinTol,
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& AvoidEdgeVrt,
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>&    theVFmap);

private:
  TopoDS_Shape                                           myInitShape;
  double                                                 myLinTol;
  double                                                 myAngTol;
  bool                                                   myUnifyFaces;
  bool                                                   myUnifyEdges;
  bool                                                   myConcatBSplines;
  bool                                                   myAllowInternal;
  bool                                                   mySafeInputMode;
  TopoDS_Shape                                           myShape;
  occ::handle<ShapeBuild_ReShape>                        myContext;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myKeepShapes;
  DataMapOfFacePlane                                     myFacePlaneMap;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                           myEFmap;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myFaceNewFace;

  occ::handle<BRepTools_History> myHistory;
};
