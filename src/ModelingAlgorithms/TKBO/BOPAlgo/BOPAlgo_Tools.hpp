#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <Standard_Handle.hpp>
#include <BOPDS_PDS.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Bnd_Box.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>
#include <Message_ProgressRange.hpp>

class BOPDS_PaveBlock;
class BOPDS_CommonBlock;
class IntTools_Context;
class TopoDS_Shape;

class BOPAlgo_Tools
{
public:
  template <class TheMap, class TheList>
  static void MakeBlocks(const TheMap&                                 theMILI,
                         TheList&                                      theMBlocks,
                         const occ::handle<NCollection_BaseAllocator>& theAllocator)
  {
    NCollection_Map<typename TheMap::key_type, typename TheMap::hasher> aMFence;
    int                                                                 i, aNb = theMILI.Extent();
    for (i = 1; i <= aNb; ++i)
    {
      const typename TheMap::key_type& n = theMILI.FindKey(i);
      if (!aMFence.Add(n))
        continue;

      typename TheList::value_type& aChain =
        theMBlocks.Append(typename TheList::value_type(theAllocator));
      aChain.Append(n);

      typename TheList::value_type::Iterator aItLChain(aChain);
      for (; aItLChain.More(); aItLChain.Next())
      {
        const typename TheMap::key_type&    n1  = aItLChain.Value();
        const typename TheList::value_type& aLI = theMILI.FindFromKey(n1);

        typename TheList::value_type::Iterator aItLI(aLI);
        for (; aItLI.More(); aItLI.Next())
        {
          const typename TheMap::key_type& n2 = aItLI.Value();
          if (aMFence.Add(n2))
          {
            aChain.Append(n2);
          }
        }
      }
    }
  }

  template <class TheType, class TheMap>
  static void FillMap(const TheType&                                n1,
                      const TheType&                                n2,
                      TheMap&                                       theMILI,
                      const occ::handle<NCollection_BaseAllocator>& theAllocator)
  {
    typename TheMap::value_type* pList1 = theMILI.ChangeSeek(n1);
    if (!pList1)
    {
      pList1 = &theMILI(theMILI.Add(n1, NCollection_List<TheType>(theAllocator)));
    }
    pList1->Append(n2);

    typename TheMap::value_type* pList2 = theMILI.ChangeSeek(n2);
    if (!pList2)
    {
      pList2 = &theMILI(theMILI.Add(n2, typename TheMap::value_type(theAllocator)));
    }
    pList2->Append(n1);
  }

  Standard_EXPORT static void FillMap(
    const occ::handle<BOPDS_PaveBlock>&                                              thePB1,
    const int                                                                        theF,
    NCollection_IndexedDataMap<occ::handle<BOPDS_PaveBlock>, NCollection_List<int>>& theMILI,
    const occ::handle<NCollection_BaseAllocator>&                                    theAllocator);

  Standard_EXPORT static void PerformCommonBlocks(
    NCollection_IndexedDataMap<occ::handle<BOPDS_PaveBlock>,
                               NCollection_List<occ::handle<BOPDS_PaveBlock>>>& theMBlocks,
    const occ::handle<NCollection_BaseAllocator>&                               theAllocator,
    BOPDS_PDS&                                                                  theDS,
    const occ::handle<IntTools_Context>& theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static void PerformCommonBlocks(
    const NCollection_IndexedDataMap<occ::handle<BOPDS_PaveBlock>, NCollection_List<int>>&
                                                  theMBlocks,
    const occ::handle<NCollection_BaseAllocator>& theAllocator,
    BOPDS_PDS&                                    pDS,
    const occ::handle<IntTools_Context>&          theContext = occ::handle<IntTools_Context>());

  Standard_EXPORT static double ComputeToleranceOfCB(
    const occ::handle<BOPDS_CommonBlock>& theCB,
    const BOPDS_PDS                       theDS,
    const occ::handle<IntTools_Context>&  theContext);

  Standard_EXPORT static int EdgesToWires(const TopoDS_Shape& theEdges,
                                          TopoDS_Shape&       theWires,
                                          const bool          theShared = false,
                                          const double        theAngTol = 1.e-8);

  Standard_EXPORT static bool WiresToFaces(const TopoDS_Shape& theWires,
                                           TopoDS_Shape&       theFaces,
                                           const double        theAngTol = 1.e-8);

  Standard_EXPORT static void IntersectVertices(
    const NCollection_IndexedDataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher>& theVertices,
    const double                                                                     theFuzzyValue,
    NCollection_List<NCollection_List<TopoDS_Shape>>&                                theChains);

  Standard_EXPORT static void ClassifyFaces(
    const NCollection_List<TopoDS_Shape>&                                      theFaces,
    const NCollection_List<TopoDS_Shape>&                                      theSolids,
    const bool                                                                 theRunParallel,
    occ::handle<IntTools_Context>&                                             theContext,
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>&                       theInParts,
    const NCollection_DataMap<TopoDS_Shape, Bnd_Box, TopTools_ShapeMapHasher>& theShapeBoxMap =
      NCollection_DataMap<TopoDS_Shape, Bnd_Box, TopTools_ShapeMapHasher>(),
    const NCollection_DataMap<TopoDS_Shape,
                              NCollection_List<TopoDS_Shape>,
                              TopTools_ShapeMapHasher>& theSolidsIF =
      NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>(),
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT static void FillInternals(
    const NCollection_List<TopoDS_Shape>&               theSolids,
    const NCollection_List<TopoDS_Shape>&               theParts,
    const NCollection_DataMap<TopoDS_Shape,
                              NCollection_List<TopoDS_Shape>,
                              TopTools_ShapeMapHasher>& theImages,
    const occ::handle<IntTools_Context>&                theContext);

  Standard_EXPORT static bool TrsfToPoint(const Bnd_Box& theBox1,
                                          const Bnd_Box& theBox2,
                                          gp_Trsf&       theTrsf,
                                          const gp_Pnt&  thePoint    = gp_Pnt(0.0, 0.0, 0.0),
                                          const double   theCriteria = 1.e+5);
};
