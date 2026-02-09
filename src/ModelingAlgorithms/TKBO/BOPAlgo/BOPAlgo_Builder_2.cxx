#include <BOPAlgo_Builder.hpp>
#include <BOPAlgo_Alerts.hpp>
#include <BOPAlgo_BuilderFace.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BOPAlgo_Tools.hpp>
#include <BOPDS_DS.hpp>
#include <BOPDS_FaceInfo.hpp>
#include <BOPDS_Interf.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <BOPDS_ShapeInfo.hpp>
#include <NCollection_Vector.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BOPTools_AlgoTools2D.hpp>
#include <BOPTools_AlgoTools3D.hpp>
#include <BOPTools_Set.hpp>
#include <NCollection_Map.hpp>
#include <BOPTools_Parallel.hpp>
#include <BRep_Builder.hpp>
#include <BRepLib.hpp>
#include <BRep_Tool.hpp>
#include <GeomLib.hpp>
#include <NCollection_IncAllocator.hpp>
#include <IntTools_Context.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

#include <algorithm>

static TopoDS_Face BuildDraftFace(
  const TopoDS_Face& theFace,
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                     theImages,
  occ::handle<IntTools_Context>&     theCtx,
  const occ::handle<Message_Report>& theReport);

class BOPAlgo_PairOfShapeBoolean : public BOPAlgo_ParallelAlgo
{

public:
  DEFINE_STANDARD_ALLOC

  BOPAlgo_PairOfShapeBoolean()
      : BOPAlgo_ParallelAlgo(),
        myFlag(false)
  {
  }

  ~BOPAlgo_PairOfShapeBoolean() override = default;

  TopoDS_Shape& Shape1() { return myShape1; }

  TopoDS_Shape& Shape2() { return myShape2; }

  bool& Flag() { return myFlag; }

  void SetContext(const occ::handle<IntTools_Context>& aContext) { myContext = aContext; }

  const occ::handle<IntTools_Context>& Context() const { return myContext; }

  void Perform() override
  {
    Message_ProgressScope aPS(myProgressRange, nullptr, 1);
    if (UserBreak(aPS))
    {
      return;
    }

    const TopoDS_Face& aFj = *((TopoDS_Face*)&myShape1);
    const TopoDS_Face& aFk = *((TopoDS_Face*)&myShape2);
    myFlag = BOPTools_AlgoTools::AreFacesSameDomain(aFj, aFk, myContext, myFuzzyValue);
  }

protected:
  bool                          myFlag;
  TopoDS_Shape                  myShape1;
  TopoDS_Shape                  myShape2;
  occ::handle<IntTools_Context> myContext;
};

typedef NCollection_Vector<BOPAlgo_PairOfShapeBoolean> BOPAlgo_VectorOfPairOfShapeBoolean;

class BOPAlgo_SplitFace : public BOPAlgo_BuilderFace
{
public:
  void SetProgressRange(const Message_ProgressRange& theRange) { myRange = theRange; }

  void Perform()
  {
    Message_ProgressScope aPS(myRange, nullptr, 1);
    if (!aPS.More())
    {
      return;
    }
    BOPAlgo_BuilderFace::Perform(aPS.Next());
  }

private:
  void Perform(const Message_ProgressRange&) override {};

private:
  Message_ProgressRange myRange;
};

typedef NCollection_Vector<BOPAlgo_SplitFace> BOPAlgo_VectorOfBuilderFace;

class BOPAlgo_VFI : public BOPAlgo_ParallelAlgo
{

public:
  DEFINE_STANDARD_ALLOC

  BOPAlgo_VFI()
      : BOPAlgo_ParallelAlgo(),
        myIsInternal(false)
  {
  }

  ~BOPAlgo_VFI() override = default;

  void SetVertex(const TopoDS_Vertex& aV) { myV = aV; }

  TopoDS_Vertex& Vertex() { return myV; }

  void SetFace(const TopoDS_Face& aF) { myF = aF; }

  TopoDS_Face& Face() { return myF; }

  bool IsInternal() const { return myIsInternal; }

  void SetContext(const occ::handle<IntTools_Context>& aContext) { myContext = aContext; }

  const occ::handle<IntTools_Context>& Context() const { return myContext; }

