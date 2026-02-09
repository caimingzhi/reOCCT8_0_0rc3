#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <NCollection_List.hpp>
#include <BOPTools_CoupleOfShape.hpp>
#include <BOPTools_ConnexityBlock.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <TopAbs_State.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>
#include <Precision.hpp>
class TopoDS_Vertex;
class gp_Pnt;
class IntTools_Curve;
class TopoDS_Edge;
class TopoDS_Face;
class TopoDS_Shape;
class IntTools_Context;
class TopoDS_Solid;
class IntTools_Range;
class TopoDS_Shell;
class Message_Report;

class BOPTools_AlgoTools
{
public:
  DEFINE_STANDARD_ALLOC

public:
  static double DTolerance() { return 1.e-12; }

public:
  Standard_EXPORT static int ComputeVV(const TopoDS_Vertex& theV,
                                       const gp_Pnt&        theP,
                                       const double         theTolP);

  Standard_EXPORT static int ComputeVV(const TopoDS_Vertex& theV1,
                                       const TopoDS_Vertex& theV2,
                                       const double         theFuzz = Precision::Confusion());

public:
  Standard_EXPORT static void MakeVertex(const NCollection_List<TopoDS_Shape>& theLV,
                                         TopoDS_Vertex&                        theV);

  Standard_EXPORT static void MakeNewVertex(const gp_Pnt&  aP1,
                                            const double   aTol,
                                            TopoDS_Vertex& aNewVertex);

  Standard_EXPORT static void MakeNewVertex(const TopoDS_Vertex& aV1,
                                            const TopoDS_Vertex& aV2,
                                            TopoDS_Vertex&       aNewVertex);

  Standard_EXPORT static void MakeNewVertex(const TopoDS_Edge& aE1,
                                            const double       aP1,
                                            const TopoDS_Edge& aE2,
                                            const double       aP2,
                                            TopoDS_Vertex&     aNewVertex);

  Standard_EXPORT static void MakeNewVertex(const TopoDS_Edge& aE1,
                                            const double       aP1,
                                            const TopoDS_Face& aF2,
                                            TopoDS_Vertex&     aNewVertex);

public:
  Standard_EXPORT static void UpdateVertex(const IntTools_Curve& aIC,
                                           const double          aT,
                                           const TopoDS_Vertex&  aV);

  Standard_EXPORT static void UpdateVertex(const TopoDS_Edge&   aE,
                                           const double         aT,
                                           const TopoDS_Vertex& aV);

  Standard_EXPORT static void UpdateVertex(const TopoDS_Vertex& aVF, const TopoDS_Vertex& aVN);

public:
  Standard_EXPORT static void MakeEdge(const IntTools_Curve& theCurve,
                                       const TopoDS_Vertex&  theV1,
                                       const double          theT1,
                                       const TopoDS_Vertex&  theV2,
                                       const double          theT2,
                                       const double          theTolR3D,
                                       TopoDS_Edge&          theE);

  Standard_EXPORT static TopoDS_Edge CopyEdge(const TopoDS_Edge& theEdge);

  Standard_EXPORT static void MakeSplitEdge(const TopoDS_Edge&   aE1,
                                            const TopoDS_Vertex& aV1,
                                            const double         aP1,
                                            const TopoDS_Vertex& aV2,
                                            const double         aP2,
                                            TopoDS_Edge&         aNewEdge);

