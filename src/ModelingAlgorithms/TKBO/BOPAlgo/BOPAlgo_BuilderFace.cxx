#include <BOPAlgo_BuilderFace.hpp>
#include <BOPAlgo_WireEdgeSet.hpp>
#include <BOPAlgo_WireSplitter.hpp>
#include <BOPAlgo_Alerts.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BOPTools_BoxTree.hpp>
#include <Bnd_Tools.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepBndLib.hpp>
#include <BRepTools.hpp>
#include <Geom_Surface.hpp>
#include <gp_Pnt2d.hpp>
#include <IntTools_Context.hpp>
#include <IntTools_FClass2d.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

static bool IsGrowthWire(const TopoDS_Shape&,
                         const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&);

static bool IsInside(const TopoDS_Shape&, const TopoDS_Shape&, occ::handle<IntTools_Context>&);
static void MakeInternalWires(const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&,
                              NCollection_List<TopoDS_Shape>&);

BOPAlgo_BuilderFace::BOPAlgo_BuilderFace()

{
  myOrientation = TopAbs_EXTERNAL;
}

BOPAlgo_BuilderFace::BOPAlgo_BuilderFace(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPAlgo_BuilderArea(theAllocator)
{
  myOrientation = TopAbs_EXTERNAL;
}

BOPAlgo_BuilderFace::~BOPAlgo_BuilderFace() = default;

void BOPAlgo_BuilderFace::SetFace(const TopoDS_Face& theFace)
{
  myOrientation = theFace.Orientation();
  myFace        = theFace;
  myFace.Orientation(TopAbs_FORWARD);
}

TopAbs_Orientation BOPAlgo_BuilderFace::Orientation() const
{
  return myOrientation;
}

const TopoDS_Face& BOPAlgo_BuilderFace::Face() const
{
  return myFace;
}

void BOPAlgo_BuilderFace::CheckData()
{
  if (myFace.IsNull())
  {
    AddError(new BOPAlgo_AlertNullInputShapes);
    return;
  }
  if (myContext.IsNull())
  {
    myContext = new IntTools_Context;
  }
}

void BOPAlgo_BuilderFace::Perform(const Message_ProgressRange& theRange)
{
  Message_ProgressScope aPS(theRange, nullptr, 100);

  GetReport()->Clear();

  CheckData();
  if (HasErrors())
  {
    return;
  }

  PerformShapesToAvoid(aPS.Next(1));
  if (HasErrors())
  {
    return;
  }

  PerformLoops(aPS.Next(10));
  if (HasErrors())
  {
    return;
  }

  PerformAreas(aPS.Next(80));
  if (HasErrors())
  {
    return;
  }

  PerformInternalShapes(aPS.Next(9));
}

void BOPAlgo_BuilderFace::PerformShapesToAvoid(const Message_ProgressRange& theRange)
{
  bool bFound;
  int  i, aNbV, aNbE;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                           aMVE;
  NCollection_List<TopoDS_Shape>::Iterator aIt;

  myShapesToAvoid.Clear();

  Message_ProgressScope aPS(theRange, nullptr, 1);

  for (;;)
  {
    if (UserBreak(aPS))
    {
      return;
    }
    bFound = false;

    aMVE.Clear();
    aIt.Initialize(myShapes);
    for (; aIt.More(); aIt.Next())
    {
      const TopoDS_Shape& aE = aIt.Value();
      if (!myShapesToAvoid.Contains(aE))
      {
        TopExp::MapShapesAndAncestors(aE, TopAbs_VERTEX, TopAbs_EDGE, aMVE);
      }
    }
    aNbV = aMVE.Extent();

    for (i = 1; i <= aNbV; ++i)
    {
      const TopoDS_Vertex& aV = (*(TopoDS_Vertex*)(&aMVE.FindKey(i)));

      NCollection_List<TopoDS_Shape>& aLE = aMVE.ChangeFromKey(aV);
      aNbE                                = aLE.Extent();
      if (!aNbE)
      {
        continue;
      }

      const TopoDS_Edge& aE1 = (*(TopoDS_Edge*)(&aLE.First()));
      if (aNbE == 1)
      {
        if (BRep_Tool::Degenerated(aE1))
        {
          continue;
        }
        if (aV.Orientation() == TopAbs_INTERNAL)
        {
          continue;
        }
        bFound = true;
        myShapesToAvoid.Add(aE1);
      }
      else if (aNbE == 2)
      {
        const TopoDS_Edge& aE2 = (*(TopoDS_Edge*)(&aLE.Last()));
        if (aE2.IsSame(aE1))
        {
          TopoDS_Vertex aV1x, aV2x;

          TopExp::Vertices(aE1, aV1x, aV2x);
          if (aV1x.IsSame(aV2x))
          {
            continue;
          }
          bFound = true;
          myShapesToAvoid.Add(aE1);
          myShapesToAvoid.Add(aE2);
        }
      }
    }

    if (!bFound)
    {
      break;
    }
  }
}

void BOPAlgo_BuilderFace::PerformLoops(const Message_ProgressRange& theRange)
{
  bool                                     bFlag;
  int                                      i, aNbEA;
  NCollection_List<TopoDS_Shape>::Iterator aIt;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                aVEMap;
  NCollection_Map<TopoDS_Shape> aMAdded;
  TopoDS_Iterator               aItW;
  BRep_Builder                  aBB;
  BOPAlgo_WireEdgeSet           aWES(myAllocator);
  BOPAlgo_WireSplitter          aWSp(myAllocator);

  Message_ProgressScope aMainScope(theRange, "Making wires", 10);

  myLoops.Clear();
  aWES.SetFace(myFace);

  aIt.Initialize(myShapes);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aE = aIt.Value();
    if (!myShapesToAvoid.Contains(aE))
    {
      aWES.AddStartElement(aE);
    }
  }

  aWSp.SetWES(aWES);
  aWSp.SetRunParallel(myRunParallel);
  aWSp.SetContext(myContext);
  aWSp.Perform(aMainScope.Next(9));
  if (aWSp.HasErrors())
  {
    return;
  }

  const NCollection_List<TopoDS_Shape>& aLW = aWES.Shapes();
  aIt.Initialize(aLW);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aW = aIt.Value();
    myLoops.Append(aW);
  }

  NCollection_Map<TopoDS_Shape> aMEP;

  aIt.Initialize(myLoops);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aW = aIt.Value();
    aItW.Initialize(aW);
    for (; aItW.More(); aItW.Next())
    {
      const TopoDS_Shape& aE = aItW.Value();
      aMEP.Add(aE);
    }
  }
  if (UserBreak(aMainScope))
  {
    return;
  }

  aNbEA = myShapesToAvoid.Extent();
  for (i = 1; i <= aNbEA; ++i)
  {
    const TopoDS_Shape& aE = myShapesToAvoid(i);
    aMEP.Add(aE);
  }

  aIt.Initialize(myShapes);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aE = aIt.Value();
    if (!aMEP.Contains(aE))
    {
      myShapesToAvoid.Add(aE);
    }
  }

  if (UserBreak(aMainScope))
  {
    return;
  }

  myLoopsInternal.Clear();

  aNbEA = myShapesToAvoid.Extent();
  for (i = 1; i <= aNbEA; ++i)
  {
    const TopoDS_Shape& aEE = myShapesToAvoid(i);
    TopExp::MapShapesAndAncestors(aEE, TopAbs_VERTEX, TopAbs_EDGE, aVEMap);
  }

  bFlag = true;
  for (i = 1; (i <= aNbEA) && bFlag; ++i)
  {
    const TopoDS_Shape& aEE = myShapesToAvoid(i);
    if (!aMAdded.Add(aEE))
    {
      continue;
    }

    if (UserBreak(aMainScope))
    {
      return;
    }

    TopoDS_Wire aW;
    aBB.MakeWire(aW);
    aBB.Add(aW, aEE);

    aItW.Initialize(aW);
    for (; aItW.More() && bFlag; aItW.Next())
    {
      const TopoDS_Edge& aE = (*(TopoDS_Edge*)(&aItW.Value()));

      TopoDS_Iterator aItE(aE);
      for (; aItE.More() && bFlag; aItE.Next())
      {
        const TopoDS_Vertex&                  aV  = (*(TopoDS_Vertex*)(&aItE.Value()));
        const NCollection_List<TopoDS_Shape>& aLE = aVEMap.FindFromKey(aV);
        aIt.Initialize(aLE);
        for (; aIt.More() && bFlag; aIt.Next())
        {
          const TopoDS_Shape& aEx = aIt.Value();
          if (aMAdded.Add(aEx))
          {
            aBB.Add(aW, aEx);
            if (aMAdded.Extent() == aNbEA)
            {
              bFlag = !bFlag;
            }
          }
        }
      }
    }
    aW.Closed(BRep_Tool::IsClosed(aW));
    myLoopsInternal.Append(aW);
  }
}