  void Perform() override
  {
    Message_ProgressScope aPS(myProgressRange, nullptr, 1);
    if (UserBreak(aPS))
    {
      return;
    }

    double aT1, aT2, dummy;

    int iFlag    = myContext->ComputeVF(myV, myF, aT1, aT2, dummy, myFuzzyValue);
    myIsInternal = (iFlag == 0);
  }

protected:
  bool                          myIsInternal;
  TopoDS_Vertex                 myV;
  TopoDS_Face                   myF;
  occ::handle<IntTools_Context> myContext;
};

typedef NCollection_Vector<BOPAlgo_VFI> BOPAlgo_VectorOfVFI;

void BOPAlgo_Builder::FillImagesFaces(const Message_ProgressRange& theRange)
{
  Message_ProgressScope aPS(theRange, "Filling splits of faces", 10);
  BuildSplitFaces(aPS.Next(9));
  if (HasErrors())
  {
    return;
  }
  FillSameDomainFaces(aPS.Next(0.5));
  if (HasErrors())
  {
    return;
  }
  FillInternalVertices(aPS.Next(0.5));
}

void BOPAlgo_Builder::BuildSplitFaces(const Message_ProgressRange& theRange)
{
  bool                                     bHasFaceInfo, bIsClosed, bIsDegenerated, bToReverse;
  int                                      i, j, k, aNbS, aNbPBIn, aNbPBOn, aNbPBSc, aNbAV, nSp;
  TopoDS_Face                              aFF, aFSD;
  TopoDS_Edge                              aSp, aEE;
  TopAbs_Orientation                       anOriF, anOriE;
  TopExp_Explorer                          aExp;
  NCollection_List<TopoDS_Shape>::Iterator aIt;
  NCollection_List<int>                    aLIAV;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;
  occ::handle<NCollection_BaseAllocator>                 aAllocator;
  BOPAlgo_VectorOfBuilderFace                            aVBF;

  aAllocator = NCollection_BaseAllocator::CommonBaseAllocator();

  NCollection_List<TopoDS_Shape>                         aLE(aAllocator);
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMDE(100, aAllocator);

  Message_ProgressScope aPSOuter(theRange, nullptr, 10);

  NCollection_IndexedDataMap<int, NCollection_List<TopoDS_Shape>> aFacesIm;

  aNbS = myDS->NbSourceShapes();

  for (i = 0; i < aNbS; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (aSI.ShapeType() != TopAbs_FACE)
    {
      continue;
    }
    if (UserBreak(aPSOuter))
    {
      return;
    }

    const TopoDS_Face& aF        = (*(TopoDS_Face*)(&aSI.Shape()));
    bool               isUClosed = false, isVClosed = false, isChecked = false;

    bHasFaceInfo = myDS->HasFaceInfo(i);
    if (!bHasFaceInfo)
    {
      continue;
    }

    const BOPDS_FaceInfo& aFI = myDS->FaceInfo(i);

    const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& aMPBIn = aFI.PaveBlocksIn();
    const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& aMPBOn = aFI.PaveBlocksOn();
    const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& aMPBSc = aFI.PaveBlocksSc();
    aLIAV.Clear();
    myDS->AloneVertices(i, aLIAV);

    aNbPBIn = aMPBIn.Extent();
    aNbPBOn = aMPBOn.Extent();
    aNbPBSc = aMPBSc.Extent();
    aNbAV   = aLIAV.Extent();
    if (!aNbPBIn && !aNbPBOn && !aNbPBSc && !aNbAV)
    {
      continue;
    }

    if (!aNbPBIn && !aNbPBSc)
    {

      bool hasInternals = false;
      if (!aNbAV)
      {

        bool hasModified = false;

        TopoDS_Iterator aItW(aF);
        for (; aItW.More(); aItW.Next())
        {
          TopoDS_Iterator itE(aItW.Value());
          hasInternals = (itE.More() && (itE.Value().Orientation() == TopAbs_INTERNAL));
          if (hasInternals)
            break;

          hasModified |= myImages.IsBound(aItW.Value());
        }

        if (!hasInternals && !hasModified)
          continue;
      }

      if (!hasInternals)
      {

        TopoDS_Face aFD = BuildDraftFace(aF, myImages, myContext, myReport);
        if (!aFD.IsNull())
        {
          aFacesIm(aFacesIm.Add(i, NCollection_List<TopoDS_Shape>())).Append(aFD);
          continue;
        }
      }
    }

    aMFence.Clear();

    anOriF = aF.Orientation();
    aFF    = aF;
    aFF.Orientation(TopAbs_FORWARD);

    aLE.Clear();

    aExp.Init(aFF, TopAbs_EDGE);
    for (; aExp.More(); aExp.Next())
    {
      const TopoDS_Edge& aE = (*(TopoDS_Edge*)(&aExp.Current()));
      anOriE                = aE.Orientation();

      if (!myImages.IsBound(aE))
      {
        if (anOriE == TopAbs_INTERNAL)
        {
          aEE = aE;
          aEE.Orientation(TopAbs_FORWARD);
          aLE.Append(aEE);
          aEE.Orientation(TopAbs_REVERSED);
          aLE.Append(aEE);
        }
        else
        {
          aLE.Append(aE);
        }

        continue;
      }

      if (!isChecked)
      {
        const occ::handle<Geom_Surface> aSurf = BRep_Tool::Surface(aF);
        GeomLib::IsClosed(aSurf, BRep_Tool::Tolerance(aE), isUClosed, isVClosed);

        isChecked = true;
      }

      bIsClosed = false;

      if ((isUClosed || isVClosed) && BRep_Tool::IsClosed(aE, aF))
      {

        bool isUIso = false, isVIso = false;
        BOPTools_AlgoTools2D::IsEdgeIsoline(aE, aF, isUIso, isVIso);

        bIsClosed = ((isUClosed && isUIso) || (isVClosed && isVIso));
      }

      bIsDegenerated = BRep_Tool::Degenerated(aE);

      const NCollection_List<TopoDS_Shape>& aLIE = myImages.Find(aE);
      aIt.Initialize(aLIE);
      for (; aIt.More(); aIt.Next())
      {
        aSp = (*(TopoDS_Edge*)(&aIt.Value()));
        if (bIsDegenerated)
        {
          aSp.Orientation(anOriE);
          aLE.Append(aSp);
          continue;
        }

        if (anOriE == TopAbs_INTERNAL)
        {
          aSp.Orientation(TopAbs_FORWARD);
          aLE.Append(aSp);
          aSp.Orientation(TopAbs_REVERSED);
          aLE.Append(aSp);
          continue;
        }

        if (bIsClosed)
        {
          if (aMFence.Add(aSp))
          {
            if (!BRep_Tool::IsClosed(aSp, aF))
            {
              if (!BOPTools_AlgoTools3D::DoSplitSEAMOnFace(aSp, aF))
              {

                if (!BOPTools_AlgoTools3D::DoSplitSEAMOnFace(aE, aSp, aF))
                {
                  TopoDS_Compound aWS;
                  BRep_Builder().MakeCompound(aWS);
                  BRep_Builder().Add(aWS, aF);
                  BRep_Builder().Add(aWS, aSp);
                  AddWarning(new BOPAlgo_AlertUnableToMakeClosedEdgeOnFace(aWS));
                }
              }
            }

            aSp.Orientation(TopAbs_FORWARD);
            aLE.Append(aSp);
            aSp.Orientation(TopAbs_REVERSED);
            aLE.Append(aSp);
          }
          continue;
        }

        aSp.Orientation(anOriE);
        bToReverse = BOPTools_AlgoTools::IsSplitToReverseWithWarn(aSp, aE, myContext, myReport);
        if (bToReverse)
        {
          aSp.Reverse();
        }
        aLE.Append(aSp);
      }
    }

    for (j = 1; j <= aNbPBIn; ++j)
    {
      const occ::handle<BOPDS_PaveBlock>& aPB = aMPBIn(j);
      nSp                                     = aPB->Edge();
      Standard_ASSERT(nSp >= 0, "Face information is not up to date", continue);
      aSp = (*(TopoDS_Edge*)(&myDS->Shape(nSp)));

      aSp.Orientation(TopAbs_FORWARD);
      aLE.Append(aSp);
      aSp.Orientation(TopAbs_REVERSED);
      aLE.Append(aSp);
    }

    for (j = 1; j <= aNbPBSc; ++j)
    {
      const occ::handle<BOPDS_PaveBlock>& aPB = aMPBSc(j);
      nSp                                     = aPB->Edge();
      aSp                                     = (*(TopoDS_Edge*)(&myDS->Shape(nSp)));

      aSp.Orientation(TopAbs_FORWARD);
      aLE.Append(aSp);
      aSp.Orientation(TopAbs_REVERSED);
      aLE.Append(aSp);
    }

    if (!myPaveFiller->NonDestructive())
    {

      BRepLib::BuildPCurveForEdgesOnPlane(aLE, aFF);
    }

    BOPAlgo_SplitFace& aBF = aVBF.Appended();
    aBF.SetFace(aF);
    aBF.SetShapes(aLE);
    aBF.SetRunParallel(myRunParallel);
  }

  aPSOuter.Next();

  int aNbBF = aVBF.Length();

  Message_ProgressScope aPSParallel(aPSOuter.Next(9), "Splitting faces", aNbBF);
  for (int iF = 0; iF < aNbBF; iF++)
  {
    BOPAlgo_SplitFace& aBF = aVBF.ChangeValue(iF);
    aBF.SetProgressRange(aPSParallel.Next());
  }

  BOPTools_Parallel::Perform(myRunParallel, aVBF);

  if (UserBreak(aPSOuter))
  {
    return;
  }
  for (k = 0; k < aNbBF; ++k)
  {
    BOPAlgo_BuilderFace& aBF = aVBF(k);
    aFacesIm.Add(myDS->Index(aBF.Face()), aBF.Areas());
    myReport->Merge(aBF.GetReport());
  }

  aNbBF = aFacesIm.Extent();
  for (k = 1; k <= aNbBF; ++k)
  {
    const TopoDS_Face& aF                      = TopoDS::Face(myDS->Shape(aFacesIm.FindKey(k)));
    anOriF                                     = aF.Orientation();
    const NCollection_List<TopoDS_Shape>& aLFR = aFacesIm(k);

    NCollection_List<TopoDS_Shape>* pLFIm = myImages.Bound(aF, NCollection_List<TopoDS_Shape>());
    aIt.Initialize(aLFR);
    for (; aIt.More(); aIt.Next())
    {
      TopoDS_Shape& aFR = aIt.ChangeValue();
      if (anOriF == TopAbs_REVERSED)
        aFR.Orientation(TopAbs_REVERSED);
      pLFIm->Append(aFR);
    }
  }
}

