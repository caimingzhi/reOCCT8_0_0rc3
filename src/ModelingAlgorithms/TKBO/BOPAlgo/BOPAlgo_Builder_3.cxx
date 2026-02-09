#include <BOPAlgo_Builder.hpp>

#include <TopAbs_State.hpp>

#include <TopoDS.hpp>
#include <TopoDS_AlertWithShape.hpp>
#include <TopoDS_Shape.hpp>

#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>

#include <BRep_Builder.hpp>

#include <BOPAlgo_BuilderSolid.hpp>

#include <IntTools_Context.hpp>

#include <BOPDS_DS.hpp>
#include <BOPDS_ShapeInfo.hpp>

#include <BOPTools_AlgoTools.hpp>
#include <BOPTools_Set.hpp>
#include <NCollection_Map.hpp>
#include <BOPTools_Parallel.hpp>

#include <BOPAlgo_Tools.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_Vector.hpp>

#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedDataMap.hpp>

#include <algorithm>

static void OwnInternalShapes(const TopoDS_Shape&,
                              NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&);

void BOPAlgo_Builder::FillImagesSolids(const Message_ProgressRange& theRange)
{
  int i = 0, aNbS = myDS->NbSourceShapes();
  for (i = 0; i < aNbS; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (aSI.ShapeType() == TopAbs_SOLID)
    {
      break;
    }
  }
  if (i >= aNbS)
  {
    return;
  }

  Message_ProgressScope aPS(theRange, "Building splits of solids", 10);

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> aDraftSolids;

  FillIn3DParts(aDraftSolids, aPS.Next(4));
  if (HasErrors())
  {
    return;
  }

  BuildSplitSolids(aDraftSolids, aPS.Next(5));
  if (HasErrors())
  {
    return;
  }

  FillInternalShapes(aPS.Next());
}