void BOPAlgo_BuilderFace::PerformAreas(const Message_ProgressRange& theRange)
{
  myAreas.Clear();
  BRep_Builder aBB;

  TopLoc_Location aLoc;

  const occ::handle<Geom_Surface>& aS = BRep_Tool::Surface(myFace, aLoc);

  double aTol = BRep_Tool::Tolerance(myFace);

  Message_ProgressScope aMainScope(theRange, nullptr, 10);

  if (myLoops.IsEmpty())
  {
    if (myContext->IsInfiniteFace(myFace))
    {
      TopoDS_Face aFace;
      aBB.MakeFace(aFace, aS, aLoc, aTol);
      if (BRep_Tool::NaturalRestriction(myFace))
        aBB.NaturalRestriction(aFace, true);
      myAreas.Append(aFace);
    }
    return;
  }

  NCollection_List<TopoDS_Shape> aNewFaces;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aHoleFaces;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMHE;

  Message_ProgressScope aPSClass(aMainScope.Next(5), "Making faces", myLoops.Size());
  NCollection_List<TopoDS_Shape>::Iterator aItLL(myLoops);
  for (; aItLL.More(); aItLL.Next(), aPSClass.Next())
  {
    if (UserBreak(aPSClass))
    {
      return;
    }

    const TopoDS_Shape& aWire = aItLL.Value();

    TopoDS_Face aFace;
    aBB.MakeFace(aFace, aS, aLoc, aTol);
    aBB.Add(aFace, aWire);

    bool bIsGrowth = IsGrowthWire(aWire, aMHE);
    if (!bIsGrowth)
    {

      IntTools_FClass2d& aClsf = myContext->FClass2d(aFace);
      bIsGrowth                = !aClsf.IsHole();
    }

    if (bIsGrowth)
    {
      aNewFaces.Append(aFace);
    }
    else
    {
      aHoleFaces.Add(aFace);
      TopExp::MapShapes(aWire, TopAbs_EDGE, aMHE);
    }
  }

  if (aHoleFaces.IsEmpty())
  {

    myAreas.Append(aNewFaces);
    return;
  }

  BOPTools_Box2dTree aBoxTree;
  int                i, aNbH = aHoleFaces.Extent();
  aBoxTree.SetSize(aNbH);
  for (i = 1; i <= aNbH; ++i)
  {
    const TopoDS_Face& aHFace = TopoDS::Face(aHoleFaces(i));

    Bnd_Box2d aBox;
    BRepTools::AddUVBounds(aHFace, aBox);
    aBoxTree.Add(i, Bnd_Tools::Bnd2BVH(aBox));
  }

  aBoxTree.Build();

  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> aHoleFaceMap;

  BOPTools_Box2dTreeSelector aSelector;
  aSelector.SetBVHSet(&aBoxTree);

  Message_ProgressScope aPSHoles(aMainScope.Next(4), "Adding holes", aNewFaces.Extent());
  NCollection_List<TopoDS_Shape>::Iterator aItLS(aNewFaces);
  for (; aItLS.More(); aItLS.Next(), aPSHoles.Next())
  {
    if (UserBreak(aPSHoles))
    {
      return;
    }
    const TopoDS_Face& aFace = TopoDS::Face(aItLS.Value());

    Bnd_Box2d aBox;
    BRepTools::AddUVBounds(aFace, aBox);

    aSelector.Clear();
    aSelector.SetBox(Bnd_Tools::Bnd2BVH(aBox));
    aSelector.Select();

    const NCollection_List<int>&    aLI = aSelector.Indices();
    NCollection_List<int>::Iterator aItLI(aLI);
    for (; aItLI.More(); aItLI.Next())
    {
      int                 k     = aItLI.Value();
      const TopoDS_Shape& aHole = aHoleFaces(k);

      if (!IsInside(aHole, aFace, myContext))
        continue;

      TopoDS_Shape* pFaceWas = aHoleFaceMap.ChangeSeek(aHole);
      if (pFaceWas)
      {
        if (IsInside(aFace, *pFaceWas, myContext))
        {
          *pFaceWas = aFace;
        }
      }
      else
      {
        aHoleFaceMap.Add(aHole, aFace);
      }
    }
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aFaceHolesMap;

  aNbH = aHoleFaceMap.Extent();
  for (i = 1; i <= aNbH; ++i)
  {
    const TopoDS_Shape& aHole = aHoleFaceMap.FindKey(i);
    const TopoDS_Shape& aFace = aHoleFaceMap(i);

    NCollection_List<TopoDS_Shape>* pLHoles = aFaceHolesMap.ChangeSeek(aFace);
    if (!pLHoles)
      pLHoles = &aFaceHolesMap(aFaceHolesMap.Add(aFace, NCollection_List<TopoDS_Shape>()));
    pLHoles->Append(aHole);
  }

  if (aHoleFaces.Extent() != aHoleFaceMap.Extent())
  {
    Bnd_Box aBoxF;
    BRepBndLib::Add(myFace, aBoxF);
    if (aBoxF.IsOpenXmin() || aBoxF.IsOpenXmax() || aBoxF.IsOpenYmin() || aBoxF.IsOpenYmax()
        || aBoxF.IsOpenZmin() || aBoxF.IsOpenZmax())
    {
      TopoDS_Face aFace;
      aBB.MakeFace(aFace, aS, aLoc, aTol);
      NCollection_List<TopoDS_Shape>& anUnUsedHoles =
        aFaceHolesMap(aFaceHolesMap.Add(aFace, NCollection_List<TopoDS_Shape>()));
      aNbH = aHoleFaces.Extent();
      for (i = 1; i <= aNbH; ++i)
      {
        const TopoDS_Shape& aHole = aHoleFaces(i);
        if (!aHoleFaceMap.Contains(aHole))
          anUnUsedHoles.Append(aHole);
      }

      aNewFaces.Append(aFace);
    }
  }

  Message_ProgressScope aPSU(aMainScope.Next(), nullptr, aNewFaces.Size());
  aItLS.Initialize(aNewFaces);
  for (; aItLS.More(); aItLS.Next(), aPSU.Next())
  {
    if (UserBreak(aPSU))
    {
      return;
    }

    TopoDS_Face&                          aFace   = *(TopoDS_Face*)&aItLS.Value();
    const NCollection_List<TopoDS_Shape>* pLHoles = aFaceHolesMap.Seek(aFace);
    if (pLHoles)
    {

      NCollection_List<TopoDS_Shape>::Iterator aItLH(*pLHoles);
      for (; aItLH.More(); aItLH.Next())
      {
        const TopoDS_Shape& aFHole = aItLH.Value();

        TopoDS_Iterator aItW(aFHole);
        aBB.Add(aFace, aItW.Value());
      }

      myContext->FClass2d(aFace).Init(aFace, aTol);
    }

    myAreas.Append(aFace);
  }
}

void BOPAlgo_BuilderFace::PerformInternalShapes(const Message_ProgressRange& theRange)
{
  if (myAvoidInternalShapes)

    return;

  if (myLoopsInternal.IsEmpty())

    return;

  BOPTools_Box2dTree aBoxTree;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> anEdgesMap;

  Message_ProgressScope aMainScope(theRange, "Adding internal shapes", 3);

  NCollection_List<TopoDS_Shape>::Iterator itLE(myLoopsInternal);
  for (; itLE.More(); itLE.Next())
  {
    if (UserBreak(aMainScope))
    {
      return;
    }
    TopoDS_Iterator itE(itLE.Value());
    for (; itE.More(); itE.Next())
    {
      const TopoDS_Edge& aE = TopoDS::Edge(itE.Value());
      if (!anEdgesMap.Contains(aE))
      {
        Bnd_Box2d aBoxE;
        BRepTools::AddUVBounds(myFace, aE, aBoxE);

        aBoxTree.Add(anEdgesMap.Add(aE), Bnd_Tools::Bnd2BVH(aBoxE));
      }
    }
  }

  aBoxTree.Build();

  aMainScope.Next();

  NCollection_Map<int> aMEDone;

  Message_ProgressScope                    aPSClass(aMainScope.Next(), nullptr, myAreas.Size());
  NCollection_List<TopoDS_Shape>::Iterator itLF(myAreas);
  for (; itLF.More(); itLF.Next(), aPSClass.Next())
  {
    if (UserBreak(aPSClass))
    {
      return;
    }
    TopoDS_Face& aF = *(TopoDS_Face*)&itLF.Value();

    Bnd_Box2d aBoxF;
    BRepTools::AddUVBounds(aF, aBoxF);

    BOPTools_Box2dTreeSelector aSelector;
    aSelector.SetBVHSet(&aBoxTree);
    aSelector.SetBox(Bnd_Tools::Bnd2BVH(aBoxF));
    if (!aSelector.Select())
      continue;

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> anEdgesInside;

    const NCollection_List<int>&    aLI = aSelector.Indices();
    NCollection_List<int>::Iterator itLI(aLI);
    for (; itLI.More(); itLI.Next())
    {
      const int nE = itLI.Value();
      if (aMEDone.Contains(nE))
        continue;

      const TopoDS_Edge& aE = TopoDS::Edge(anEdgesMap(nE));
      if (IsInside(aE, aF, myContext))
      {
        anEdgesInside.Add(aE);
        aMEDone.Add(nE);
      }
    }

    if (anEdgesInside.IsEmpty())
      continue;

    NCollection_List<TopoDS_Shape> aLSI;
    MakeInternalWires(anEdgesInside, aLSI);

    NCollection_List<TopoDS_Shape>::Iterator itLSI(aLSI);
    for (; itLSI.More(); itLSI.Next())
    {
      const TopoDS_Shape& aWI = itLSI.Value();
      BRep_Builder().Add(aF, aWI);
    }

    if (aMEDone.Extent() == anEdgesMap.Extent())

      return;
  }

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> anEdgesUnUsed;
  for (int i = 1; i <= anEdgesMap.Extent(); ++i)
  {
    if (!aMEDone.Contains(i))
      anEdgesUnUsed.Add(anEdgesMap(i));
  }

  NCollection_List<TopoDS_Shape> aLSI;
  MakeInternalWires(anEdgesUnUsed, aLSI);

  TopoDS_Compound aWShape;
  BRep_Builder().MakeCompound(aWShape);
  BRep_Builder().Add(aWShape, myFace);
  if (aLSI.Extent() == 1)
    BRep_Builder().Add(aWShape, aLSI.First());
  else
  {
    TopoDS_Compound aCE;
    BRep_Builder().MakeCompound(aCE);
    for (NCollection_List<TopoDS_Shape>::Iterator it(aLSI); it.More(); it.Next())
      BRep_Builder().Add(aCE, it.Value());
    BRep_Builder().Add(aWShape, aCE);
  }

  AddWarning(new BOPAlgo_AlertFaceBuilderUnusedEdges(aWShape));
}

void MakeInternalWires(const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theME,
                       NCollection_List<TopoDS_Shape>& theWires)
{
  int                                                    i, aNbE;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aAddedMap;
  NCollection_List<TopoDS_Shape>::Iterator               aItE;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
               aMVE;
  BRep_Builder aBB;

  aNbE = theME.Extent();
  for (i = 1; i <= aNbE; ++i)
  {
    const TopoDS_Shape& aE = theME(i);
    TopExp::MapShapesAndAncestors(aE, TopAbs_VERTEX, TopAbs_EDGE, aMVE);
  }

  for (i = 1; i <= aNbE; ++i)
  {
    TopoDS_Shape aEE = theME(i);
    if (!aAddedMap.Add(aEE))
    {
      continue;
    }

    TopoDS_Wire aW;
    aBB.MakeWire(aW);
    aEE.Orientation(TopAbs_INTERNAL);
    aBB.Add(aW, aEE);

    TopoDS_Iterator aItAdded(aW);
    for (; aItAdded.More(); aItAdded.Next())
    {
      const TopoDS_Shape& aE = aItAdded.Value();

      TopExp_Explorer aExp(aE, TopAbs_VERTEX);
      for (; aExp.More(); aExp.Next())
      {
        const TopoDS_Shape&                   aV  = aExp.Current();
        const NCollection_List<TopoDS_Shape>& aLE = aMVE.FindFromKey(aV);
        aItE.Initialize(aLE);
        for (; aItE.More(); aItE.Next())
        {
          TopoDS_Shape aEL = aItE.Value();
          if (aAddedMap.Add(aEL))
          {
            aEL.Orientation(TopAbs_INTERNAL);
            aBB.Add(aW, aEL);
          }
        }
      }
    }
    aW.Closed(BRep_Tool::IsClosed(aW));
    theWires.Append(aW);
  }
}

bool IsInside(const TopoDS_Shape&            theWire,
              const TopoDS_Shape&            theF,
              occ::handle<IntTools_Context>& theContext)
{

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aFaceEdgesMap;
  TopExp::MapShapes(theF, TopAbs_EDGE, aFaceEdgesMap);

  const TopoDS_Face& aF          = TopoDS::Face(theF);
  IntTools_FClass2d& aClassifier = theContext->FClass2d(aF);

  bool isInside = false;

  TopExp_Explorer anExp(theWire, TopAbs_EDGE);
  for (; anExp.More(); anExp.Next())
  {
    const TopoDS_Edge& aE = TopoDS::Edge(anExp.Current());
    if (BRep_Tool::Degenerated(aE))

      continue;

    if (aFaceEdgesMap.Contains(aE))

      return isInside;

    double                           aT1, aT2;
    const occ::handle<Geom2d_Curve>& aC2D = BRep_Tool::CurveOnSurface(aE, aF, aT1, aT2);
    if (aC2D.IsNull())
      continue;

    gp_Pnt2d aP2D = aC2D->Value((aT1 + aT2) / 2.);

    TopAbs_State aState = aClassifier.Perform(aP2D);
    isInside            = (aState == TopAbs_IN);
    break;
  }
  return isInside;
}

bool IsGrowthWire(const TopoDS_Shape&                                                  theWire,
                  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMHE)
{
  if (theMHE.Extent())
  {
    TopoDS_Iterator aIt(theWire);
    for (; aIt.More(); aIt.Next())
    {
      if (theMHE.Contains(aIt.Value()))
        return true;
    }
  }
  return false;
}