typedef NCollection_IndexedDataMap<BOPTools_Set, NCollection_List<TopoDS_Shape>>
  BOPAlgo_IndexedDataMapOfSetListOfShape;

static void AddEdgeSet(const TopoDS_Shape&                           theS,
                       BOPAlgo_IndexedDataMapOfSetListOfShape&       theMap,
                       const occ::handle<NCollection_BaseAllocator>& theAllocator)
{

  BOPTools_Set aSE;
  aSE.Add(theS, TopAbs_EDGE);

  NCollection_List<TopoDS_Shape>* pLF = theMap.ChangeSeek(aSE);
  if (!pLF)
    pLF = &theMap(theMap.Add(aSE, NCollection_List<TopoDS_Shape>(theAllocator)));
  pLF->Append(theS);
}

void BOPAlgo_Builder::FillSameDomainFaces(const Message_ProgressRange& theRange)
{

  const NCollection_Vector<BOPDS_InterfFF>& aFFs   = myDS->InterfFF();
  int                                       aNbFFs = aFFs.Length();
  if (!aNbFFs)
    return;

  Message_ProgressScope aPSOuter(theRange, nullptr, 10);

  occ::handle<NCollection_BaseAllocator> aAllocator = new NCollection_IncAllocator;

  NCollection_Vector<int> aFIVec(256, aAllocator);

  NCollection_Map<int> aMFence(1, aAllocator);

  for (int i = 0; i < aNbFFs; ++i)
  {
    if (UserBreak(aPSOuter))
    {
      return;
    }
    const BOPDS_InterfFF& aFF = aFFs(i);

    int nF[2];
    aFF.Indices(nF[0], nF[1]);

    for (int j = 0; j < 2; ++j)
    {
      if (!myDS->HasFaceInfo(nF[j]))
        continue;

      if (!aMFence.Add(nF[j]))
        continue;

      aFIVec.Appended() = nF[j];
    }
  }

  std::sort(aFIVec.begin(), aFIVec.end());

  NCollection_IndexedDataMap<BOPTools_Set, NCollection_List<TopoDS_Shape>> anESetFaces(1,
                                                                                       aAllocator);

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFPlanar(1, aAllocator);

  int aNbF = aFIVec.Length();
  for (int i = 0; i < aNbF; ++i)
  {
    if (UserBreak(aPSOuter))
    {
      return;
    }
    const int              nF  = aFIVec(i);
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(nF);
    const TopoDS_Shape&    aF  = aSI.Shape();

    bool bCheckPlanar = false;
    {

      if (myContext->SurfaceAdaptor(TopoDS::Face(aF)).GetType() == GeomAbs_Plane)
      {

        const Bnd_Box& aBox = aSI.Box();
        bCheckPlanar        = !(aBox.IsOpenXmin() || aBox.IsOpenXmax() || aBox.IsOpenYmin()
                         || aBox.IsOpenYmax() || aBox.IsOpenZmin() || aBox.IsOpenZmax());
      }
    }

    const NCollection_List<TopoDS_Shape>* pLFSp = myImages.Seek(aF);
    if (pLFSp)
    {
      NCollection_List<TopoDS_Shape>::Iterator aItLF(*pLFSp);
      for (; aItLF.More(); aItLF.Next())
      {
        AddEdgeSet(aItLF.Value(), anESetFaces, aAllocator);
        if (bCheckPlanar)
          aMFPlanar.Add(aItLF.Value());
      }
    }
    else
    {
      AddEdgeSet(aF, anESetFaces, aAllocator);
      if (bCheckPlanar)
        aMFPlanar.Add(aF);
    }
  }

  BOPAlgo_VectorOfPairOfShapeBoolean aVPSB;

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aDMSLS(1, aAllocator);

  int aNbSets = anESetFaces.Extent();
  for (int i = 1; i <= aNbSets; ++i)
  {
    if (UserBreak(aPSOuter))
    {
      return;
    }
    const NCollection_List<TopoDS_Shape>& aLF = anESetFaces(i);
    if (aLF.Extent() < 2)
      continue;

    NCollection_List<TopoDS_Shape>::Iterator aIt1(aLF);
    for (; aIt1.More(); aIt1.Next())
    {
      const TopoDS_Shape& aF1          = aIt1.Value();
      bool                bCheckPlanar = aMFPlanar.Contains(aF1);

      NCollection_List<TopoDS_Shape>::Iterator aIt2 = aIt1;
      for (aIt2.Next(); aIt2.More(); aIt2.Next())
      {
        const TopoDS_Shape& aF2 = aIt2.Value();
        if (bCheckPlanar && aMFPlanar.Contains(aF2))
        {

          BOPAlgo_Tools::FillMap(aF1, aF2, aDMSLS, aAllocator);
          continue;
        }

        BOPAlgo_PairOfShapeBoolean& aPSB = aVPSB.Appended();
        aPSB.Shape1()                    = aF1;
        aPSB.Shape2()                    = aF2;
        aPSB.SetFuzzyValue(myFuzzyValue);
      }
    }
  }

  aPSOuter.Next();

  Message_ProgressScope aPSParallel(aPSOuter.Next(6), "Checking SD faces", aVPSB.Size());
  for (int iPSB = 0; iPSB < aVPSB.Size(); ++iPSB)
  {
    aVPSB.ChangeValue(iPSB).SetProgressRange(aPSParallel.Next());
  }

  BOPTools_Parallel::Perform(myRunParallel, aVPSB, myContext);

  if (UserBreak(aPSOuter))
  {
    return;
  }

  NCollection_List<NCollection_List<TopoDS_Shape>> aMBlocks(aAllocator);

  int aNbPairs = aVPSB.Length();
  for (int i = 0; i < aNbPairs; ++i)
  {
    BOPAlgo_PairOfShapeBoolean& aPSB = aVPSB(i);
    if (aPSB.Flag())
      BOPAlgo_Tools::FillMap(aPSB.Shape1(), aPSB.Shape2(), aDMSLS, aAllocator);
  }
  aVPSB.Clear();

  BOPAlgo_Tools::MakeBlocks(aDMSLS, aMBlocks, aAllocator);

  Message_ProgressScope aPS(aPSOuter.Next(3), "Filling same domain faces map", aMBlocks.Size());

  NCollection_List<NCollection_List<TopoDS_Shape>>::Iterator aItB(aMBlocks);
  for (; aItB.More(); aItB.Next(), aPS.Next())
  {
    if (UserBreak(aPS))
    {
      return;
    }
    const NCollection_List<TopoDS_Shape>& aLSD = aItB.Value();

    TopoDS_Face*                             pFSD  = nullptr;
    int                                      nFMin = ::IntegerLast();
    NCollection_List<TopoDS_Shape>::Iterator aItLF(aLSD);
    for (; aItLF.More(); aItLF.Next())
    {
      const TopoDS_Shape& aF = aItLF.Value();

      const int nF = myDS->Index(aF);
      if (nF >= 0)
      {

        myImages.Bound(aF, NCollection_List<TopoDS_Shape>())->Append(aF);

        if (nF < nFMin)
        {
          nFMin = nF;
          pFSD  = (TopoDS_Face*)&aF;
        }
      }
    }

    if (!pFSD)
    {

      pFSD = (TopoDS_Face*)&aLSD.First();
    }

    aItLF.Initialize(aLSD);
    for (; aItLF.More(); aItLF.Next())
    {
      const TopoDS_Shape& aF = aItLF.Value();
      myShapesSD.Bind(aF, *pFSD);
    }
  }

  int aNbS = myDS->NbSourceShapes();
  for (int i = 0; i < aNbS; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (aSI.ShapeType() != TopAbs_FACE)
      continue;

    const TopoDS_Shape&             aF    = aSI.Shape();
    NCollection_List<TopoDS_Shape>* pLFIm = myImages.ChangeSeek(aF);
    if (!pLFIm)
      continue;

    NCollection_List<TopoDS_Shape>::Iterator aItLFIm(*pLFIm);
    for (; aItLFIm.More(); aItLFIm.Next())
    {
      TopoDS_Shape&       aFIm = aItLFIm.ChangeValue();
      const TopoDS_Shape* pFSD = myShapesSD.Seek(aFIm);
      if (pFSD)

        aFIm = *pFSD;

      NCollection_List<TopoDS_Shape>* pLFOr = myOrigins.ChangeSeek(aFIm);
      if (!pLFOr)
        pLFOr = myOrigins.Bound(aFIm, NCollection_List<TopoDS_Shape>());
      pLFOr->Append(aF);
    }
  }

  aMBlocks.Clear();
  aDMSLS.Clear();
}