  Standard_EXPORT static void MakeSectEdge(const IntTools_Curve& aIC,
                                           const TopoDS_Vertex&  aV1,
                                           const double          aP1,
                                           const TopoDS_Vertex&  aV2,
                                           const double          aP2,
                                           TopoDS_Edge&          aNewEdge);

public:
  Standard_EXPORT static TopAbs_State ComputeState(const gp_Pnt&                        thePoint,
                                                   const TopoDS_Solid&                  theSolid,
                                                   const double                         theTol,
                                                   const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT static TopAbs_State ComputeState(const TopoDS_Vertex&                 theVertex,
                                                   const TopoDS_Solid&                  theSolid,
                                                   const double                         theTol,
                                                   const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT static TopAbs_State ComputeState(const TopoDS_Edge&                   theEdge,
                                                   const TopoDS_Solid&                  theSolid,
                                                   const double                         theTol,
                                                   const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT static TopAbs_State ComputeState(
    const TopoDS_Face&                                                   theFace,
    const TopoDS_Solid&                                                  theSolid,
    const double                                                         theTol,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theBounds,
    const occ::handle<IntTools_Context>&                                 theContext);

  Standard_EXPORT static TopAbs_State ComputeStateByOnePoint(
    const TopoDS_Shape&                  theShape,
    const TopoDS_Solid&                  theSolid,
    const double                         theTol,
    const occ::handle<IntTools_Context>& theContext);

public:
  Standard_EXPORT static bool GetFaceOff(const TopoDS_Edge&                        theEdge,
                                         const TopoDS_Face&                        theFace,
                                         NCollection_List<BOPTools_CoupleOfShape>& theLCEF,
                                         TopoDS_Face&                              theFaceOff,
                                         const occ::handle<IntTools_Context>&      theContext);

  Standard_EXPORT static int IsInternalFace(const TopoDS_Face&                   theFace,
                                            const TopoDS_Edge&                   theEdge,
                                            const TopoDS_Face&                   theFace1,
                                            const TopoDS_Face&                   theFace2,
                                            const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT static int IsInternalFace(const TopoDS_Face&                   theFace,
                                            const TopoDS_Edge&                   theEdge,
                                            NCollection_List<TopoDS_Shape>&      theLF,
                                            const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT static bool IsInternalFace(
    const TopoDS_Face&                                   theFace,
    const TopoDS_Solid&                                  theSolid,
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>& theMEF,
    const double                                         theTol,
    const occ::handle<IntTools_Context>&                 theContext);

public:
  Standard_EXPORT static void MakePCurve(
    const TopoDS_Edge&                   theE,
    const TopoDS_Face&                   theF1,
    const TopoDS_Face&                   theF2,
    const IntTools_Curve&                theCurve,
    const bool                           thePC1,
    const bool                           thePC2,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

public:
  Standard_EXPORT static bool IsHole(const TopoDS_Shape& theW, const TopoDS_Shape& theF);

public:
  Standard_EXPORT static bool IsSplitToReverse(const TopoDS_Shape&                  theSplit,
                                               const TopoDS_Shape&                  theShape,
                                               const occ::handle<IntTools_Context>& theContext,
                                               int* theError = nullptr);

  Standard_EXPORT static bool IsSplitToReverseWithWarn(
    const TopoDS_Shape&                  theSplit,
    const TopoDS_Shape&                  theShape,
    const occ::handle<IntTools_Context>& theContext,
    const occ::handle<Message_Report>&   theReport = nullptr);

  Standard_EXPORT static bool IsSplitToReverse(const TopoDS_Face&                   theSplit,
                                               const TopoDS_Face&                   theShape,
                                               const occ::handle<IntTools_Context>& theContext,
                                               int* theError = nullptr);

  Standard_EXPORT static bool IsSplitToReverse(const TopoDS_Edge&                   theSplit,
                                               const TopoDS_Edge&                   theShape,
                                               const occ::handle<IntTools_Context>& theContext,
                                               int* theError = nullptr);

  Standard_EXPORT static int Sense(const TopoDS_Face&                   theF1,
                                   const TopoDS_Face&                   theF2,
                                   const occ::handle<IntTools_Context>& theContext);

public:
  Standard_EXPORT static void MakeConnexityBlock(
    NCollection_List<TopoDS_Shape>&                                theLS,
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapAvoid,
    NCollection_List<TopoDS_Shape>&                                theLSCB,
    const occ::handle<NCollection_BaseAllocator>&                  theAllocator);

  Standard_EXPORT static void MakeConnexityBlocks(const TopoDS_Shape&             theS,
                                                  const TopAbs_ShapeEnum          theConnectionType,
                                                  const TopAbs_ShapeEnum          theElementType,
                                                  NCollection_List<TopoDS_Shape>& theLCB);

  Standard_EXPORT static void MakeConnexityBlocks(
    const TopoDS_Shape&                                  theS,
    const TopAbs_ShapeEnum                               theConnectionType,
    const TopAbs_ShapeEnum                               theElementType,
    NCollection_List<NCollection_List<TopoDS_Shape>>&    theLCB,
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>& theConnectionMap);

  Standard_EXPORT static void MakeConnexityBlocks(
    const NCollection_List<TopoDS_Shape>&      theLS,
    const TopAbs_ShapeEnum                     theConnectionType,
    const TopAbs_ShapeEnum                     theElementType,
    NCollection_List<BOPTools_ConnexityBlock>& theLCB);

public:
  Standard_EXPORT static void OrientEdgesOnWire(TopoDS_Shape& theWire);

  Standard_EXPORT static void OrientFacesOnShell(TopoDS_Shape& theShell);

public:
  Standard_EXPORT static void CorrectTolerances(
    const TopoDS_Shape&                                                  theS,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapToAvoid,
    const double                                                         theTolMax      = 0.0001,
    const bool                                                           theRunParallel = false);

  Standard_EXPORT static void CorrectCurveOnSurface(
    const TopoDS_Shape&                                                  theS,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapToAvoid,
    const double                                                         theTolMax      = 0.0001,
    const bool                                                           theRunParallel = false);

  Standard_EXPORT static void CorrectPointOnCurve(
    const TopoDS_Shape&                                                  theS,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapToAvoid,
    const double                                                         theTolMax      = 0.0001,
    const bool                                                           theRunParallel = false);

  Standard_EXPORT static void CorrectShapeTolerances(
    const TopoDS_Shape&                                                  theS,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapToAvoid,
    const bool                                                           theRunParallel = false);

public:
  Standard_EXPORT static bool AreFacesSameDomain(const TopoDS_Face&                   theF1,
                                                 const TopoDS_Face&                   theF2,
                                                 const occ::handle<IntTools_Context>& theContext,
                                                 const double theFuzz = Precision::Confusion());

public:
  Standard_EXPORT static bool GetEdgeOff(const TopoDS_Edge& theEdge,
                                         const TopoDS_Face& theFace,
                                         TopoDS_Edge&       theEdgeOff);

  Standard_EXPORT static bool GetEdgeOnFace(const TopoDS_Edge& theEdge,
                                            const TopoDS_Face& theFace,
                                            TopoDS_Edge&       theEdgeOnF);

public:
  Standard_EXPORT static void CorrectRange(const TopoDS_Edge&    aE1,
                                           const TopoDS_Edge&    aE2,
                                           const IntTools_Range& aSR,
                                           IntTools_Range&       aNewSR);

  Standard_EXPORT static void CorrectRange(const TopoDS_Edge&    aE,
                                           const TopoDS_Face&    aF,
                                           const IntTools_Range& aSR,
                                           IntTools_Range&       aNewSR);

public:
  Standard_EXPORT static bool IsMicroEdge(const TopoDS_Edge&                   theEdge,
                                          const occ::handle<IntTools_Context>& theContext,
                                          const bool theCheckSplittable = true);

public:
  Standard_EXPORT static bool IsInvertedSolid(const TopoDS_Solid& theSolid);

public:
  Standard_EXPORT static bool ComputeTolerance(const TopoDS_Face& theFace,
                                               const TopoDS_Edge& theEdge,
                                               double&            theMaxDist,
                                               double&            theMaxPar);

public:
  Standard_EXPORT static void MakeContainer(const TopAbs_ShapeEnum theType, TopoDS_Shape& theShape);

  Standard_EXPORT static void PointOnEdge(const TopoDS_Edge& aEdge, const double aPrm, gp_Pnt& aP);

  Standard_EXPORT static bool IsBlockInOnFace(const IntTools_Range&                aShR,
                                              const TopoDS_Face&                   aF,
                                              const TopoDS_Edge&                   aE,
                                              const occ::handle<IntTools_Context>& aContext);

  Standard_EXPORT static void Dimensions(const TopoDS_Shape& theS, int& theDMin, int& theDMax);

  Standard_EXPORT static int Dimension(const TopoDS_Shape& theS);

  Standard_EXPORT static void TreatCompound(
    const TopoDS_Shape&                                     theS,
    NCollection_List<TopoDS_Shape>&                         theList,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>* theMap = nullptr);

  Standard_EXPORT static bool IsOpenShell(const TopoDS_Shell& theShell);
};
