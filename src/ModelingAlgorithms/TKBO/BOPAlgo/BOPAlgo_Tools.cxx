#include <BOPAlgo_Tools.hpp>

#include <BOPAlgo_Builder.hpp>
#include <BOPAlgo_BuilderFace.hpp>
#include <NCollection_DataMap.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <Standard_Handle.hpp>
#include <BOPDS_DS.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BOPTools_BoxTree.hpp>
#include <BOPTools_Parallel.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepBndLib.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepLib.hpp>
#include <Bnd_Tools.hpp>
#include <GeomAPI_ProjectPointOnCurve.hpp>
#include <GeomAPI_ProjectPointOnSurf.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Parab.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <IntTools_Context.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_Vector.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Map.hpp>

#include <algorithm>
class BOPDS_PaveBlock;

typedef NCollection_IndexedDataMap<TopoDS_Shape, gp_Dir, TopTools_ShapeMapHasher>
  BOPAlgo_IndexedDataMapOfShapeDir;
typedef NCollection_IndexedDataMap<TopoDS_Shape, gp_Pln, TopTools_ShapeMapHasher>
  BOPAlgo_IndexedDataMapOfShapePln;

static void MakeWires(
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theEdges,
  TopoDS_Compound&                                                     theWires,
  const bool                                                           theCheckUniquePlane,
  BOPAlgo_IndexedDataMapOfShapeDir&                                    theDMEdgeTgt,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&              theMEdgesNoUniquePlane);

static bool FindPlane(const BRepAdaptor_Curve& theCurve, gp_Pln& thePlane);

static bool FindPlane(
  const TopoDS_Shape&                                     theWire,
  gp_Pln&                                                 thePlane,
  BOPAlgo_IndexedDataMapOfShapeDir&                       theDMEdgeTgt,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMEdgesNoUniquePlane);

static bool FindEdgeTangent(const TopoDS_Edge&                theEdge,
                            BOPAlgo_IndexedDataMapOfShapeDir& theDMEdgeTgt,
                            gp_Dir&                           theTgt);

static bool FindEdgeTangent(const BRepAdaptor_Curve& theCurve, gp_Vec& theTangent);

void BOPAlgo_Tools::FillMap(
  const occ::handle<BOPDS_PaveBlock>&                                              aPB,
  const int                                                                        nF,
  NCollection_IndexedDataMap<occ::handle<BOPDS_PaveBlock>, NCollection_List<int>>& aMPBLI,
  const occ::handle<NCollection_BaseAllocator>&                                    aAllocator)
{
  NCollection_List<int>* pLI = aMPBLI.ChangeSeek(aPB);
  if (!pLI)
  {
    pLI = &aMPBLI(aMPBLI.Add(aPB, NCollection_List<int>(aAllocator)));
  }
  pLI->Append(nF);
}

void BOPAlgo_Tools::PerformCommonBlocks(
  NCollection_IndexedDataMap<occ::handle<BOPDS_PaveBlock>,
                             NCollection_List<occ::handle<BOPDS_PaveBlock>>>& aMPBLPB,
  const occ::handle<NCollection_BaseAllocator>&                               aAllocator,
  BOPDS_PDS&                                                                  pDS,
  const occ::handle<IntTools_Context>&                                        theContext)
{
  int aNbCB;

  aNbCB = aMPBLPB.Extent();
  if (!aNbCB)
  {
    return;
  }

  NCollection_List<NCollection_List<occ::handle<BOPDS_PaveBlock>>> aMBlocks(aAllocator);
  BOPAlgo_Tools::MakeBlocks(aMPBLPB, aMBlocks, aAllocator);

  occ::handle<NCollection_IncAllocator> anAllocTmp = new NCollection_IncAllocator;
  NCollection_Map<int>                  aMFaces(1, anAllocTmp);

  NCollection_List<NCollection_List<occ::handle<BOPDS_PaveBlock>>>::Iterator aItB(aMBlocks);
  for (; aItB.More(); aItB.Next())
  {
    const NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB  = aItB.Value();
    int                                                   aNbPB = aLPB.Extent();
    if (aNbPB < 2)
      continue;

    aMFaces.Clear();
    anAllocTmp->Reset(false);

    occ::handle<BOPDS_CommonBlock> aCB;

    NCollection_List<int> aLFaces;

    NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItLPB(aLPB);
    for (; aItLPB.More(); aItLPB.Next())
    {
      const occ::handle<BOPDS_PaveBlock>& aPB = aItLPB.Value();
      if (pDS->IsCommonBlock(aPB))
      {
        const occ::handle<BOPDS_CommonBlock>& aCBx = pDS->CommonBlock(aPB);

        NCollection_List<int>::Iterator aItLF(aCBx->Faces());
        for (; aItLF.More(); aItLF.Next())
        {
          const int nF = aItLF.Value();

          if (aMFaces.Add(nF))
            aLFaces.Append(nF);
        }
        if (aCB.IsNull())
          aCB = aCBx;
      }
    }

    if (aCB.IsNull())
      aCB = new BOPDS_CommonBlock;

    aCB->SetPaveBlocks(aLPB);
    aCB->SetFaces(aLFaces);
    for (aItLPB.Initialize(aLPB); aItLPB.More(); aItLPB.Next())
      pDS->SetCommonBlock(aItLPB.Value(), aCB);

    double aTolCB = BOPAlgo_Tools::ComputeToleranceOfCB(aCB, pDS, theContext);
    aCB->SetTolerance(aTolCB);
  }
}

void BOPAlgo_Tools::PerformCommonBlocks(
  const NCollection_IndexedDataMap<occ::handle<BOPDS_PaveBlock>, NCollection_List<int>>& aMPBLI,
  const occ::handle<NCollection_BaseAllocator>&,
  BOPDS_PDS&                           pDS,
  const occ::handle<IntTools_Context>& theContext)
{
  int                             nF, i, aNb;
  NCollection_List<int>::Iterator aItLI;
  occ::handle<BOPDS_PaveBlock>    aPB;
  occ::handle<BOPDS_CommonBlock>  aCB;

  aNb = aMPBLI.Extent();
  for (i = 1; i <= aNb; ++i)
  {
    aPB = aMPBLI.FindKey(i);
    if (pDS->IsCommonBlock(aPB))
    {
      aCB = pDS->CommonBlock(aPB);
    }
    else
    {
      aCB = new BOPDS_CommonBlock;
      aCB->AddPaveBlock(aPB);
    }

    const NCollection_List<int>& aLI = aMPBLI.FindFromKey(aPB);
    NCollection_List<int>        aNewFaces;
    const NCollection_List<int>& anOldFaces = aCB->Faces();
    aItLI.Initialize(aLI);
    for (; aItLI.More(); aItLI.Next())
    {
      nF = aItLI.Value();

      NCollection_List<int>::Iterator it(anOldFaces);
      for (; it.More(); it.Next())
      {
        if (it.Value() == nF)
          break;
      }
      if (!it.More())
      {
        aNewFaces.Append(nF);
      }
    }
    aCB->AppendFaces(aNewFaces);
    pDS->SetCommonBlock(aPB, aCB);

    double aTolCB = BOPAlgo_Tools::ComputeToleranceOfCB(aCB, pDS, theContext);
    aCB->SetTolerance(aTolCB);
  }
}