void BOPAlgo_Builder::FillInternalVertices(const Message_ProgressRange& theRange)
{
  Message_ProgressScope aPSOuter(theRange, nullptr, 1);

  BOPAlgo_VectorOfVFI aVVFI;

  int aNbS = myDS->NbSourceShapes();
  for (int i = 0; i < aNbS; ++i)
  {
    const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(i);
    if (aSI.ShapeType() != TopAbs_FACE)
      continue;

    if (UserBreak(aPSOuter))
    {
      return;
    }

    const TopoDS_Shape&                   aF    = aSI.Shape();
    const NCollection_List<TopoDS_Shape>* pLFIm = myImages.Seek(aF);
    if (!pLFIm)
      continue;

    NCollection_List<int> aLIAV;
    myDS->AloneVertices(i, aLIAV);

    NCollection_List<int>::Iterator aItLV(aLIAV);
    for (; aItLV.More(); aItLV.Next())
    {
      TopoDS_Vertex aV = TopoDS::Vertex(myDS->Shape(aItLV.Value()));
      aV.Orientation(TopAbs_INTERNAL);

      NCollection_List<TopoDS_Shape>::Iterator aItLFIm(*pLFIm);
      for (; aItLFIm.More(); aItLFIm.Next())
      {
        const TopoDS_Face& aFIm = TopoDS::Face(aItLFIm.Value());

        BOPAlgo_VFI& aVFI = aVVFI.Appended();
        aVFI.SetVertex(aV);
        aVFI.SetFace(aFIm);
        aVFI.SetFuzzyValue(myFuzzyValue);
      }
    }
  }

  Message_ProgressScope aPSParallel(aPSOuter.Next(), "Looking for internal shapes", aVVFI.Size());
  for (int iVFI = 0; iVFI < aVVFI.Size(); ++iVFI)
  {
    aVVFI.ChangeValue(iVFI).SetProgressRange(aPSParallel.Next());
  }

  BOPTools_Parallel::Perform(myRunParallel, aVVFI, myContext);

  if (UserBreak(aPSOuter))
  {
    return;
  }

  int aNbVFI = aVVFI.Length();
  for (int i = 0; i < aNbVFI; ++i)
  {
    BOPAlgo_VFI& aVFI = aVVFI(i);
    if (aVFI.IsInternal())
    {
      TopoDS_Vertex& aV = aVFI.Vertex();
      TopoDS_Face&   aF = aVFI.Face();
      BRep_Builder().Add(aF, aV);
    }
  }
}

