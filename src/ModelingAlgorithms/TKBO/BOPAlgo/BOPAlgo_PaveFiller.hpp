#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_Algo.hpp>
#include <BOPAlgo_GlueEnum.hpp>
#include <BOPAlgo_SectionAttribute.hpp>
#include <NCollection_DataMap.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <BOPDS_CoupleOfPaveBlocks.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>
#include <BOPDS_Pair.hpp>
#include <BOPDS_PDS.hpp>

class BOPDS_Iterator;
typedef BOPDS_Iterator* BOPDS_PIterator;

#include <NCollection_Vector.hpp>
#include <BOPDS_Curve.hpp>
#include <BOPTools_BoxTree.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <IntTools_ShrunkRange.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_Real.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_Shape.hpp>
class IntTools_Context;
class BOPDS_PaveBlock;
class gp_Pnt;
class BOPDS_Curve;
class TopoDS_Vertex;
class TopoDS_Edge;
class TopoDS_Face;

class BOPAlgo_PaveFiller : public BOPAlgo_Algo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_PaveFiller();

  Standard_EXPORT ~BOPAlgo_PaveFiller() override;

  Standard_EXPORT BOPAlgo_PaveFiller(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT const BOPDS_DS& DS();

  Standard_EXPORT BOPDS_PDS PDS();

  Standard_EXPORT const BOPDS_PIterator& Iterator();

  void SetArguments(const NCollection_List<TopoDS_Shape>& theLS) { myArguments = theLS; }

  void AddArgument(const TopoDS_Shape& theShape) { myArguments.Append(theShape); }

  const NCollection_List<TopoDS_Shape>& Arguments() const { return myArguments; }

  Standard_EXPORT const occ::handle<IntTools_Context>& Context();

  Standard_EXPORT void SetSectionAttribute(const BOPAlgo_SectionAttribute& theSecAttr);

  Standard_EXPORT void SetNonDestructive(const bool theFlag);

  Standard_EXPORT bool NonDestructive() const;

  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT void SetGlue(const BOPAlgo_GlueEnum theGlue);

  Standard_EXPORT BOPAlgo_GlueEnum Glue() const;

  void SetAvoidBuildPCurve(const bool theValue) { myAvoidBuildPCurve = theValue; }

  bool IsAvoidBuildPCurve() const { return myAvoidBuildPCurve; }

protected:
  typedef NCollection_DataMap<occ::handle<BOPDS_PaveBlock>, Bnd_Box>
    BOPAlgo_DataMapOfPaveBlockBndBox;

  typedef NCollection_DataMap<occ::handle<BOPDS_PaveBlock>, NCollection_List<int>>
    BOPAlgo_DataMapOfPaveBlockListOfInteger;

  typedef NCollection_DataMap<int, NCollection_Map<occ::handle<BOPDS_PaveBlock>>>
    BOPAlgo_DataMapOfIntegerMapOfPaveBlock;

  Standard_EXPORT void SetNonDestructive();

  Standard_EXPORT void SetIsPrimary(const bool theFlag);

  Standard_EXPORT bool IsPrimary() const;

  Standard_EXPORT virtual void PerformInternal(const Message_ProgressRange& theRange);

  Standard_EXPORT void Clear() override;

  Standard_EXPORT virtual void Init(const Message_ProgressRange& theRange);

  Standard_EXPORT void Prepare(const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void PerformVV(const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void PerformVE(const Message_ProgressRange& theRange);

  Standard_EXPORT void IntersectVE(
    const NCollection_IndexedDataMap<occ::handle<BOPDS_PaveBlock>, NCollection_List<int>>&
                                 theVEPairs,
    const Message_ProgressRange& theRange,
    const bool                   bAddInterfs = true);

  Standard_EXPORT void SplitPaveBlocks(const NCollection_Map<int>& theMEdges,
                                       const bool                  theAddInterfs);

  Standard_EXPORT virtual void PerformVF(const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void PerformEE(const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void PerformEF(const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void PerformFF(const Message_ProgressRange& theRange);

  Standard_EXPORT void TreatVerticesEE();

  Standard_EXPORT void MakeSDVerticesFF(
    const NCollection_DataMap<int, NCollection_List<int>>& aDMVLV,
    NCollection_DataMap<int, int>&                         theDMNewSD);

  Standard_EXPORT void MakeSplitEdges(const Message_ProgressRange& theRange);

  Standard_EXPORT void MakeBlocks(const Message_ProgressRange& theRange);

  Standard_EXPORT void MakePCurves(const Message_ProgressRange& theRange);

  Standard_EXPORT int MakeSDVertices(const NCollection_List<int>& theVertIndices,
                                     const bool                   theAddInterfs = true);

  Standard_EXPORT void ProcessDE(const Message_ProgressRange& theRange);

  Standard_EXPORT void FillShrunkData(occ::handle<BOPDS_PaveBlock>& thePB);

  Standard_EXPORT void FillShrunkData(const TopAbs_ShapeEnum theType1,
                                      const TopAbs_ShapeEnum theType2);

  Standard_EXPORT void AnalyzeShrunkData(const occ::handle<BOPDS_PaveBlock>& thePB,
                                         const IntTools_ShrunkRange&         theSR);

  Standard_EXPORT void PerformNewVertices(
    NCollection_IndexedDataMap<TopoDS_Shape, BOPDS_CoupleOfPaveBlocks, TopTools_ShapeMapHasher>&
                                                  theMVCPB,
    const occ::handle<NCollection_BaseAllocator>& theAllocator,
    const Message_ProgressRange&                  theRange,
    const bool                                    theIsEEIntersection = true);

  Standard_EXPORT bool CheckFacePaves(const TopoDS_Vertex&        theVnew,
                                      const NCollection_Map<int>& theMIF);

  Standard_EXPORT static bool CheckFacePaves(const int                   theN,
                                             const NCollection_Map<int>& theMIFOn,
                                             const NCollection_Map<int>& theMIFIn);

  Standard_EXPORT bool IsExistingVertex(const gp_Pnt&               theP,
                                        const double                theTol,
                                        const NCollection_Map<int>& theMVOn) const;

  Standard_EXPORT void PutPavesOnCurve(const NCollection_Map<int>&                      theMVOnIn,
                                       const NCollection_Map<int>&                      theMVCommon,
                                       BOPDS_Curve&                                     theNC,
                                       const NCollection_Map<int>&                      theMI,
                                       const NCollection_Map<int>&                      theMVEF,
                                       NCollection_DataMap<int, double>&                theMVTol,
                                       NCollection_DataMap<int, NCollection_List<int>>& theDMVLV);

  Standard_EXPORT void FilterPavesOnCurves(const NCollection_Vector<BOPDS_Curve>& theVNC,
                                           NCollection_DataMap<int, double>&      theMVTol);

  Standard_EXPORT bool ExtendedTolerance(const int                   nV,
                                         const NCollection_Map<int>& aMI,
                                         double&                     aTolVExt,
                                         const int                   aType = 0);

  Standard_EXPORT void PutBoundPaveOnCurve(const TopoDS_Face&     theF1,
                                           const TopoDS_Face&     theF2,
                                           BOPDS_Curve&           theNC,
                                           NCollection_List<int>& theLBV);

  Standard_EXPORT bool IsExistingPaveBlock(
    const occ::handle<BOPDS_PaveBlock>&                         thePB,
    const BOPDS_Curve&                                          theNC,
    const double                                                theTolR3D,
    const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& theMPB,
    BOPTools_BoxTree&                                           thePBTree,
    const NCollection_Map<occ::handle<BOPDS_PaveBlock>>&        theMPBCommon,
    occ::handle<BOPDS_PaveBlock>&                               thePBOut,
    double&                                                     theTolNew);

  Standard_EXPORT bool IsExistingPaveBlock(const occ::handle<BOPDS_PaveBlock>& thePB,
                                           const BOPDS_Curve&                  theNC,
                                           const NCollection_List<int>&        theLSE,
                                           int&                                theNEOut,
                                           double&                             theTolNew);

  Standard_EXPORT void PostTreatFF(
    NCollection_IndexedDataMap<TopoDS_Shape, BOPDS_CoupleOfPaveBlocks, TopTools_ShapeMapHasher>&
                                                                         theMSCPB,
    NCollection_DataMap<occ::handle<BOPDS_PaveBlock>,
                        NCollection_List<occ::handle<BOPDS_PaveBlock>>>& theDMExEdges,
    NCollection_DataMap<int, int>&                                       theDMNewSD,
    const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>&          theMicroPB,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theVertsOnRejectedPB,
    const occ::handle<NCollection_BaseAllocator>&                        theAllocator,
    const Message_ProgressRange&                                         theRange);

  Standard_EXPORT void FindPaveBlocks(const int                                       theV,
                                      const int                                       theF,
                                      NCollection_List<occ::handle<BOPDS_PaveBlock>>& theLPB);

  Standard_EXPORT void FillPaves(const int                                             theV,
                                 const int                                             theE,
                                 const int                                             theF,
                                 const NCollection_List<occ::handle<BOPDS_PaveBlock>>& theLPB,
                                 const occ::handle<BOPDS_PaveBlock>&                   thePB);

  Standard_EXPORT void MakeSplitEdge(const int theV, const int theF);

  Standard_EXPORT void GetEFPnts(const int                          nF1,
                                 const int                          nF2,
                                 NCollection_List<IntSurf_PntOn2S>& aListOfPnts);

  Standard_EXPORT void PutEFPavesOnCurve(const NCollection_Vector<BOPDS_Curve>&           theVC,
                                         const int                                        theIndex,
                                         const NCollection_Map<int>&                      theMI,
                                         const NCollection_Map<int>&                      theMVEF,
                                         NCollection_DataMap<int, double>&                theMVTol,
                                         NCollection_DataMap<int, NCollection_List<int>>& aDMVLV);

  Standard_EXPORT void PutStickPavesOnCurve(
    const TopoDS_Face&                               aF1,
    const TopoDS_Face&                               aF2,
    const NCollection_Map<int>&                      theMI,
    const NCollection_Vector<BOPDS_Curve>&           theVC,
    const int                                        theIndex,
    const NCollection_Map<int>&                      theMVStick,
    NCollection_DataMap<int, double>&                theMVTol,
    NCollection_DataMap<int, NCollection_List<int>>& aDMVLV);

  Standard_EXPORT void GetStickVertices(const int             nF1,
                                        const int             nF2,
                                        NCollection_Map<int>& theMVStick,
                                        NCollection_Map<int>& theMVEF,
                                        NCollection_Map<int>& theMI);

  Standard_EXPORT void GetFullShapeMap(const int nF, NCollection_Map<int>& theMI);

  Standard_EXPORT void RemoveUsedVertices(const NCollection_Vector<BOPDS_Curve>& theVC,
                                          NCollection_Map<int>&                  theMV);

  Standard_EXPORT void PutPaveOnCurve(const int                                        nV,
                                      const double                                     theTolR3D,
                                      const BOPDS_Curve&                               theNC,
                                      const NCollection_Map<int>&                      theMI,
                                      NCollection_DataMap<int, double>&                theMVTol,
                                      NCollection_DataMap<int, NCollection_List<int>>& aDMVLV,
                                      const int                                        aType = 0);

  Standard_EXPORT void ProcessExistingPaveBlocks(
    const int                                                   theInt,
    const int                                                   theCur,
    const int                                                   nF1,
    const int                                                   nF2,
    const TopoDS_Edge&                                          theES,
    const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& theMPBOnIn,
    BOPTools_BoxTree&                                           thePBTree,
    NCollection_IndexedDataMap<TopoDS_Shape, BOPDS_CoupleOfPaveBlocks, TopTools_ShapeMapHasher>&
                                                                     theMSCPB,
    NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>& theMVI,
    NCollection_List<occ::handle<BOPDS_PaveBlock>>&                  theLPBC,
    BOPAlgo_DataMapOfPaveBlockListOfInteger&                         thePBFacesMap,
    NCollection_Map<occ::handle<BOPDS_PaveBlock>>&                   theMPB);

  Standard_EXPORT void ProcessExistingPaveBlocks(
    const int                                                   theInt,
    const int                                                   nF1,
    const int                                                   nF2,
    const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& theMPBOnIn,
    BOPTools_BoxTree&                                           thePBTree,
    const NCollection_DataMap<int, NCollection_List<int>>&      theDMBV,
    NCollection_IndexedDataMap<TopoDS_Shape, BOPDS_CoupleOfPaveBlocks, TopTools_ShapeMapHasher>&
                                                                     theMSCPB,
    NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>& theMVI,
    BOPAlgo_DataMapOfPaveBlockListOfInteger&                         thePBFacesMap,
    NCollection_Map<occ::handle<BOPDS_PaveBlock>>&                   theMPB);

  Standard_EXPORT void UpdateExistingPaveBlocks(
    const occ::handle<BOPDS_PaveBlock>&             thePB,
    NCollection_List<occ::handle<BOPDS_PaveBlock>>& theLPB,
    const BOPAlgo_DataMapOfPaveBlockListOfInteger&  thePBFacesMap);

  Standard_EXPORT void TreatNewVertices(
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     BOPDS_CoupleOfPaveBlocks,
                                     TopTools_ShapeMapHasher>& theMVCPB,
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>&       theImages);

  Standard_EXPORT void PutClosingPaveOnCurve(BOPDS_Curve& aNC);

  Standard_EXPORT void PreparePostTreatFF(
    const int                           aInt,
    const int                           aCur,
    const occ::handle<BOPDS_PaveBlock>& aPB,
    NCollection_IndexedDataMap<TopoDS_Shape, BOPDS_CoupleOfPaveBlocks, TopTools_ShapeMapHasher>&
                                                                     aMSCPB,
    NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>& aMVI,
    NCollection_List<occ::handle<BOPDS_PaveBlock>>&                  aLPB);

  Standard_EXPORT void UpdateFaceInfo(
    NCollection_DataMap<occ::handle<BOPDS_PaveBlock>,
                        NCollection_List<occ::handle<BOPDS_PaveBlock>>>& theDME,
    const NCollection_DataMap<int, int>&                                 theDMV,
    const BOPAlgo_DataMapOfPaveBlockListOfInteger&                       thePBFacesMap);

  Standard_EXPORT bool ForceInterfVE(const int                     nV,
                                     occ::handle<BOPDS_PaveBlock>& aPB,
                                     NCollection_Map<int>&         theMEdges);

  Standard_EXPORT bool ForceInterfVF(const int nV, const int nF);

  Standard_EXPORT bool CheckPlanes(const int nF1, const int nF2) const;

  Standard_EXPORT int SplitEdge(const int    nE,
                                const int    nV1,
                                const double aT1,
                                const int    nV2,
                                const double aT2);

  Standard_EXPORT void UpdatePaveBlocks(const NCollection_DataMap<int, int>& aDMNewSD);

  Standard_EXPORT int UpdateVertex(const int nV, const double aTolNew);

  Standard_EXPORT void UpdatePaveBlocksWithSDVertices();

  Standard_EXPORT void UpdateCommonBlocksWithSDVertices();

  Standard_EXPORT void UpdateBlocksWithSharedVertices();

  Standard_EXPORT void UpdateInterfsWithSDVertices();

  Standard_EXPORT bool EstimatePaveOnCurve(const int          nV,
                                           const BOPDS_Curve& theNC,
                                           const double       theTolR3D);

  Standard_EXPORT void UpdateEdgeTolerance(const int nE, const double aTolNew);

  Standard_EXPORT void RemovePaveBlocks(const NCollection_Map<int>& theEdges);

  Standard_EXPORT void CorrectToleranceOfSE();

  Standard_EXPORT void ReduceIntersectionRange(const int theV1,
                                               const int theV2,
                                               const int theE,
                                               const int theF,
                                               double&   theTS1,
                                               double&   theTS2);

  Standard_EXPORT bool GetPBBox(const TopoDS_Edge&                  theE,
                                const occ::handle<BOPDS_PaveBlock>& thePB,
                                BOPAlgo_DataMapOfPaveBlockBndBox&   thePBBox,
                                double&                             theFirst,
                                double&                             theLast,
                                double&                             theSFirst,
                                double&                             theSLast,
                                Bnd_Box&                            theBox);

  Standard_EXPORT void PutSEInOtherFaces(const Message_ProgressRange& theRange);

  Standard_EXPORT void CheckSelfInterference();

  Standard_EXPORT void AddIntersectionFailedWarning(const TopoDS_Shape& theS1,
                                                    const TopoDS_Shape& theS2);

  Standard_EXPORT void RepeatIntersection(const Message_ProgressRange& theRange);

  Standard_EXPORT void UpdateVerticesOfCB();

  Standard_EXPORT void ForceInterfEE(const Message_ProgressRange& theRange);

  Standard_EXPORT void ForceInterfEF(const Message_ProgressRange& theRange);

  Standard_EXPORT void ForceInterfEF(
    const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& theMPB,
    const Message_ProgressRange&                                theRange,
    const bool                                                  theAddInterf);

  Standard_EXPORT void RemoveMicroSectionEdges(
    NCollection_IndexedDataMap<TopoDS_Shape, BOPDS_CoupleOfPaveBlocks, TopTools_ShapeMapHasher>&
                                                          theMSCPB,
    NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& theMicroPB);

  Standard_EXPORT void RemoveMicroEdges();

  struct EdgeRangeDistance
  {
    double First;
    double Last;
    double Distance;

    EdgeRangeDistance(const double theFirst    = 0.0,
                      const double theLast     = 0.0,
                      const double theDistance = RealLast())
        : First(theFirst),
          Last(theLast),
          Distance(theDistance)
    {
    }
  };

protected:
  Standard_EXPORT void fillPIConstants(const double     theWhole,
                                       BOPAlgo_PISteps& theSteps) const override;

  Standard_EXPORT void fillPISteps(BOPAlgo_PISteps& theSteps) const override;

protected:
  NCollection_List<TopoDS_Shape> myArguments;
  BOPDS_PDS                      myDS;
  BOPDS_PIterator                myIterator;
  occ::handle<IntTools_Context>  myContext;
  BOPAlgo_SectionAttribute       mySectionAttribute;
  bool                           myNonDestructive;
  bool                           myIsPrimary;
  bool                           myAvoidBuildPCurve;
  BOPAlgo_GlueEnum               myGlue;

  BOPAlgo_DataMapOfIntegerMapOfPaveBlock myFPBDone;
  NCollection_Map<int>                   myIncreasedSS;
  NCollection_Map<int>                   myVertsToAvoidExtension;

  NCollection_DataMap<BOPDS_Pair, NCollection_List<EdgeRangeDistance>> myDistances;
};