double BOPAlgo_Tools::ComputeToleranceOfCB(const occ::handle<BOPDS_CommonBlock>& theCB,
                                           const BOPDS_PDS                       theDS,
                                           const occ::handle<IntTools_Context>&  theContext)
{
  double aTolMax = 0.;
  if (theCB.IsNull())
  {
    return aTolMax;
  }

  const occ::handle<BOPDS_PaveBlock>& aPBR = theCB->PaveBlock1();
  int                                 nE   = aPBR->OriginalEdge();
  const TopoDS_Edge&                  aEOr = *(TopoDS_Edge*)&theDS->Shape(nE);
  aTolMax                                  = BRep_Tool::Tolerance(aEOr);

  const NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB = theCB->PaveBlocks();
  const NCollection_List<int>&                          aLFI = theCB->Faces();

  if ((aLPB.Extent() < 2) && aLFI.IsEmpty())
  {
    return aTolMax;
  }

  const int aNbPnt = 11;
  double    aTol, aT, aT1, aT2, aDt;
  gp_Pnt    aP;

  const occ::handle<Geom_Curve>& aC3D = BRep_Tool::Curve(aEOr, aT1, aT2);

  aPBR->Range(aT1, aT2);
  aDt = (aT2 - aT1) / (aNbPnt + 1);

  occ::handle<IntTools_Context> aCtx = theContext;
  if (aCtx.IsNull())
    aCtx = new IntTools_Context();

  if (aLPB.Extent() > 1)
  {

    NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItPB;
    GeomAPI_ProjectPointOnCurve                              aProjPC;

    aItPB.Initialize(aLPB);
    for (; aItPB.More(); aItPB.Next())
    {
      const occ::handle<BOPDS_PaveBlock>& aPB = aItPB.Value();
      if (aPB == aPBR)
      {
        continue;
      }

      nE                    = aPB->OriginalEdge();
      const TopoDS_Edge& aE = *(TopoDS_Edge*)&theDS->Shape(nE);
      aTol                  = BRep_Tool::Tolerance(aE);

      aProjPC = aCtx->ProjPC(aE);

      aT = aT1;
      for (int i = 1; i <= aNbPnt; i++)
      {
        aT += aDt;
        aC3D->D0(aT, aP);
        aProjPC.Perform(aP);
        if (aProjPC.NbPoints())
        {
          double aTolNew = aTol + aProjPC.LowerDistance();
          if (aTolNew > aTolMax)
          {
            aTolMax = aTolNew;
          }
        }
      }
    }
  }

  if (aLFI.Extent())
  {
    for (NCollection_List<int>::Iterator aItLI(aLFI); aItLI.More(); aItLI.Next())
    {
      const int          nF = aItLI.Value();
      const TopoDS_Face& aF = *(TopoDS_Face*)&theDS->Shape(nF);
      aTol                  = BRep_Tool::Tolerance(aF);

      GeomAPI_ProjectPointOnSurf& aProjPS = aCtx->ProjPS(aF);

      aT = aT1;
      for (int i = 1; i <= aNbPnt; i++)
      {
        aT += aDt;
        aC3D->D0(aT, aP);
        aProjPS.Perform(aP);
        if (aProjPS.NbPoints())
        {
          double aTolNew = aTol + aProjPS.LowerDistance();
          if (aTolNew > aTolMax)
          {
            aTolMax = aTolNew;
          }
        }
      }
    }
  }

  return aTolMax;
}