static bool HasMultiConnected(
  const TopoDS_Edge& theEdge,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    theMap)
{
  TopoDS_Iterator itV(theEdge);
  for (; itV.More(); itV.Next())
  {
    const TopoDS_Shape&             aV    = itV.Value();
    NCollection_List<TopoDS_Shape>* pList = theMap.ChangeSeek(aV);
    if (!pList)
    {
      pList = theMap.Bound(aV, NCollection_List<TopoDS_Shape>());
      pList->Append(theEdge);
    }
    else
    {

      if (!pList->Contains(theEdge))
        pList->Append(theEdge);

      if (pList->Extent() > 2)
        return true;
    }
  }
  return false;
}

TopoDS_Face BuildDraftFace(
  const TopoDS_Face& theFace,
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                     theImages,
  occ::handle<IntTools_Context>&     theCtx,
  const occ::handle<Message_Report>& theReport)
{
  BRep_Builder aBB;

  TopLoc_Location                  aLoc;
  const occ::handle<Geom_Surface>& aS   = BRep_Tool::Surface(theFace, aLoc);
  const double                     aTol = BRep_Tool::Tolerance(theFace);

  TopoDS_Face aDraftFace;
  aBB.MakeFace(aDraftFace, aS, aLoc, aTol);

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aVerticesCounter;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMEdges;

  TopoDS_Iterator aItW(theFace.Oriented(TopAbs_FORWARD));
  for (; aItW.More(); aItW.Next())
  {
    const TopoDS_Shape& aW = aItW.Value();
    if (aW.ShapeType() != TopAbs_WIRE)
      continue;

    TopoDS_Iterator aItE(aW.Oriented(TopAbs_FORWARD));
    if (!aItE.More())
      continue;

    TopoDS_Wire aNewWire;
    aBB.MakeWire(aNewWire);

    for (; aItE.More(); aItE.Next())
    {
      const TopoDS_Edge& aE = TopoDS::Edge(aItE.Value());

      TopAbs_Orientation anOriE = aE.Orientation();
      if (anOriE == TopAbs_INTERNAL)
      {

        return TopoDS_Face();
      }

      bool bIsDegenerated = BRep_Tool::Degenerated(aE);

      bool bIsClosed = BRep_Tool::IsClosed(aE, theFace);

      const NCollection_List<TopoDS_Shape>* pLEIm = theImages.Seek(aE);
      if (!pLEIm)
      {

        if (!bIsDegenerated && HasMultiConnected(aE, aVerticesCounter))
          return TopoDS_Face();

        if (!bIsClosed && !aMEdges.Add(aE))
          return TopoDS_Face();

        aBB.Add(aNewWire, aE);
        continue;
      }

      NCollection_List<TopoDS_Shape>::Iterator aItLEIm(*pLEIm);
      for (; aItLEIm.More(); aItLEIm.Next())
      {
        TopoDS_Edge& aSp = TopoDS::Edge(aItLEIm.ChangeValue());

        if (!bIsDegenerated && HasMultiConnected(aSp, aVerticesCounter))
          return TopoDS_Face();

        if (!bIsClosed && !aMEdges.Add(aSp))
          return TopoDS_Face();

        aSp.Orientation(anOriE);
        if (bIsDegenerated)
        {
          aBB.Add(aNewWire, aSp);
          continue;
        }

        if (bIsClosed && !BRep_Tool::IsClosed(aSp, theFace))
          BOPTools_AlgoTools3D::DoSplitSEAMOnFace(aSp, theFace);

        if (BOPTools_AlgoTools::IsSplitToReverseWithWarn(aSp, aE, theCtx, theReport))
          aSp.Reverse();

        aBB.Add(aNewWire, aSp);
      }
    }

    aNewWire.Orientation(aW.Orientation());
    aNewWire.Closed(BRep_Tool::IsClosed(aNewWire));
    aBB.Add(aDraftFace, aNewWire);
  }

  if (theFace.Orientation() == TopAbs_REVERSED)
    aDraftFace.Reverse();

  return aDraftFace;
}