void BOPAlgo_Builder::FillIn3DParts(
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theDraftSolids,
  const Message_ProgressRange&                                              theRange)
{
  Message_ProgressScope aPS(theRange, nullptr, 2);

  occ::handle<NCollection_BaseAllocator> anAlloc = new NCollection_IncAllocator;

  NCollection_DataMap<TopoDS_Shape, Bnd_Box, TopTools_ShapeMapHasher> aShapeBoxMap(1, anAlloc);

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence(1, anAlloc);

  NCollection_List<TopoDS_Shape> aLFaces(anAlloc);

  int i, aNbS = myDS->NbSourceShapes();
  for (i = 0; i < aNbS; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (aSI.ShapeType() != TopAbs_FACE)
      continue;

    if (UserBreak(aPS))
    {
      return;
    }

    const TopoDS_Shape&                   aS    = aSI.Shape();
    const NCollection_List<TopoDS_Shape>* pLSIm = myImages.Seek(aS);

    if (pLSIm)
    {
      NCollection_List<TopoDS_Shape>::Iterator aItLSIm(*pLSIm);
      for (; aItLSIm.More(); aItLSIm.Next())
      {
        const TopoDS_Shape& aSIm = aItLSIm.Value();
        if (aMFence.Add(aSIm))
          aLFaces.Append(aSIm);
      }
    }
    else
    {
      aLFaces.Append(aS);
      aShapeBoxMap.Bind(aS, aSI.Box());
    }
  }

  BRep_Builder aBB;

  NCollection_List<TopoDS_Shape> aLSolids(anAlloc);

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aSolidsIF(1, anAlloc);

  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> aDraftSolid(
    1,
    anAlloc);

  for (i = 0; i < aNbS; ++i)
  {
    BOPDS_ShapeInfo& aSI = myDS->ChangeShapeInfo(i);
    if (aSI.ShapeType() != TopAbs_SOLID)
    {
      continue;
    }
    if (UserBreak(aPS))
    {
      return;
    }
    const TopoDS_Shape& aS     = aSI.Shape();
    const TopoDS_Solid& aSolid = (*(TopoDS_Solid*)(&aS));

    Bnd_Box& aBoxS = aSI.ChangeBox();
    if (aBoxS.IsVoid())
      myDS->BuildBndBoxSolid(i, aBoxS, myCheckInverted);

    NCollection_List<TopoDS_Shape> aLIF;
    TopoDS_Solid                   aSD;
    aBB.MakeSolid(aSD);
    BuildDraftSolid(aSolid, aSD, aLIF);

    aLSolids.Append(aSD);
    aSolidsIF.Bind(aSD, aLIF);
    aShapeBoxMap.Bind(aSD, aBoxS);
    aDraftSolid.Add(aS, aSD);
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    anInParts;

  BOPAlgo_Tools::ClassifyFaces(aLFaces,
                               aLSolids,
                               myRunParallel,
                               myContext,
                               anInParts,
                               aShapeBoxMap,
                               aSolidsIF,
                               aPS.Next());

  int aNbSol = aDraftSolid.Extent();
  for (i = 1; i <= aNbSol; ++i)
  {
    if (UserBreak(aPS))
    {
      return;
    }
    const TopoDS_Solid&                   aSolid     = TopoDS::Solid(aDraftSolid.FindKey(i));
    const TopoDS_Solid&                   aSDraft    = TopoDS::Solid(aDraftSolid(i));
    const NCollection_List<TopoDS_Shape>& aLInFaces  = anInParts.FindFromKey(aSDraft);
    const NCollection_List<TopoDS_Shape>& aLInternal = aSolidsIF.Find(aSDraft);

    int aNbIN = aLInFaces.Extent();

    if (!aNbIN)
    {
      bool bHasImage = false;

      for (TopoDS_Iterator it(aSolid); it.More() && !bHasImage; it.Next())
        bHasImage = myImages.IsBound(it.Value());

      if (!bHasImage)

        continue;
    }

    theDraftSolids.Bind(aSolid, aSDraft);

    int aNbInt = aLInternal.Extent();
    if (aNbInt || aNbIN)
    {

      NCollection_List<TopoDS_Shape>* pLIN =
        myInParts.Bound(aSolid, NCollection_List<TopoDS_Shape>());

      NCollection_List<TopoDS_Shape>::Iterator aItLS(aLInFaces);
      for (; aItLS.More(); aItLS.Next())
        pLIN->Append(aItLS.Value());

      aItLS.Initialize(aLInternal);
      for (; aItLS.More(); aItLS.Next())
        pLIN->Append(aItLS.Value());
    }
  }
}

void BOPAlgo_Builder::BuildDraftSolid(const TopoDS_Shape&             theSolid,
                                      TopoDS_Shape&                   theDraftSolid,
                                      NCollection_List<TopoDS_Shape>& theLIF)
{
  bool                                     bToReverse;
  int                                      iFlag;
  TopAbs_Orientation                       aOrF, aOrSh, aOrSd;
  TopoDS_Iterator                          aIt1, aIt2;
  TopoDS_Shell                             aShD;
  TopoDS_Shape                             aFx;
  BRep_Builder                             aBB;
  NCollection_List<TopoDS_Shape>::Iterator aItS;

  aOrSd = theSolid.Orientation();
  theDraftSolid.Orientation(aOrSd);

  aIt1.Initialize(theSolid);
  for (; aIt1.More(); aIt1.Next())
  {
    const TopoDS_Shape& aSh = aIt1.Value();
    if (aSh.ShapeType() != TopAbs_SHELL)
    {
      continue;
    }

    aOrSh = aSh.Orientation();
    aBB.MakeShell(aShD);
    aShD.Orientation(aOrSh);
    iFlag = 0;

    aIt2.Initialize(aSh);
    for (; aIt2.More(); aIt2.Next())
    {
      const TopoDS_Shape& aF = aIt2.Value();
      aOrF                   = aF.Orientation();

      if (myImages.IsBound(aF))
      {
        const NCollection_List<TopoDS_Shape>& aLSp = myImages.Find(aF);
        aItS.Initialize(aLSp);
        for (; aItS.More(); aItS.Next())
        {
          aFx = aItS.Value();

          if (myShapesSD.IsBound(aFx))
          {

            if (aOrF == TopAbs_INTERNAL)
            {
              aFx.Orientation(aOrF);
              theLIF.Append(aFx);
            }
            else
            {
              bToReverse =
                BOPTools_AlgoTools::IsSplitToReverseWithWarn(aFx, aF, myContext, myReport);
              if (bToReverse)
              {
                aFx.Reverse();
              }

              iFlag = 1;
              aBB.Add(aShD, aFx);
            }
          }
          else
          {
            aFx.Orientation(aOrF);
            if (aOrF == TopAbs_INTERNAL)
            {
              theLIF.Append(aFx);
            }
            else
            {
              iFlag = 1;
              aBB.Add(aShD, aFx);
            }
          }
        }
      }

      else
      {
        if (aOrF == TopAbs_INTERNAL)
        {
          theLIF.Append(aF);
        }
        else
        {
          iFlag = 1;
          aBB.Add(aShD, aF);
        }
      }
    }

    if (iFlag)
    {
      aShD.Closed(BRep_Tool::IsClosed(aShD));
      aBB.Add(theDraftSolid, aShD);
    }
  }
}

class BOPAlgo_SplitSolid : public BOPAlgo_BuilderSolid
{
public:
  void SetSolid(const TopoDS_Solid& theSolid) { mySolid = theSolid; }

  const TopoDS_Solid& Solid() const { return mySolid; }

  void SetProgressRange(const Message_ProgressRange& theRange) { myRange = theRange; }

  void Perform()
  {
    Message_ProgressScope aPS(myRange, nullptr, 1);
    if (!aPS.More())
    {
      return;
    }
    BOPAlgo_BuilderSolid::Perform(aPS.Next());
  }

private:
  void Perform(const Message_ProgressRange&) override {}

private:
  TopoDS_Solid          mySolid;
  Message_ProgressRange myRange;
};

typedef NCollection_Vector<BOPAlgo_SplitSolid> BOPAlgo_VectorOfBuilderSolid;

void BOPAlgo_Builder::BuildSplitSolids(
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theDraftSolids,
  const Message_ProgressRange&                                              theRange)
{
  bool                                     bFlagSD;
  int                                      i, aNbS;
  TopExp_Explorer                          aExp;
  NCollection_List<TopoDS_Shape>::Iterator aIt;

  occ::handle<NCollection_BaseAllocator> aAlr0;
  aAlr0 = NCollection_BaseAllocator::CommonBaseAllocator();

  NCollection_List<TopoDS_Shape>                         aSFS(aAlr0), aLSEmpty(aAlr0);
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence(100, aAlr0);
  NCollection_Map<BOPTools_Set>                          aMST(100, aAlr0);
  BOPAlgo_VectorOfBuilderSolid                           aVBS;

  Message_ProgressScope aPSOuter(theRange, nullptr, 10);

  aNbS = myDS->NbSourceShapes();
  for (i = 0; i < aNbS; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);

    if (aSI.ShapeType() != TopAbs_SOLID)
    {
      continue;
    }
    if (UserBreak(aPSOuter))
    {
      return;
    }

    const TopoDS_Shape& aS = aSI.Shape();
    if (!aMFence.Add(aS))
    {
      continue;
    }
    if (theDraftSolids.IsBound(aS))
    {
      continue;
    }

    BOPTools_Set aST;

    aST.Add(aS, TopAbs_FACE);
    aMST.Add(aST);
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aSolidsIm;

  for (i = 0; i < aNbS; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (aSI.ShapeType() != TopAbs_SOLID)
      continue;

    const TopoDS_Shape& aS     = aSI.Shape();
    const TopoDS_Solid& aSolid = (*(TopoDS_Solid*)(&aS));
    if (!theDraftSolids.IsBound(aS))
      continue;

    const TopoDS_Shape&                   aSD   = theDraftSolids.Find(aS);
    const NCollection_List<TopoDS_Shape>* pLFIN = myInParts.Seek(aS);
    if (!pLFIN || pLFIN->IsEmpty())
    {
      aSolidsIm(aSolidsIm.Add(aS, NCollection_List<TopoDS_Shape>())).Append(aSD);
      continue;
    }

    aSFS.Clear();

    aExp.Init(aSD, TopAbs_FACE);
    for (; aExp.More(); aExp.Next())
    {
      const TopoDS_Shape& aF = aExp.Current();
      aSFS.Append(aF);
    }

    aIt.Initialize(*pLFIN);
    for (; aIt.More(); aIt.Next())
    {
      TopoDS_Shape aF = aIt.Value();

      aF.Orientation(TopAbs_FORWARD);
      aSFS.Append(aF);
      aF.Orientation(TopAbs_REVERSED);
      aSFS.Append(aF);
    }

    BOPAlgo_SplitSolid& aBS = aVBS.Appended();
    aBS.SetSolid(aSolid);
    aBS.SetShapes(aSFS);
    aBS.SetRunParallel(myRunParallel);
  }

  int k, aNbBS;

  aNbBS = aVBS.Length();

  Message_ProgressScope aPSParallel(aPSOuter.Next(9), "Splitting solids", aNbBS);
  for (int iS = 0; iS < aNbBS; iS++)
  {
    BOPAlgo_SplitSolid& aSplitSolid = aVBS.ChangeValue(iS);
    aSplitSolid.SetProgressRange(aPSParallel.Next());
  }

  BOPTools_Parallel::Perform(myRunParallel, aVBS);

  if (UserBreak(aPSOuter))
  {
    return;
  }

  for (k = 0; k < aNbBS; ++k)
  {
    BOPAlgo_SplitSolid& aBS = aVBS(k);
    aSolidsIm.Add(aBS.Solid(), aBS.Areas());

    const occ::handle<Message_Report>& aBSReport       = aBS.GetReport();
    Message_Gravity                    anAlertTypes[2] = {Message_Warning, Message_Fail};
    for (int iGravity = 0; iGravity < 2; iGravity++)
    {
      const NCollection_List<occ::handle<Message_Alert>>& anLAlerts =
        aBSReport->GetAlerts(anAlertTypes[iGravity]);
      for (NCollection_List<occ::handle<Message_Alert>>::Iterator itA(anLAlerts); itA.More();
           itA.Next())
      {
        occ::handle<Message_Alert> anAlert = itA.Value();

        occ::handle<TopoDS_AlertWithShape> anAlertWithShape =
          occ::down_cast<TopoDS_AlertWithShape>(itA.Value());
        if (!anAlertWithShape.IsNull())
        {
          TopoDS_Shape aWarnShape;
          BRep_Builder().MakeCompound(TopoDS::Compound(aWarnShape));
          BRep_Builder().Add(aWarnShape, aBS.Solid());
          BRep_Builder().Add(aWarnShape, anAlertWithShape->GetShape());

          anAlertWithShape->SetShape(aWarnShape);
          AddWarning(anAlertWithShape);
        }
        else
          AddWarning(anAlert);
      }
    }
  }

  aNbBS = aSolidsIm.Extent();
  for (k = 1; k <= aNbBS; ++k)
  {
    const TopoDS_Shape&                   aS   = aSolidsIm.FindKey(k);
    const NCollection_List<TopoDS_Shape>& aLSR = aSolidsIm(k);

    if (!myImages.IsBound(aS))
    {
      NCollection_List<TopoDS_Shape>* pLSx = myImages.Bound(aS, NCollection_List<TopoDS_Shape>());

      aIt.Initialize(aLSR);
      for (; aIt.More(); aIt.Next())
      {
        BOPTools_Set aST;

        const TopoDS_Shape& aSR = aIt.Value();
        aST.Add(aSR, TopAbs_FACE);

        bFlagSD = aMST.Contains(aST);

        const BOPTools_Set& aSTx = aMST.Added(aST);
        const TopoDS_Shape& aSx  = aSTx.Shape();
        pLSx->Append(aSx);

        NCollection_List<TopoDS_Shape>* pLOr = myOrigins.ChangeSeek(aSx);
        if (!pLOr)
        {
          pLOr = myOrigins.Bound(aSx, NCollection_List<TopoDS_Shape>());
        }
        pLOr->Append(aS);

        if (bFlagSD)
        {
          myShapesSD.Bind(aSR, aSx);
        }
      }
    }
  }
}

void BOPAlgo_Builder::FillInternalShapes(const Message_ProgressRange& theRange)
{
  int                                      i, j, aNbS, aNbSI, aNbSx;
  TopAbs_ShapeEnum                         aType;
  TopAbs_State                             aState;
  TopoDS_Iterator                          aItS;
  BRep_Builder                             aBB;
  NCollection_List<TopoDS_Shape>::Iterator aIt, aIt1;

  occ::handle<NCollection_BaseAllocator> aAllocator;

  aAllocator = NCollection_BaseAllocator::CommonBaseAllocator();

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                aMSx(100, aAllocator);
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMx(100, aAllocator);
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMSI(100, aAllocator);
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>        aMFence(100, aAllocator);
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>        aMSOr(100, aAllocator);
  NCollection_List<TopoDS_Shape>                                aLSd(aAllocator);
  NCollection_List<TopoDS_Shape>                                aLArgs(aAllocator);
  NCollection_List<TopoDS_Shape>                                aLSC(aAllocator);
  NCollection_List<TopoDS_Shape>                                aLSI(aAllocator);

  Message_ProgressScope aPS(theRange, nullptr, 10);

  const NCollection_List<TopoDS_Shape>& aArguments = myDS->Arguments();
  aIt.Initialize(aArguments);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aS = aIt.Value();
    BOPTools_AlgoTools::TreatCompound(aS, aLSC, &aMFence);
  }
  aIt.Initialize(aLSC);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aS = aIt.Value();
    aType                  = aS.ShapeType();
    if (aType == TopAbs_WIRE)
    {
      aItS.Initialize(aS);
      for (; aItS.More(); aItS.Next())
      {
        const TopoDS_Shape& aE = aItS.Value();
        if (aMFence.Add(aE))
        {
          aLArgs.Append(aE);
        }
      }
    }
    else if (aType == TopAbs_VERTEX || aType == TopAbs_EDGE)
    {
      aLArgs.Append(aS);
    }
  }
  aMFence.Clear();

  aIt.Initialize(aLArgs);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aS = aIt.Value();
    aType                  = aS.ShapeType();
    if (aType == TopAbs_VERTEX || aType == TopAbs_EDGE || aType == TopAbs_WIRE)
    {
      if (aMFence.Add(aS))
      {
        if (myImages.IsBound(aS))
        {
          const NCollection_List<TopoDS_Shape>& aLSp = myImages.Find(aS);
          aIt1.Initialize(aLSp);
          for (; aIt1.More(); aIt1.Next())
          {
            const TopoDS_Shape& aSp = aIt1.Value();
            aMSI.Add(aSp);
          }
        }
        else
        {
          aMSI.Add(aS);
        }
      }
    }
  }
  if (UserBreak(aPS))
  {
    return;
  }

  aNbSI = aMSI.Extent();

  aMFence.Clear();
  aLSd.Clear();

  aNbS = myDS->NbSourceShapes();
  for (i = 0; i < aNbS; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);

    if (aSI.ShapeType() != TopAbs_SOLID)
    {
      continue;
    }
    if (UserBreak(aPS))
    {
      return;
    }

    const TopoDS_Shape& aS = aSI.Shape();

    aMx.Clear();
    OwnInternalShapes(aS, aMx);

    aNbSx = aMx.Extent();
    for (j = 1; j <= aNbSx; ++j)
    {
      const TopoDS_Shape& aSi = aMx(j);
      if (myImages.IsBound(aSi))
      {
        const NCollection_List<TopoDS_Shape>& aLSp = myImages.Find(aSi);
        aIt1.Initialize(aLSp);
        for (; aIt1.More(); aIt1.Next())
        {
          const TopoDS_Shape& aSp = aIt1.Value();
          aMSI.Add(aSp);
        }
      }
      else
      {
        aMSI.Add(aSi);
      }
    }

    if (myImages.IsBound(aS))
    {
      const NCollection_List<TopoDS_Shape>& aLSp = myImages.Find(aS);
      aIt.Initialize(aLSp);
      for (; aIt.More(); aIt.Next())
      {
        const TopoDS_Shape& aSp = aIt.Value();
        if (aMFence.Add(aSp))
        {
          TopExp::MapShapesAndAncestors(aSp, TopAbs_VERTEX, TopAbs_EDGE, aMSx);
          TopExp::MapShapesAndAncestors(aSp, TopAbs_VERTEX, TopAbs_FACE, aMSx);
          TopExp::MapShapesAndAncestors(aSp, TopAbs_EDGE, TopAbs_FACE, aMSx);
          aLSd.Append(aSp);
        }
      }
    }
    else
    {
      if (aMFence.Add(aS))
      {
        TopExp::MapShapesAndAncestors(aS, TopAbs_VERTEX, TopAbs_EDGE, aMSx);
        TopExp::MapShapesAndAncestors(aS, TopAbs_VERTEX, TopAbs_FACE, aMSx);
        TopExp::MapShapesAndAncestors(aS, TopAbs_EDGE, TopAbs_FACE, aMSx);
        aLSd.Append(aS);
        aMSOr.Add(aS);
      }
    }
  }

  aNbSI = aMSI.Extent();
  for (i = 1; i <= aNbSI; ++i)
  {
    const TopoDS_Shape& aSI = aMSI(i);
    if (aMSx.Contains(aSI))
    {
      const NCollection_List<TopoDS_Shape>& aLSx = aMSx.FindFromKey(aSI);
      aNbSx                                      = aLSx.Extent();
      if (!aNbSx)
      {
        aLSI.Append(aSI);
      }
    }
    else
    {
      aLSI.Append(aSI);
    }
  }

  aNbSI = aLSI.Extent();
  if (!aNbSI)
  {
    return;
  }

  aPS.Next();

  aMx.Clear();

  Message_ProgressScope aPSLoop(aPS.Next(9), "Looking for internal shapes", aLSd.Size());

  aIt.Initialize(aLSd);
  for (; aIt.More(); aIt.Next(), aPSLoop.Next())
  {
    TopoDS_Solid aSd = TopoDS::Solid(aIt.Value());

    aIt1.Initialize(aLSI);
    for (; aIt1.More();)
    {
      TopoDS_Shape aSI = aIt1.Value();
      aSI.Orientation(TopAbs_INTERNAL);

      aState = BOPTools_AlgoTools::ComputeStateByOnePoint(aSI, aSd, 1.e-11, myContext);

      if (aState != TopAbs_IN)
      {
        aIt1.Next();
        continue;
      }

      if (aMSOr.Contains(aSd))
      {

        TopoDS_Solid aSdx;

        aBB.MakeSolid(aSdx);
        aItS.Initialize(aSd);
        for (; aItS.More(); aItS.Next())
        {
          const TopoDS_Shape& aSh = aItS.Value();
          aBB.Add(aSdx, aSh);
        }

        aBB.Add(aSdx, aSI);

        NCollection_List<TopoDS_Shape>* pLS = myImages.Bound(aSd, NCollection_List<TopoDS_Shape>());
        pLS->Append(aSdx);

        NCollection_List<TopoDS_Shape>* pLOr =
          myOrigins.Bound(aSdx, NCollection_List<TopoDS_Shape>());
        pLOr->Append(aSd);

        aMSOr.Remove(aSd);
        aSd = aSdx;
      }
      else
      {
        aBB.Add(aSd, aSI);
      }

      aLSI.Remove(aIt1);
    }
  }

  aLArgs.Clear();
  aLSd.Clear();
  aMSOr.Clear();
  aMFence.Clear();
  aMSI.Clear();
  aMx.Clear();
  aMSx.Clear();
}

void OwnInternalShapes(const TopoDS_Shape&                                            theS,
                       NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMx)
{
  TopoDS_Iterator aIt;

  aIt.Initialize(theS);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aSx = aIt.Value();
    if (aSx.ShapeType() != TopAbs_SHELL)
    {
      theMx.Add(aSx);
    }
  }
}