int BOPAlgo_Tools::EdgesToWires(const TopoDS_Shape& theEdges,
                                TopoDS_Shape&       theWires,
                                const bool          theShared,
                                const double        theAngTol)
{
  int iErr = 0;

  NCollection_List<TopoDS_Shape> aLE;

  TopExp_Explorer aExp(theEdges, TopAbs_EDGE);
  for (; aExp.More(); aExp.Next())
  {
    const TopoDS_Edge& aE = TopoDS::Edge(aExp.Current());
    if (!BRep_Tool::Degenerated(aE) && BRep_Tool::IsGeometric(aE))
    {
      aLE.Append(aExp.Current());
    }
  }

  if (aLE.IsEmpty())
  {

    iErr = 1;
    return iErr;
  }

  BRep_Builder    aBB;
  TopoDS_Compound aRWires;
  aBB.MakeCompound(aRWires);

  if (aLE.Extent() == 1)
  {
    TopoDS_Wire aWire;
    aBB.MakeWire(aWire);
    aBB.Add(aWire, aLE.First());
    aBB.Add(aRWires, aWire);
    theWires = aRWires;
    return iErr;
  }

  TopoDS_Shape aSEdges;

  if (!theShared)
  {

    BOPAlgo_Builder aGF;
    aGF.SetArguments(aLE);
    aGF.Perform();
    if (aGF.HasErrors())
    {

      iErr = 2;
      return iErr;
    }

    aSEdges = aGF.Shape();
  }
  else
  {
    aBB.MakeCompound(TopoDS::Compound(aSEdges));
    NCollection_List<TopoDS_Shape>::Iterator aItLE(aLE);
    for (; aItLE.More(); aItLE.Next())
    {
      aBB.Add(aSEdges, aItLE.Value());
    }
  }

  BOPAlgo_IndexedDataMapOfShapePln aDMEdgePln;

  BOPAlgo_IndexedDataMapOfShapeDir aDMEdgeTgt;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMEdgesNoUniquePlane;

  TopoDS_Compound aLEdges;
  aBB.MakeCompound(aLEdges);

  aExp.Init(aSEdges, TopAbs_EDGE);
  for (; aExp.More(); aExp.Next())
  {
    const TopoDS_Edge& aE = TopoDS::Edge(aExp.Current());
    BRepAdaptor_Curve  aBAC(aE);

    gp_Pln aPln;
    if (FindPlane(aBAC, aPln))
    {
      aDMEdgePln.Add(aE, aPln);
    }
    else
    {
      gp_Vec aVT;
      if (FindEdgeTangent(aBAC, aVT))
      {
        aDMEdgeTgt.Add(aE, gp_Dir(aVT));
        aBB.Add(aLEdges, aE);
        aMEdgesNoUniquePlane.Add(aE);
      }
    }
  }

  typedef NCollection_List<gp_Dir> BOPAlgo_ListOfDir;

  BOPAlgo_ListOfDir aLPFence;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMEFence;

  int i, j, aNbPlanes = aDMEdgePln.Extent(), aNbEdges = aDMEdgeTgt.Extent();
  for (i = 1; i <= aNbPlanes; ++i)
  {
    const TopoDS_Shape& aEI = aDMEdgePln.FindKey(i);
    if (!aMEFence.Add(aEI))
    {
      continue;
    }

    const gp_Pln& aPlnI = aDMEdgePln(i);
    const gp_Dir& aDI   = aPlnI.Position().Direction();

    aLPFence.Append(aDI);

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMEPln;
    aMEPln.Add(aEI);

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMV;
    TopExp::MapShapes(aEI, TopAbs_VERTEX, aMV);

    for (j = i + 1; j <= aNbPlanes; ++j)
    {
      const gp_Dir& aDJ = aDMEdgePln(j).Position().Direction();
      if (aDI.IsParallel(aDJ, theAngTol))
      {
        const TopoDS_Shape& aEJ = aDMEdgePln.FindKey(j);
        aMEPln.Add(aEJ);
        aMEFence.Add(aEJ);
        TopExp::MapShapes(aEJ, TopAbs_VERTEX, aMV);
      }
    }

    TopoDS_Compound aCEPln;
    aBB.MakeCompound(aCEPln);

    for (j = 1; j <= aNbEdges; ++j)
    {
      const gp_Dir& aDJ = aDMEdgeTgt(j);
      if (aDI.IsNormal(aDJ, theAngTol))
      {
        aBB.Add(aCEPln, aDMEdgeTgt.FindKey(j));
      }
    }

    NCollection_List<TopoDS_Shape> aLCBE;
    BOPTools_AlgoTools::MakeConnexityBlocks(aCEPln, TopAbs_VERTEX, TopAbs_EDGE, aLCBE);

    NCollection_List<TopoDS_Shape>::Iterator aItLCB(aLCBE);
    for (; aItLCB.More(); aItLCB.Next())
    {
      const TopoDS_Shape& aCBE = aItLCB.Value();

      TopExp_Explorer aExpV(aCBE, TopAbs_VERTEX);
      for (; aExpV.More(); aExpV.Next())
      {
        if (aMV.Contains(aExpV.Current()))
        {
          break;
        }
      }

      bool bAddBlock = aExpV.More();
      if (!bAddBlock)
      {

        gp_Pln aPln;
        bAddBlock = FindPlane(aCBE, aPln, aDMEdgeTgt, aMEdgesNoUniquePlane);
      }

      if (bAddBlock)
      {

        for (TopoDS_Iterator aItE(aCBE); aItE.More(); aItE.Next())
        {
          aMEPln.Add(aItE.Value());
        }
      }
    }

    MakeWires(aMEPln, aRWires, false, aDMEdgeTgt, aMEdgesNoUniquePlane);
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aDMVE;
  TopExp::MapShapesAndAncestors(aLEdges, TopAbs_VERTEX, TopAbs_EDGE, aDMVE);

  int aNbV = aDMVE.Extent();
  for (i = 1; i <= aNbV; ++i)
  {
    const NCollection_List<TopoDS_Shape>& aLEI = aDMVE(i);
    if (aLEI.Extent() < 2)
    {
      continue;
    }

    NCollection_List<TopoDS_Shape>::Iterator aItLEI1(aLEI);
    for (; aItLEI1.More(); aItLEI1.Next())
    {
      const TopoDS_Shape& aEI1 = aItLEI1.Value();
      const gp_Dir&       aDI1 = aDMEdgeTgt.FindFromKey(aEI1);

      NCollection_List<TopoDS_Shape>::Iterator aItLEI2(aLEI);
      for (; aItLEI2.More(); aItLEI2.Next())
      {
        const TopoDS_Shape& aEI2 = aItLEI2.Value();
        if (aEI2.IsSame(aEI1))
        {
          continue;
        }

        const gp_Dir& aDI2 = aDMEdgeTgt.FindFromKey(aEI2);

        if (aDI1.IsParallel(aDI2, theAngTol))
        {
          continue;
        }

        gp_Dir aDNI = aDI1 ^ aDI2;

        BOPAlgo_ListOfDir::Iterator aItLPln(aLPFence);
        for (; aItLPln.More(); aItLPln.Next())
        {
          if (aDNI.IsParallel(aItLPln.Value(), theAngTol))
          {
            break;
          }
        }
        if (aItLPln.More())
        {
          continue;
        }

        aLPFence.Append(aDNI);

        NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMEPln;
        aMEPln.Add(aEI1);
        aMEPln.Add(aEI2);

        for (j = 1; j <= aNbEdges; ++j)
        {
          const gp_Dir& aDJ = aDMEdgeTgt(j);
          if (aDNI.IsNormal(aDJ, theAngTol))
          {
            aMEPln.Add(aDMEdgeTgt.FindKey(j));
          }
        }

        MakeWires(aMEPln, aRWires, true, aDMEdgeTgt, aMEdgesNoUniquePlane);
      }
    }
  }

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMEAlone, aMEUsed;
  TopExp::MapShapes(aRWires, TopAbs_EDGE, aMEUsed);

  for (i = 1; i <= aNbEdges; ++i)
  {
    const TopoDS_Shape& aE = aDMEdgeTgt.FindKey(i);
    if (!aMEUsed.Contains(aE))
    {
      aMEAlone.Add(aE);
    }
  }

  MakeWires(aMEAlone, aRWires, false, aDMEdgeTgt, aMEdgesNoUniquePlane);

  theWires = aRWires;

  return iErr;
}

bool BOPAlgo_Tools::WiresToFaces(const TopoDS_Shape& theWires,
                                 TopoDS_Shape&       theFaces,
                                 const double        theAngTol)
{
  BRep_Builder                                           aBB;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFence;
  TopoDS_Compound                                        aRFaces;
  aBB.MakeCompound(aRFaces);

  const double aMax = 1.e+8;

  BOPAlgo_IndexedDataMapOfShapeDir aDMEdgeTgt;

  BOPAlgo_IndexedDataMapOfShapePln aDMWirePln;

  NCollection_DataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher> aDMWireTol;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMEdgesNoUniquePlane;

  TopExp_Explorer aExpW(theWires, TopAbs_WIRE);
  for (; aExpW.More(); aExpW.Next())
  {
    const TopoDS_Wire& aWire = TopoDS::Wire(aExpW.Current());
    gp_Pln             aPlane;
    if (FindPlane(aWire, aPlane, aDMEdgeTgt, aMEdgesNoUniquePlane))
    {
      aDMWirePln.Add(aWire, aPlane);

      aDMWireTol.Bind(aWire, BRep_Tool::MaxTolerance(aWire, TopAbs_EDGE));
    }
  }

  int i, j, aNb = aDMWirePln.Extent();
  for (i = 1; i <= aNb; ++i)
  {
    const TopoDS_Shape& aWireI = aDMWirePln.FindKey(i);
    if (aMFence.Contains(aWireI))
    {
      continue;
    }

    const gp_Pln& aPlnI = aDMWirePln(i);

    NCollection_List<TopoDS_Shape> aLW;
    aLW.Append(aWireI);
    aMFence.Add(aWireI);

    double aTolI = aDMWireTol.Find(aWireI);

    for (j = i + 1; j <= aNb; ++j)
    {
      const TopoDS_Shape& aWireJ = aDMWirePln.FindKey(j);
      if (aMFence.Contains(aWireJ))
      {
        continue;
      }

      const gp_Pln& aPlnJ = aDMWirePln(j);

      if (!aPlnI.Position().Direction().IsParallel(aPlnJ.Position().Direction(), theAngTol))
      {
        continue;
      }

      double aDist = aPlnI.Distance(aPlnJ.Location());
      double aTolJ = aDMWireTol.Find(aWireJ);
      if (aDist > (aTolI + aTolJ))
      {
        continue;
      }

      aLW.Append(aWireJ);
      aMFence.Add(aWireJ);
    }

    NCollection_List<TopoDS_Shape>           aLE;
    NCollection_List<TopoDS_Shape>::Iterator aItLW(aLW);
    for (; aItLW.More(); aItLW.Next())
    {
      TopoDS_Iterator aItE(aItLW.Value());
      for (; aItE.More(); aItE.Next())
      {
        aLE.Append(aItE.Value().Oriented(TopAbs_FORWARD));
        aLE.Append(aItE.Value().Oriented(TopAbs_REVERSED));
      }
    }

    TopoDS_Face aFF = BRepBuilderAPI_MakeFace(aPlnI, -aMax, aMax, -aMax, aMax).Face();
    aFF.Orientation(TopAbs_FORWARD);

    try
    {
      OCC_CATCH_SIGNALS

      BRepLib::BuildPCurveForEdgesOnPlane(aLE, aFF);

      BOPAlgo_BuilderFace aBF;
      aBF.SetShapes(aLE);
      aBF.SetFace(aFF);
      aBF.Perform();
      if (aBF.HasErrors())
      {
        continue;
      }

      const NCollection_List<TopoDS_Shape>&    aLFSp = aBF.Areas();
      NCollection_List<TopoDS_Shape>::Iterator aItLF(aLFSp);
      for (; aItLF.More(); aItLF.Next())
      {
        const TopoDS_Shape& aFSp = aItLF.ChangeValue();
        aBB.Add(aRFaces, aFSp);
      }
    }
    catch (Standard_Failure const&)
    {
      continue;
    }
  }

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMEmpty;
  BOPTools_AlgoTools::CorrectTolerances(aRFaces, aMEmpty, 0.05, false);
  BOPTools_AlgoTools::CorrectShapeTolerances(aRFaces, aMEmpty, false);

  theFaces = aRFaces;
  return theFaces.NbChildren() > 0;
}

void MakeWires(const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theEdges,
               TopoDS_Compound&                                                     theWires,
               const bool                                              theCheckUniquePlane,
               BOPAlgo_IndexedDataMapOfShapeDir&                       theDMEdgeTgt,
               NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMEdgesNoUniquePlane)
{
  TopoDS_Compound aCE;
  BRep_Builder().MakeCompound(aCE);
  int i, aNbE = theEdges.Extent();
  for (i = 1; i <= aNbE; ++i)
  {
    BRep_Builder().Add(aCE, theEdges(i));
  }

  NCollection_List<TopoDS_Shape> aLCBE;
  BOPTools_AlgoTools::MakeConnexityBlocks(aCE, TopAbs_VERTEX, TopAbs_EDGE, aLCBE);

  NCollection_List<TopoDS_Shape>::Iterator aItLCB(aLCBE);
  for (; aItLCB.More(); aItLCB.Next())
  {
    const TopoDS_Shape& aCBE = aItLCB.Value();

    if (theCheckUniquePlane)
    {
      gp_Pln aPln;
      if (!FindPlane(aCBE, aPln, theDMEdgeTgt, theMEdgesNoUniquePlane))
      {
        continue;
      }
    }

    TopoDS_Wire aWire;
    BRep_Builder().MakeWire(aWire);
    for (TopoDS_Iterator aItE(aCBE); aItE.More(); aItE.Next())
    {
      BRep_Builder().Add(aWire, aItE.Value());
    }

    BRep_Builder().Add(theWires, aWire);
  }
}

bool FindEdgeTangent(const TopoDS_Edge&                theEdge,
                     BOPAlgo_IndexedDataMapOfShapeDir& theDMEdgeTgt,
                     gp_Dir&                           theTgt)
{
  gp_Dir* pDTE = theDMEdgeTgt.ChangeSeek(theEdge);
  if (!pDTE)
  {
    gp_Vec            aVTE;
    BRepAdaptor_Curve aBAC(theEdge);
    if (!FindEdgeTangent(aBAC, aVTE))
    {
      return false;
    }
    pDTE = &theDMEdgeTgt(theDMEdgeTgt.Add(theEdge, gp_Dir(aVTE)));
  }
  theTgt = *pDTE;
  return true;
}

bool FindEdgeTangent(const BRepAdaptor_Curve& theCurve, gp_Vec& theTangent)
{
  if (!theCurve.Is3DCurve())
  {
    return false;
  }

  if (theCurve.GetType() == GeomAbs_Line)
  {
    theTangent = theCurve.Line().Position().Direction();
    return true;
  }

  double       aT, aT1(theCurve.FirstParameter()), aT2(theCurve.LastParameter());
  const int    aNbP = 11;
  const double aDt  = (aT2 - aT1) / aNbP;

  for (aT = aT1 + aDt; aT <= aT2; aT += aDt)
  {
    gp_Pnt aP;
    theCurve.D1(aT, aP, theTangent);
    if (theTangent.Magnitude() > Precision::Confusion())
    {
      return true;
    }
  }

  return false;
}

bool FindPlane(const BRepAdaptor_Curve& theCurve, gp_Pln& thePlane)
{
  if (!theCurve.Is3DCurve())
  {
    return false;
  }

  bool   bFound = true;
  gp_Vec aVN;
  switch (theCurve.GetType())
  {
    case GeomAbs_Line:
      return false;
    case GeomAbs_Circle:
      aVN = theCurve.Circle().Position().Direction();
      break;
    case GeomAbs_Ellipse:
      aVN = theCurve.Ellipse().Position().Direction();
      break;
    case GeomAbs_Hyperbola:
      aVN = theCurve.Hyperbola().Position().Direction();
      break;
    case GeomAbs_Parabola:
      aVN = theCurve.Parabola().Position().Direction();
      break;
    default:
    {

      bFound = false;
      double       aT, aT1(theCurve.FirstParameter()), aT2(theCurve.LastParameter());
      const int    aNbP = 11;
      const double aDt  = (aT2 - aT1) / aNbP;

      aT = aT1;
      gp_Pnt aP1;
      gp_Vec aV1;
      theCurve.D1(aT, aP1, aV1);

      for (aT = aT1 + aDt; aT <= aT2; aT += aDt)
      {
        gp_Pnt aP2;
        gp_Vec aV2;
        theCurve.D1(aT, aP2, aV2);

        aVN = aV1 ^ aV2;
        if (aVN.Magnitude() > Precision::Confusion())
        {
          bFound = true;
          break;
        }
      }
      break;
    }
  }

  if (bFound)
  {
    thePlane = gp_Pln(theCurve.Value(theCurve.FirstParameter()), gp_Dir(aVN));
  }
  return bFound;
}

bool FindPlane(const TopoDS_Shape&                                     theWire,
               gp_Pln&                                                 thePlane,
               BOPAlgo_IndexedDataMapOfShapeDir&                       theDMEdgeTgt,
               NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMEdgesNoUniquePlane)
{
  TopExp_Explorer aExpE1(theWire, TopAbs_EDGE);
  if (!aExpE1.More())
  {
    return false;
  }

  for (; aExpE1.More(); aExpE1.Next())
  {

    const TopoDS_Edge& aE1 = TopoDS::Edge(aExpE1.Current());

    gp_Dir aDTE1;
    if (!FindEdgeTangent(aE1, theDMEdgeTgt, aDTE1))
    {
      continue;
    }

    TopExp_Explorer aExpE2(theWire, TopAbs_EDGE);
    for (; aExpE2.More(); aExpE2.Next())
    {
      const TopoDS_Edge& aE2 = TopoDS::Edge(aExpE2.Current());
      if (aE1.IsSame(aE2))
      {
        continue;
      }

      gp_Dir aDTE2;
      if (!FindEdgeTangent(aE2, theDMEdgeTgt, aDTE2))
      {
        continue;
      }

      if (aDTE1.IsParallel(aDTE2, Precision::Angular()))
      {
        continue;
      }

      gp_Dir aDN = aDTE1 ^ aDTE2;

      TopoDS_Iterator aItV(aE1);
      thePlane = gp_Pln(BRep_Tool::Pnt(TopoDS::Vertex(aItV.Value())), aDN);
      return true;
    }
  }

  aExpE1.Init(theWire, TopAbs_EDGE);
  for (; aExpE1.More(); aExpE1.Next())
  {
    const TopoDS_Edge& aE = TopoDS::Edge(aExpE1.Current());
    if (theMEdgesNoUniquePlane.Contains(aE))
    {
      continue;
    }
    BRepAdaptor_Curve aBAC(aE);
    if (FindPlane(aBAC, thePlane))
    {
      return true;
    }
    theMEdgesNoUniquePlane.Add(aE);
  }
  return false;
}

class BOPAlgo_PairVerticesSelector : public BOPTools_BoxPairSelector
{
public:
  BOPAlgo_PairVerticesSelector()
      : myVertices(nullptr),
        myFuzzyValue(Precision::Confusion())
  {
  }

  void SetMapOfVerticesTolerances(
    const NCollection_IndexedDataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher>& theVertices)
  {
    myVertices = &theVertices;
  }

  void SetFuzzyValue(const double theFuzzyValue) { myFuzzyValue = theFuzzyValue; }

  bool Accept(const int theID1, const int theID2) override
  {
    if (!RejectElement(theID1, theID2))
    {
      const int            anID1  = this->myBVHSet1->Element(theID1);
      const TopoDS_Vertex& aV1    = TopoDS::Vertex(myVertices->FindKey(anID1));
      double               aTolV1 = BRep_Tool::Tolerance(aV1);
      if (aTolV1 < myVertices->FindFromIndex(anID1))
        aTolV1 = myVertices->FindFromIndex(anID1);
      gp_Pnt aP1 = BRep_Tool::Pnt(aV1);

      const int            anID2  = this->myBVHSet1->Element(theID2);
      const TopoDS_Vertex& aV2    = TopoDS::Vertex(myVertices->FindKey(anID2));
      double               aTolV2 = BRep_Tool::Tolerance(aV2);
      if (aTolV2 < myVertices->FindFromIndex(anID2))
        aTolV2 = myVertices->FindFromIndex(anID2);
      gp_Pnt aP2 = BRep_Tool::Pnt(aV2);

      double aTolSum2 = aTolV1 + aTolV2 + myFuzzyValue;
      aTolSum2 *= aTolSum2;

      double aD2 = aP1.SquareDistance(aP2);
      if (aD2 < aTolSum2)
      {
        myPairs.push_back(PairIDs(anID1, anID2));
        return true;
      }
    }
    return false;
  }

protected:
  const NCollection_IndexedDataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher>* myVertices;
  double                                                                           myFuzzyValue;
};

void BOPAlgo_Tools::IntersectVertices(
  const NCollection_IndexedDataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher>& theVertices,
  const double                                                                     theFuzzyValue,
  NCollection_List<NCollection_List<TopoDS_Shape>>&                                theChains)
{
  int aNbV = theVertices.Extent();
  if (aNbV <= 1)
  {
    if (aNbV == 1)
    {
      theChains.Append(NCollection_List<TopoDS_Shape>()).Append(theVertices.FindKey(1));
    }
    return;
  }

  double aTolAdd = theFuzzyValue / 2.;

  BOPTools_BoxTree aBBTree;
  aBBTree.SetSize(aNbV);

  for (int i = 1; i <= aNbV; ++i)
  {
    const TopoDS_Vertex& aV   = TopoDS::Vertex(theVertices.FindKey(i));
    double               aTol = BRep_Tool::Tolerance(aV);
    if (aTol < theVertices(i))
      aTol = theVertices(i);

    Bnd_Box aBox;
    aBox.Add(BRep_Tool::Pnt(aV));
    aBox.SetGap(aTol + aTolAdd);
    aBBTree.Add(i, Bnd_Tools::Bnd2BVH(aBox));
  }

  aBBTree.Build();

  BOPAlgo_PairVerticesSelector aPairSelector;
  aPairSelector.SetBVHSets(&aBBTree, &aBBTree);
  aPairSelector.SetSame(true);
  aPairSelector.SetMapOfVerticesTolerances(theVertices);
  aPairSelector.SetFuzzyValue(theFuzzyValue);
  aPairSelector.Select();

  const std::vector<BOPTools_BoxPairSelector::PairIDs>& aPairs   = aPairSelector.Pairs();
  const int                                             aNbPairs = static_cast<int>(aPairs.size());

  occ::handle<NCollection_IncAllocator>                  anAlloc = new NCollection_IncAllocator;
  NCollection_IndexedDataMap<int, NCollection_List<int>> aMILI(1, anAlloc);

  for (int iPair = 0; iPair < aNbPairs; ++iPair)
  {
    const BOPTools_BoxPairSelector::PairIDs& aPair = aPairs[iPair];
    BOPAlgo_Tools::FillMap(aPair.ID1, aPair.ID2, aMILI, anAlloc);
  }

  NCollection_List<NCollection_List<int>> aBlocks(anAlloc);
  BOPAlgo_Tools::MakeBlocks(aMILI, aBlocks, anAlloc);

  NCollection_List<NCollection_List<int>>::Iterator itLI(aBlocks);
  for (; itLI.More(); itLI.Next())
  {
    const NCollection_List<int>&    aLI    = itLI.Value();
    NCollection_List<TopoDS_Shape>& aChain = theChains.Append(NCollection_List<TopoDS_Shape>());

    for (NCollection_List<int>::Iterator itI(aLI); itI.More(); itI.Next())
      aChain.Append(theVertices.FindKey(itI.Value()));
  }

  for (int i = 1; i <= aNbV; ++i)
  {
    if (!aMILI.Contains(i))
    {
      NCollection_List<TopoDS_Shape>& aChain = theChains.Append(NCollection_List<TopoDS_Shape>());
      aChain.Append(theVertices.FindKey(i));
    }
  }
}

class BOPAlgo_ShapeBox
{
public:
  BOPAlgo_ShapeBox() = default;

  void SetShape(const TopoDS_Shape& theS) { myShape = theS; };

  const TopoDS_Shape& Shape() const { return myShape; };

  void SetBox(const Bnd_Box& theBox) { myBox = theBox; };

  const Bnd_Box& Box() const { return myBox; };

private:
  TopoDS_Shape myShape;
  Bnd_Box      myBox;
};

typedef NCollection_Vector<BOPAlgo_ShapeBox> BOPAlgo_VectorOfShapeBox;

class BOPAlgo_FillIn3DParts : public BOPAlgo_ParallelAlgo
{
public:
  DEFINE_STANDARD_ALLOC

  BOPAlgo_FillIn3DParts()
  {
    myBBTree    = nullptr;
    myVShapeBox = nullptr;
  };

  ~BOPAlgo_FillIn3DParts() override = default;

  void SetSolid(const TopoDS_Solid& theSolid) { mySolid = theSolid; };

  const TopoDS_Solid& Solid() const { return mySolid; };

  void SetBoxS(const Bnd_Box& theBox) { myBoxS = theBox; };

  const Bnd_Box& BoxS() const { return myBoxS; };

  void SetOwnIF(const NCollection_List<TopoDS_Shape>& theLIF) { myOwnIF = theLIF; };

  const NCollection_List<TopoDS_Shape>& OwnIF() const { return myOwnIF; };

  void SetBBTree(BOPTools_BoxTree* theBBTree) { myBBTree = theBBTree; };

  void SetShapeBoxVector(const BOPAlgo_VectorOfShapeBox& theShapeBox)
  {
    myVShapeBox = (BOPAlgo_VectorOfShapeBox*)&theShapeBox;
  };

  void SetContext(const occ::handle<IntTools_Context>& theContext) { myContext = theContext; }

  const occ::handle<IntTools_Context>& Context() const { return myContext; }

  void Perform() override;

  const NCollection_List<TopoDS_Shape>& InFaces() const { return myInFaces; };

private:
  void MapEdgesAndFaces(const TopoDS_Shape&                                  theF,
                        NCollection_IndexedDataMap<TopoDS_Shape,
                                                   NCollection_List<TopoDS_Shape>,
                                                   TopTools_ShapeMapHasher>& theEFMap,
                        const occ::handle<NCollection_BaseAllocator>&        theAlloc);

  void MakeConnexityBlock(
    const TopoDS_Face&                                                   theF,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMEToAvoid,
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>&           theEFMap,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&              theMFDone,
    NCollection_List<TopoDS_Shape>&                                      theLCB,
    TopoDS_Face&                                                         theFaceToClassify);

  TopoDS_Solid                   mySolid;
  Bnd_Box                        myBoxS;
  NCollection_List<TopoDS_Shape> myOwnIF;
  NCollection_List<TopoDS_Shape> myInFaces;

  BOPTools_BoxTree*         myBBTree;
  BOPAlgo_VectorOfShapeBox* myVShapeBox;

  TopoDS_Iterator myItF;
  TopoDS_Iterator myItW;

  occ::handle<IntTools_Context> myContext;
};

void BOPAlgo_FillIn3DParts::Perform()
{
  Message_ProgressScope aPSOuter(myProgressRange, nullptr, 2);
  if (UserBreak(aPSOuter))
  {
    return;
  }

  myInFaces.Clear();

  BOPTools_BoxTreeSelector aSelector;
  aSelector.SetBox(Bnd_Tools::Bnd2BVH(myBoxS));
  aSelector.SetBVHSet(myBBTree);

  if (!aSelector.Select())
    return;

  const NCollection_List<int>& aLIFP = aSelector.Indices();

  occ::handle<NCollection_BaseAllocator> anAlloc = new NCollection_IncAllocator;

  occ::handle<NCollection_IncAllocator> aTmpAlloc = new NCollection_IncAllocator;

  BOPAlgo_VectorOfShapeBox& aVShapeBox = *myVShapeBox;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMSE(1, anAlloc), aMSF(1, anAlloc);
  TopExp::MapShapes(mySolid, TopAbs_EDGE, aMSE);
  TopExp::MapShapes(mySolid, TopAbs_FACE, aMSF);

  bool bIsEmpty = aMSF.IsEmpty();

  NCollection_List<TopoDS_Shape>::Iterator aItLS(myOwnIF);
  for (; aItLS.More(); aItLS.Next())
    aMSF.Add(aItLS.Value());

  NCollection_Vector<int> aIVec(256, anAlloc);

  NCollection_List<int>::Iterator aItLI(aLIFP);
  for (; aItLI.More(); aItLI.Next())
  {
    int                 nFP = aItLI.Value();
    const TopoDS_Shape& aFP = aVShapeBox(nFP).Shape();
    if (!aMSF.Contains(aFP))
      aIVec.Appended() = nFP;
  }

  int k, aNbFP = aIVec.Length();

  if (aNbFP > 1)
    std::sort(aIVec.begin(), aIVec.end());

  if (bIsEmpty)
  {

    for (k = 0; k < aNbFP; ++k)
      myInFaces.Append(aVShapeBox(aIVec(k)).Shape());

    return;
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aMEFP(1, anAlloc);
  if (aNbFP > 1)
  {
    for (k = 0; k < aNbFP; ++k)
      MapEdgesAndFaces(aVShapeBox(aIVec(k)).Shape(), aMEFP, anAlloc);
  }

  aPSOuter.Next();

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aMEFDS(1, anAlloc);

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMFDone(1, anAlloc);

  NCollection_List<TopoDS_Shape> aLCBF(aTmpAlloc);

  Message_ProgressScope aPSLoop(aPSOuter.Next(), nullptr, aNbFP);
  for (k = 0; k < aNbFP; ++k, aPSLoop.Next())
  {
    if (UserBreak(aPSLoop))
    {
      return;
    }
    aLCBF.Clear();
    aTmpAlloc->Reset(false);

    int                nFP = aIVec(k);
    const TopoDS_Face& aFP = (*(TopoDS_Face*)&aVShapeBox(nFP).Shape());
    if (!aMFDone.Add(aFP))
      continue;

    TopoDS_Face aFaceToClassify;
    MakeConnexityBlock(aFP, aMSE, aMEFP, aMFDone, aLCBF, aFaceToClassify);

    if (!myBoxS.IsWhole())
    {

      bool bOut = false;
      aItLS.Initialize(aLCBF);
      for (; aItLS.More() && !bOut; aItLS.Next())
      {
        TopExp_Explorer anExpV(aItLS.Value(), TopAbs_VERTEX);
        for (; anExpV.More() && !bOut; anExpV.Next())
        {
          const TopoDS_Vertex& aV = TopoDS::Vertex(anExpV.Current());
          Bnd_Box              aBBV;
          aBBV.Add(BRep_Tool::Pnt(aV));
          aBBV.SetGap(BRep_Tool::Tolerance(aV));
          bOut = myBoxS.IsOut(aBBV);
        }
      }
      if (bOut)
        continue;
    }

    if (aFaceToClassify.IsNull())
      aFaceToClassify = aFP;

    if (aMEFDS.IsEmpty())

      TopExp::MapShapesAndAncestors(mySolid, TopAbs_EDGE, TopAbs_FACE, aMEFDS);

    bool bIsIN = BOPTools_AlgoTools::IsInternalFace(aFaceToClassify,
                                                    mySolid,
                                                    aMEFDS,
                                                    Precision::Confusion(),
                                                    myContext);
    if (bIsIN)
    {
      aItLS.Initialize(aLCBF);
      for (; aItLS.More(); aItLS.Next())
        myInFaces.Append(aItLS.Value());
    }
  }
}

void BOPAlgo_FillIn3DParts::MapEdgesAndFaces(
  const TopoDS_Shape& theF,
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                                theEFMap,
  const occ::handle<NCollection_BaseAllocator>& theAllocator)
{
  myItF.Initialize(theF);
  for (; myItF.More(); myItF.Next())
  {
    const TopoDS_Shape& aW = myItF.Value();
    if (aW.ShapeType() != TopAbs_WIRE)
      continue;

    myItW.Initialize(aW);
    for (; myItW.More(); myItW.Next())
    {
      const TopoDS_Shape& aE = myItW.Value();

      NCollection_List<TopoDS_Shape>* pLF = theEFMap.ChangeSeek(aE);
      if (!pLF)
        pLF = &theEFMap(theEFMap.Add(aE, NCollection_List<TopoDS_Shape>(theAllocator)));
      pLF->Append(theF);
    }
  }
}

void BOPAlgo_FillIn3DParts::MakeConnexityBlock(
  const TopoDS_Face&                                                   theFStart,
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMEAvoid,
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>&           theEFMap,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&              theMFDone,
  NCollection_List<TopoDS_Shape>&                                      theLCB,
  TopoDS_Face&                                                         theFaceToClassify)
{

  theLCB.Append(theFStart);
  if (theEFMap.IsEmpty())
    return;

  NCollection_List<TopoDS_Shape>::Iterator aItCB(theLCB);
  for (; aItCB.More(); aItCB.Next())
  {
    const TopoDS_Shape& aF = aItCB.Value();
    myItF.Initialize(aF);
    for (; myItF.More(); myItF.Next())
    {
      const TopoDS_Shape& aW = myItF.Value();
      if (aW.ShapeType() != TopAbs_WIRE)
        continue;

      myItW.Initialize(aW);
      for (; myItW.More(); myItW.Next())
      {
        const TopoDS_Edge& aE = TopoDS::Edge(myItW.Value());
        if (theMEAvoid.Contains(aE) || BRep_Tool::Degenerated(aE))
        {
          if (theFaceToClassify.IsNull())
            theFaceToClassify = TopoDS::Face(aF);
          continue;
        }

        const NCollection_List<TopoDS_Shape>* pLF = theEFMap.Seek(aE);
        if (!pLF)
          continue;
        NCollection_List<TopoDS_Shape>::Iterator aItLF(*pLF);
        for (; aItLF.More(); aItLF.Next())
        {
          const TopoDS_Shape& aFToAdd = aItLF.Value();
          if (theMFDone.Add(aFToAdd))
            theLCB.Append(aFToAdd);
        }
      }
    }
  }
}

typedef NCollection_Vector<BOPAlgo_FillIn3DParts> BOPAlgo_VectorOfFillIn3DParts;

void BOPAlgo_Tools::ClassifyFaces(
  const NCollection_List<TopoDS_Shape>& theFaces,
  const NCollection_List<TopoDS_Shape>& theSolids,
  const bool                            theRunParallel,
  occ::handle<IntTools_Context>&        theContext,
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                                                             theInParts,
  const NCollection_DataMap<TopoDS_Shape, Bnd_Box, TopTools_ShapeMapHasher>& theShapeBoxMap,
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                               theSolidsIF,
  const Message_ProgressRange& theRange)
{
  occ::handle<NCollection_BaseAllocator> anAlloc = new NCollection_IncAllocator;

  Message_ProgressScope aPSOuter(theRange, nullptr, 10);

  BOPAlgo_VectorOfShapeBox aVSB(256, anAlloc);

  NCollection_List<TopoDS_Shape>::Iterator aItLF(theFaces);
  for (; aItLF.More(); aItLF.Next())
  {
    if (!aPSOuter.More())
    {
      return;
    }

    const TopoDS_Shape& aF = aItLF.Value();

    BOPAlgo_ShapeBox& aSB = aVSB.Appended();
    aSB.SetShape(aF);

    const Bnd_Box* pBox = theShapeBoxMap.Seek(aF);
    if (pBox)
      aSB.SetBox(*pBox);
    else
    {

      Bnd_Box aBox;
      BRepBndLib::Add(aF, aBox);
      aSB.SetBox(aBox);
    }
  }

  BOPTools_BoxTree aBBTree;
  int              aNbF = aVSB.Length();
  aBBTree.SetSize(aNbF);
  for (int i = 0; i < aNbF; ++i)
  {
    aBBTree.Add(i, Bnd_Tools::Bnd2BVH(aVSB(i).Box()));
  }

  aBBTree.Build();

  BOPAlgo_VectorOfFillIn3DParts aVFIP;

  NCollection_List<TopoDS_Shape>::Iterator aItLS(theSolids);
  for (; aItLS.More(); aItLS.Next())
  {
    const TopoDS_Solid& aSolid = TopoDS::Solid(aItLS.Value());

    BOPAlgo_FillIn3DParts& aFIP = aVFIP.Appended();
    aFIP.SetSolid(aSolid);

    const Bnd_Box* pBox = theShapeBoxMap.Seek(aSolid);
    if (pBox)
      aFIP.SetBoxS(*pBox);
    else
    {

      Bnd_Box aBox;
      BRepBndLib::Add(aSolid, aBox);
      if (!aBox.IsWhole())
      {
        if (BOPTools_AlgoTools::IsInvertedSolid(aSolid))
          aBox.SetWhole();
      }
      aFIP.SetBoxS(aBox);
    }

    const NCollection_List<TopoDS_Shape>* pLIF = theSolidsIF.Seek(aSolid);
    if (pLIF)
      aFIP.SetOwnIF(*pLIF);

    aFIP.SetBBTree(&aBBTree);
    aFIP.SetShapeBoxVector(aVSB);
  }

  aPSOuter.Next();

  int                   aNbS = aVFIP.Length();
  Message_ProgressScope aPSParallel(aPSOuter.Next(9),
                                    "Classification of faces relatively solids",
                                    aNbS);
  for (int iFS = 0; iFS < aNbS; ++iFS)
  {
    aVFIP.ChangeValue(iFS).SetProgressRange(aPSParallel.Next());
  }

  BOPTools_Parallel::Perform(theRunParallel, aVFIP, theContext);

  for (int i = 0; i < aNbS; ++i)
  {
    BOPAlgo_FillIn3DParts&                aFIP  = aVFIP(i);
    const TopoDS_Shape&                   aS    = aFIP.Solid();
    const NCollection_List<TopoDS_Shape>& aLFIn = aFIP.InFaces();
    theInParts.Add(aS, aLFIn);
  }
}

void BOPAlgo_Tools::FillInternals(
  const NCollection_List<TopoDS_Shape>& theSolids,
  const NCollection_List<TopoDS_Shape>& theParts,
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                       theImages,
  const occ::handle<IntTools_Context>& theContext)
{
  if (theSolids.IsEmpty() || theParts.IsEmpty())
    return;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMSSolids;
  NCollection_List<TopoDS_Shape>::Iterator                      itLS(theSolids);
  for (; itLS.More(); itLS.Next())
  {
    const TopoDS_Shape& aSolid = itLS.Value();
    if (aSolid.ShapeType() == TopAbs_SOLID)
    {
      TopExp::MapShapes(aSolid, TopAbs_VERTEX, aMSSolids);
      TopExp::MapShapes(aSolid, TopAbs_EDGE, aMSSolids);
      TopExp::MapShapes(aSolid, TopAbs_FACE, aMSSolids);
    }
  }

  NCollection_List<TopoDS_Shape>           aLPartsInput = theParts, aLParts;
  NCollection_List<TopoDS_Shape>::Iterator itLP(aLPartsInput);
  for (; itLP.More(); itLP.Next())
  {
    const TopoDS_Shape& aPart = itLP.Value();
    switch (aPart.ShapeType())
    {
      case TopAbs_VERTEX:
      case TopAbs_EDGE:
      case TopAbs_FACE:
      {
        const NCollection_List<TopoDS_Shape>* pIm = theImages.Seek(aPart);
        if (pIm)
        {
          NCollection_List<TopoDS_Shape>::Iterator itIm(*pIm);
          for (; itIm.More(); itIm.Next())
          {
            const TopoDS_Shape& aPartIm = itIm.Value();
            if (!aMSSolids.Contains(aPartIm))
              aLParts.Append(aPartIm);
          }
        }
        else if (!aMSSolids.Contains(aPart))
          aLParts.Append(aPart);

        break;
      }
      default:
      {
        for (TopoDS_Iterator it(aPart); it.More(); it.Next())
          aLPartsInput.Append(it.Value());
        break;
      }
    }
  }

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    anINFaces;
  itLS.Initialize(theSolids);
  for (; itLS.More(); itLS.Next())
  {
    const TopoDS_Shape& aSolid = itLS.Value();
    if (aSolid.ShapeType() != TopAbs_SOLID)
      continue;

    TopoDS_Solid aSd = *(TopoDS_Solid*)&aSolid;

    itLP.Initialize(aLParts);
    for (; itLP.More();)
    {
      TopoDS_Shape aPart = itLP.Value();
      TopAbs_State aState =
        BOPTools_AlgoTools::ComputeStateByOnePoint(aPart, aSd, Precision::Confusion(), theContext);
      if (aState == TopAbs_IN)
      {
        if (aPart.ShapeType() == TopAbs_FACE)
        {
          NCollection_List<TopoDS_Shape>* pFaces = anINFaces.ChangeSeek(aSd);
          if (!pFaces)
            pFaces = anINFaces.Bound(aSd, NCollection_List<TopoDS_Shape>());
          pFaces->Append(aPart);
        }
        else
        {
          aPart.Orientation(TopAbs_INTERNAL);
          BRep_Builder().Add(aSd, aPart);
        }
        aLParts.Remove(itLP);
      }
      else
        itLP.Next();
    }
  }

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator itM(anINFaces);
  for (; itM.More(); itM.Next())
  {
    TopoDS_Solid                          aSd    = *(TopoDS_Solid*)&itM.Key();
    const NCollection_List<TopoDS_Shape>& aFaces = itM.Value();

    TopoDS_Compound aCF;
    BRep_Builder().MakeCompound(aCF);

    NCollection_List<TopoDS_Shape>::Iterator itLF(aFaces);
    for (; itLF.More(); itLF.Next())
      BRep_Builder().Add(aCF, itLF.Value());

    NCollection_List<TopoDS_Shape> aLCB;
    BOPTools_AlgoTools::MakeConnexityBlocks(aCF, TopAbs_EDGE, TopAbs_FACE, aLCB);

    NCollection_List<TopoDS_Shape>::Iterator itCB(aLCB);
    for (; itCB.More(); itCB.Next())
    {
      const TopoDS_Shape& aCB = itCB.Value();

      TopoDS_Shell aShell;
      BRep_Builder().MakeShell(aShell);

      TopExp_Explorer expF(aCB, TopAbs_FACE);
      for (; expF.More(); expF.Next())
      {
        TopoDS_Face aFInt = TopoDS::Face(expF.Current());
        aFInt.Orientation(TopAbs_INTERNAL);
        BRep_Builder().Add(aShell, aFInt);
      }

      BRep_Builder().Add(aSd, aShell);
    }
  }
}

bool BOPAlgo_Tools::TrsfToPoint(const Bnd_Box& theBox1,
                                const Bnd_Box& theBox2,
                                gp_Trsf&       theTrsf,
                                const gp_Pnt&  thePoint,
                                const double   theCriteria)
{

  Bnd_Box aBox = theBox1;
  aBox.Add(theBox2);

  gp_XYZ aBCenter = (aBox.CornerMin().XYZ() + aBox.CornerMax().XYZ()) / 2.;
  double aPBDist  = (thePoint.XYZ() - aBCenter).Modulus();
  if (aPBDist < theCriteria)
    return false;

  double aBSize = std::sqrt(aBox.SquareExtent());
  if ((aBSize / aPBDist) > (1. / theCriteria))
    return false;

  theTrsf.SetTranslation(gp_Vec(aBox.CornerMin(), thePoint));
  return true;
}
