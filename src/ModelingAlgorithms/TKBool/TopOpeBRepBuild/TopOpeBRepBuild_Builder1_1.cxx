#include <BRepAdaptor_Curve.hpp>
#include <BRepTools.hpp>
#include <Geom_Curve.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_GTool.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_HBuilder.hpp>
#include <TopOpeBRepBuild_PaveSet.hpp>
#include <TopOpeBRepBuild_Tools.hpp>
#include <TopOpeBRepDS_BuildTool.hpp>
#include <TopAbs_State.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepDS_ShapeWithState.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopOpeBRepDS_ListOfShapeOn1State.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>

const double PAR_T = 0.43213918;

static TopAbs_State ClassifyEdgeToSolidByOnePoint(const TopoDS_Edge&              E,
                                                  TopOpeBRepTool_ShapeClassifier& SC);

static NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> processedEdges;
static NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> theUsedVertexMap;
static NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>        theUnkStateVer;

extern bool GLOBAL_faces2d;

TopOpeBRepBuild_Builder1::~TopOpeBRepBuild_Builder1()
{
  processedEdges.Clear();
  theUsedVertexMap.Clear();
  theUnkStateVer.Clear();
}

void TopOpeBRepBuild_Builder1::PerformShapeWithStates()
{
  theUsedVertexMap.Clear();
  theUnkStateVer.Clear();
  myDataStructure->ChangeDS().ChangeMapOfShapeWithStateObj().Clear();
  myDataStructure->ChangeDS().ChangeMapOfShapeWithStateTool().Clear();

  int i, nbC = myDataStructure->DS().NbCurves();
  for (i = 1; i <= nbC; i++)
  {
    NCollection_List<TopoDS_Shape>&          LSE = ChangeNewEdges(i);
    NCollection_List<TopoDS_Shape>::Iterator it(LSE);
    for (; it.More(); it.Next())
    {
      const TopoDS_Shape& E = it.Value();
      TopoDS_Vertex       Vf, Vl;
      TopExp::Vertices(TopoDS::Edge(E), Vf, Vl);
      theUsedVertexMap.Add(Vf);
      theUsedVertexMap.Add(Vl);
    }
  }

  const TopOpeBRepDS_DataStructure& BDS = myDataStructure->DS();
  int                               n   = BDS.NbSectionEdges();
  for (i = 1; i <= n; i++)
  {
    NCollection_List<TopoDS_Shape>::Iterator anIt;
    const TopoDS_Edge&                       E = TopoDS::Edge(BDS.SectionEdge(i));
    if (E.IsNull())
      continue;

    const NCollection_List<TopoDS_Shape>& SplitsON = Splits(E, TopAbs_ON);
    anIt.Initialize(SplitsON);
    for (; anIt.More(); anIt.Next())
    {
      TopoDS_Shape  aNewEdge = anIt.Value();
      TopoDS_Vertex Vf, Vl;
      TopExp::Vertices(TopoDS::Edge(aNewEdge), Vf, Vl);
      theUsedVertexMap.Add(Vf);
      theUsedVertexMap.Add(Vl);
    }

    const NCollection_List<TopoDS_Shape>& SplitsIN = Splits(E, TopAbs_IN);
    anIt.Initialize(SplitsIN);
    for (; anIt.More(); anIt.Next())
    {
      TopoDS_Shape  aNewEdge = anIt.Value();
      TopoDS_Vertex Vf, Vl;
      TopExp::Vertices(TopoDS::Edge(aNewEdge), Vf, Vl);
      theUsedVertexMap.Add(Vf);
      theUsedVertexMap.Add(Vl);
    }

    const NCollection_List<TopoDS_Shape>& SplitsOUT = Splits(E, TopAbs_OUT);
    anIt.Initialize(SplitsOUT);
    for (; anIt.More(); anIt.Next())
    {
      TopoDS_Shape  aNewEdge = anIt.Value();
      TopoDS_Vertex Vf, Vl;
      TopExp::Vertices(TopoDS::Edge(aNewEdge), Vf, Vl);
      theUsedVertexMap.Add(Vf);
      theUsedVertexMap.Add(Vl);
    }
  }

  TopOpeBRepDS_ShapeWithState aShapeWithState;
  TopOpeBRepDS_DataStructure& aDataStructure = myDataStructure->ChangeDS();

  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_ShapeWithState, TopTools_ShapeMapHasher>&
    aMapOfShapeWithStateObj = aDataStructure.ChangeMapOfShapeWithStateObj();
  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_ShapeWithState, TopTools_ShapeMapHasher>&
    aMapOfShapeWithStateTool = aDataStructure.ChangeMapOfShapeWithStateTool();

  aMapOfShapeWithStateObj.Add(myShape1, aShapeWithState);
  aMapOfShapeWithStateTool.Add(myShape2, aShapeWithState);

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMapOfRejectedShapesObj =
    aDataStructure.ChangeMapOfRejectedShapesObj();
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMapOfRejectedShapesTool =
    aDataStructure.ChangeMapOfRejectedShapesTool();

  aShapeWithState.SetIsSplitted(false);
  aShapeWithState.SetState(TopAbs_OUT);

  int iW, j, nW, nE, nRSObj = aMapOfRejectedShapesObj.Extent(),
                     nRSTool = aMapOfRejectedShapesTool.Extent();

  for (i = 1; i <= nRSObj; i++)
  {
    const TopoDS_Shape& aFace = aMapOfRejectedShapesObj(i);
    if (aFace.ShapeType() != TopAbs_FACE)
      continue;
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aWiresMap;

    TopExp::MapShapes(aFace, TopAbs_WIRE, aWiresMap);
    nW = aWiresMap.Extent();
    for (iW = 1; iW <= nW; iW++)
    {
      const TopoDS_Shape& aWire = aWiresMap(iW);

      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> anEdgesMap;
      TopExp::MapShapes(aWire, TopAbs_EDGE, anEdgesMap);
      nE = anEdgesMap.Extent();
      for (j = 1; j <= nE; j++)
        aMapOfShapeWithStateObj.Add(anEdgesMap(j), aShapeWithState);

      aMapOfShapeWithStateObj.Add(aWire, aShapeWithState);
    }
    aMapOfShapeWithStateObj.Add(aFace, aShapeWithState);
  }

  for (i = 1; i <= nRSTool; i++)
  {
    const TopoDS_Shape& aFace = aMapOfRejectedShapesTool(i);

    if (aFace.ShapeType() != TopAbs_FACE)
      continue;
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aWiresMap;
    TopExp::MapShapes(aFace, TopAbs_WIRE, aWiresMap);
    nW = aWiresMap.Extent();
    for (iW = 1; iW <= nW; iW++)
    {
      const TopoDS_Shape& aWire = aWiresMap(iW);

      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> anEdgesMap;
      TopExp::MapShapes(aWire, TopAbs_EDGE, anEdgesMap);
      nE = anEdgesMap.Extent();
      for (j = 1; j <= nE; j++)
        aMapOfShapeWithStateTool.Add(anEdgesMap(j), aShapeWithState);

      aMapOfShapeWithStateTool.Add(aWire, aShapeWithState);
    }
    aMapOfShapeWithStateTool.Add(aFace, aShapeWithState);
  }

  PerformShapeWithStates(myShape1, myShape2);
  processedEdges.Clear();
  PerformShapeWithStates(myShape2, myShape1);
  processedEdges.Clear();
}

void TopOpeBRepBuild_Builder1::PerformShapeWithStates(const TopoDS_Shape& anObj,
                                                      const TopoDS_Shape& aReference)
{
  myShapeClassifier.SetReference(aReference);
  TopOpeBRepDS_DataStructure& aDS = myDataStructure->ChangeDS();

  bool aFlag;
  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_ShapeWithState, TopTools_ShapeMapHasher>&
    aMapOfShapeWithState = aDS.ChangeMapOfShapeWithState(anObj, aFlag);
  if (!aFlag)
    return;

  int i, j, k, nS, nF, nE;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aFacesMap,
    aFacesWithInterferencesMap, aFacesToRestMap;
  NCollection_DataMap<TopoDS_Shape, TopAbs_State, TopTools_ShapeMapHasher> aSplFacesState;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aShellsMap;
  TopExp::MapShapes(anObj, TopAbs_SHELL, aShellsMap);

  nS = aShellsMap.Extent();
  for (i = 1; i <= nS; i++)
  {
    const TopoDS_Shape& aShell = aShellsMap(i);

    if (aMapOfShapeWithState.Contains(aShell))
      continue;

    else if (!myDataStructure->HasShape(aShell))
    {

      TopOpeBRepBuild_Tools::FindStateThroughVertex(aShell,
                                                    myShapeClassifier,
                                                    aMapOfShapeWithState,
                                                    theUnkStateVer);
      continue;
    }

    else
    {

      aFacesMap.Clear();
      aFacesWithInterferencesMap.Clear();
      aFacesToRestMap.Clear();
      aSplFacesState.Clear();

      TopExp::MapShapes(aShell, TopAbs_FACE, aFacesMap);
      nF = aFacesMap.Extent();
      for (j = 1; j <= nF; j++)
      {
        const TopoDS_Shape& aFace = aFacesMap(j);

        if (aMapOfShapeWithState.Contains(aFace))
        {

          NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> anEdgesMap;
          TopExp::MapShapes(aFace, TopAbs_EDGE, anEdgesMap);
          nE = anEdgesMap.Extent();
          for (k = 1; k <= nE; k++)
          {
            const TopoDS_Shape&                anEdge = anEdgesMap(k);
            const TopOpeBRepDS_ShapeWithState& aSWS   = aMapOfShapeWithState.FindFromKey(anEdge);
            TopAbs_State                       aState = aSWS.State();
            aSplFacesState.Bind(anEdge, aState);
          }
          continue;
        }
        else if (myDataStructure->HasShape(aFace))
          aFacesWithInterferencesMap.Add(aFace);
        else
        {
          aFacesToRestMap.Add(aFace);
        }
      }

      PerformFacesWithStates(anObj, aFacesWithInterferencesMap, aSplFacesState);

      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> anUnkStateEdge;
      TopOpeBRepBuild_Tools::PropagateState(aSplFacesState,
                                            aFacesToRestMap,
                                            TopAbs_EDGE,
                                            TopAbs_FACE,
                                            myShapeClassifier,
                                            aMapOfShapeWithState,
                                            anUnkStateEdge);

      TopOpeBRepBuild_Tools::PropagateStateForWires(aFacesToRestMap, aMapOfShapeWithState);
    }
  }
}

void TopOpeBRepBuild_Builder1::PerformFacesWithStates(
  const TopoDS_Shape&                                                  anObj,
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aFacesWithInterferencesMap,
  NCollection_DataMap<TopoDS_Shape, TopAbs_State, TopTools_ShapeMapHasher>& aSplFacesState)
{
  TopOpeBRepDS_DataStructure& aDS = myDataStructure->ChangeDS();

  bool aFlag;
  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_ShapeWithState, TopTools_ShapeMapHasher>&
    aMapOfShapeWithState = aDS.ChangeMapOfShapeWithState(anObj, aFlag);
  if (!aFlag)
    return;

  int i, j, k, nF, nW, nE;

  nF = aFacesWithInterferencesMap.Extent();

  for (i = 1; i <= nF; i++)
  {
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> anEdgesToSplitMap,
      anEdgesToRestMap;

    const TopoDS_Shape& aFace = aFacesWithInterferencesMap(i);

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aWireMap;
    TopExp::MapShapes(aFace, TopAbs_WIRE, aWireMap);
    nW = aWireMap.Extent();
    for (j = 1; j <= nW; j++)
    {
      const TopoDS_Shape& aWire = aWireMap(j);

      if (!myDataStructure->HasShape(aWire))
      {

        TopOpeBRepBuild_Tools::FindStateThroughVertex(aWire,
                                                      myShapeClassifier,
                                                      aMapOfShapeWithState,
                                                      theUnkStateVer);
        continue;
      }

      else
      {

        NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> anEdgeMap;
        TopExp::MapShapes(aWire, TopAbs_EDGE, anEdgeMap);
        nE = anEdgeMap.Extent();
        for (k = 1; k <= nE; k++)
        {
          const TopoDS_Shape& anEdge = anEdgeMap(k);

          if (myDataStructure->HasShape(anEdge))
          {
            anEdgesToSplitMap.Add(anEdge);
          }
          else
          {
            anEdgesToRestMap.Add(anEdge);
          }
        }

        StatusEdgesToSplit(anObj, anEdgesToSplitMap, anEdgesToRestMap);

        nE = anEdgesToRestMap.Extent();
        for (k = 1; k <= nE; k++)
        {
          const TopoDS_Shape& anEdge = anEdgesToRestMap(k);
          if (aMapOfShapeWithState.Contains(anEdge))
          {
            const TopOpeBRepDS_ShapeWithState& aSWS   = aMapOfShapeWithState.FindFromKey(anEdge);
            TopAbs_State                       aState = aSWS.State();
            aSplFacesState.Bind(anEdge, aState);
          }
        }
      }
    }
  }
}

void TopOpeBRepBuild_Builder1::StatusEdgesToSplit(
  const TopoDS_Shape&                                                  anObj,
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& anEdgesToSplitMap,
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& anEdgesToRestMap)
{

  TopOpeBRepDS_DataStructure& aDS = myDataStructure->ChangeDS();

  bool aFlag;
  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_ShapeWithState, TopTools_ShapeMapHasher>&
    aMapOfShapeWithState = aDS.ChangeMapOfShapeWithState(anObj, aFlag);
  if (!aFlag)
    return;

  int i, nE = anEdgesToSplitMap.Extent();
  if (!nE)
    return;

  NCollection_DataMap<TopoDS_Shape, TopAbs_State, TopTools_ShapeMapHasher> aSplEdgesState;
  NCollection_List<TopoDS_Shape>::Iterator                                 anIt;
  TopAbs_State                                                             aState;

  for (i = 1; i <= nE; i++)
  {
    const TopoDS_Shape& anEdge = anEdgesToSplitMap(i);

    if (processedEdges.Contains(anEdge))
    {
      if (aMapOfShapeWithState.Contains(anEdge))
      {
        const TopOpeBRepDS_ShapeWithState& aSWS = aMapOfShapeWithState.FindFromKey(anEdge);
        if (aSWS.IsSplitted())
        {

          const NCollection_List<TopoDS_Shape>& SplitsON = aSWS.Part(TopAbs_ON);
          anIt.Initialize(SplitsON);
          for (; anIt.More(); anIt.Next())
            aSplEdgesState.Bind(anIt.Value(), TopAbs_ON);

          const NCollection_List<TopoDS_Shape>& SplitsOUT = aSWS.Part(TopAbs_OUT);
          anIt.Initialize(SplitsOUT);
          for (; anIt.More(); anIt.Next())
            aSplEdgesState.Bind(anIt.Value(), TopAbs_OUT);

          const NCollection_List<TopoDS_Shape>& SplitsIN = aSWS.Part(TopAbs_IN);
          anIt.Initialize(SplitsIN);
          for (; anIt.More(); anIt.Next())
            aSplEdgesState.Bind(anIt.Value(), TopAbs_IN);
        }
      }
      continue;
    }

    processedEdges.Add(anEdge);

    TopOpeBRepDS_ShapeWithState aShapeWithState;

    bool IsSplitON = IsSplit(anEdge, TopAbs_ON);
    if (IsSplitON)
    {

      const NCollection_List<TopoDS_Shape>& SplitsON = Splits(anEdge, TopAbs_ON);
      anIt.Initialize(SplitsON);
      for (; anIt.More(); anIt.Next())
      {
        TopoDS_Shape aNewEdge = anIt.Value();
        aNewEdge.Orientation(anEdge.Orientation());
        aShapeWithState.AddPart(aNewEdge, TopAbs_ON);
        aSplEdgesState.Bind(anIt.Value(), TopAbs_ON);
      }

      const NCollection_List<TopoDS_Shape>& SplitsIN = Splits(anEdge, TopAbs_IN);
      anIt.Initialize(SplitsIN);
      for (; anIt.More(); anIt.Next())
      {
        TopoDS_Shape aNewEdge = anIt.Value();
        aNewEdge.Orientation(anEdge.Orientation());
        aShapeWithState.AddPart(aNewEdge, TopAbs_IN);
        aSplEdgesState.Bind(anIt.Value(), TopAbs_IN);
      }

      const NCollection_List<TopoDS_Shape>& SplitsOUT = Splits(anEdge, TopAbs_OUT);
      anIt.Initialize(SplitsOUT);
      for (; anIt.More(); anIt.Next())
      {
        TopoDS_Shape aNewEdge = anIt.Value();
        aNewEdge.Orientation(anEdge.Orientation());
        aShapeWithState.AddPart(aNewEdge, TopAbs_OUT);
        aSplEdgesState.Bind(anIt.Value(), TopAbs_OUT);
      }

      aShapeWithState.SetIsSplitted(true);
      aMapOfShapeWithState.Add(anEdge, aShapeWithState);
      continue;
    }

    NCollection_DataMap<TopoDS_Shape, TopAbs_State, TopTools_ShapeMapHasher> aDataMapOfShapeState;
    NCollection_List<TopoDS_Shape>                                           aLNew;

    bool oldState = GLOBAL_faces2d;

    GLOBAL_faces2d = true;
    SplitEdge(anEdge, aLNew, aDataMapOfShapeState);
    GLOBAL_faces2d = oldState;

    if (!aLNew.Extent())
    {

      TopoDS_Vertex Vf, Vl;
      TopExp::Vertices(TopoDS::Edge(anEdge), Vf, Vl);

      bool HasSDV1 = myDataStructure->HasSameDomain(Vf);
      bool HasSDV2 = myDataStructure->HasSameDomain(Vl);

      TopoDS_Edge aNewEdge = TopoDS::Edge(anEdge);

      if (myDataStructure->HasSameDomain(aNewEdge))
      {
        HasSDV1 = false;
        HasSDV2 = false;
      }

      if (HasSDV1 || HasSDV2)
      {
        TopoDS_Shape EOR = anEdge;
        EOR.Orientation(TopAbs_FORWARD);

        double ParF = BRep_Tool::Parameter(Vf, TopoDS::Edge(EOR));
        double ParL = BRep_Tool::Parameter(Vl, TopoDS::Edge(EOR));
        myBuildTool.CopyEdge(EOR, aNewEdge);

        if (HasSDV1)
        {
          int iref = myDataStructure->SameDomainReference(Vf);
          Vf       = TopoDS::Vertex(myDataStructure->Shape(iref));
          Vf.Orientation(TopAbs_FORWARD);
        }

        if (HasSDV2)
        {
          int iref = myDataStructure->SameDomainReference(Vl);
          Vl       = TopoDS::Vertex(myDataStructure->Shape(iref));
          Vl.Orientation(TopAbs_REVERSED);
        }

        myBuildTool.AddEdgeVertex(aNewEdge, Vf);
        myBuildTool.Parameter(aNewEdge, Vf, ParF);

        myBuildTool.AddEdgeVertex(aNewEdge, Vl);
        myBuildTool.Parameter(aNewEdge, Vl, ParL);

        aNewEdge.Orientation(anEdge.Orientation());
      }

      aState = ClassifyEdgeToSolidByOnePoint(aNewEdge, myShapeClassifier);
      aShapeWithState.SetIsSplitted(true);

      aShapeWithState.AddPart(aNewEdge, aState);
      aSplEdgesState.Bind(aNewEdge, aState);

      TopExp::Vertices(aNewEdge, Vf, Vl);
      theUsedVertexMap.Add(Vf);
      theUsedVertexMap.Add(Vl);
      if (!BRep_Tool::Degenerated(TopoDS::Edge(aNewEdge)))
      {

        myShapeClassifier.StateP3DReference(BRep_Tool::Pnt(Vf));
        if (myShapeClassifier.State() != aState && myShapeClassifier.State() != TopAbs_ON)
          theUnkStateVer.Add(Vf);
        if (!Vf.IsSame(Vl))
        {
          myShapeClassifier.StateP3DReference(BRep_Tool::Pnt(Vl));
          if (myShapeClassifier.State() != aState && myShapeClassifier.State() != TopAbs_ON)
            theUnkStateVer.Add(Vl);
        }
      }
    }
    else
    {

      NCollection_List<TopoDS_Shape>::Iterator aLIt(aLNew);
      for (; aLIt.More(); aLIt.Next())
      {
        const TopoDS_Shape& aS = aLIt.Value();
        aState                 = aDataMapOfShapeState(aS);

        bool isdegen = BRep_Tool::Degenerated(TopoDS::Edge(aS));

        if (aState == TopAbs_IN && !isdegen)
          aState = ClassifyEdgeToSolidByOnePoint(TopoDS::Edge(aS), myShapeClassifier);

        aShapeWithState.AddPart(aS, aState);
        aShapeWithState.SetIsSplitted(true);

        aSplEdgesState.Bind(aS, aState);
        TopoDS_Vertex Vf, Vl;
        TopExp::Vertices(TopoDS::Edge(aS), Vf, Vl);
        theUsedVertexMap.Add(Vf);
        theUsedVertexMap.Add(Vl);
        if (!isdegen)
        {

          myShapeClassifier.StateP3DReference(BRep_Tool::Pnt(Vf));
          if (myShapeClassifier.State() != aState && myShapeClassifier.State() != TopAbs_ON)
            theUnkStateVer.Add(Vf);
          if (!Vf.IsSame(Vl))
          {
            myShapeClassifier.StateP3DReference(BRep_Tool::Pnt(Vl));
            if (myShapeClassifier.State() != aState && myShapeClassifier.State() != TopAbs_ON)
              theUnkStateVer.Add(Vl);
          }
        }
      }
    }

    const NCollection_List<TopoDS_Shape>& EspON = aShapeWithState.Part(TopAbs_ON);

    int nON = EspON.Extent();
    if (!IsSplitON && nON)
    {
      TopOpeBRepDS_ListOfShapeOn1State ONspl;
      NCollection_List<TopoDS_Shape>&  lON = ONspl.ChangeListOnState();
      lON.Assign(EspON);
      ONspl.Split(true);
      mySplitON.Bind(anEdge, ONspl);
      myDataStructure->ChangeDS().AddSectionEdge(TopoDS::Edge(anEdge));
    }

    aMapOfShapeWithState.Add(anEdge, aShapeWithState);
  }

  nE = anEdgesToRestMap.Extent();
  for (i = 1; i <= nE; i++)
  {
    const TopoDS_Shape& anEdge = anEdgesToRestMap.FindKey(i);
    if (aMapOfShapeWithState.Contains(anEdge))
    {
      const TopOpeBRepDS_ShapeWithState& aSWS = aMapOfShapeWithState.FindFromKey(anEdge);
      if (!aSWS.IsSplitted())
      {

        aState = aSWS.State();
        aSplEdgesState.Bind(anEdge, aState);
        continue;
      }
    }
  }

  if (nE)

    TopOpeBRepBuild_Tools::PropagateState(aSplEdgesState,
                                          anEdgesToRestMap,
                                          TopAbs_VERTEX,
                                          TopAbs_EDGE,
                                          myShapeClassifier,
                                          aMapOfShapeWithState,
                                          theUnkStateVer);
}

void TopOpeBRepBuild_Builder1::SplitEdge(
  const TopoDS_Shape&                                                       anEdge,
  NCollection_List<TopoDS_Shape>&                                           aLNew,
  NCollection_DataMap<TopoDS_Shape, TopAbs_State, TopTools_ShapeMapHasher>& aDataMapOfShapeState)
{
  double             aPar1, aPar2;
  TopAbs_Orientation anOr1, anOr2;

  TopoDS_Shape EdgeF = anEdge;
  EdgeF.Orientation(TopAbs_FORWARD);

  TopOpeBRepBuild_PaveSet PVS(EdgeF);
  TopOpeBRepBuild_GTopo   G1;
  TopAbs_ShapeEnum        tf = TopAbs_FACE;
  G1                         = TopOpeBRepBuild_GTool::GFusSame(tf, tf);
  myEdgeReference            = TopoDS::Edge(EdgeF);

  GFillPointTopologyPVS(EdgeF, G1, PVS);

  PVS.InitLoop();

  NCollection_List<occ::handle<TopOpeBRepBuild_Pave>>                               aPVSlist;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<int>, TopTools_ShapeMapHasher> aVerOriMap;

  BRepAdaptor_Curve aCurveAdaptor(TopoDS::Edge(anEdge));
  double            tolEdge = BRep_Tool::Tolerance(TopoDS::Edge(anEdge));

  while (PVS.MoreLoop())
  {
    occ::handle<TopOpeBRepBuild_Pave> aPave1 = occ::down_cast<TopOpeBRepBuild_Pave>(PVS.Loop());
    const TopoDS_Vertex&              aV1    = TopoDS::Vertex(aPave1->Vertex());
    aPar1                                    = aPave1->Parameter();

    PVS.NextLoop();
    if (!PVS.MoreLoop())
    {
      aPVSlist.Append(aPave1);
      break;
    }

    occ::handle<TopOpeBRepBuild_Pave> aPave2 = occ::down_cast<TopOpeBRepBuild_Pave>(PVS.Loop());
    const TopoDS_Vertex&              aV2    = TopoDS::Vertex(aPave2->Vertex());
    aPar2                                    = aPave2->Parameter();

    double tolV1  = BRep_Tool::Tolerance(aV1);
    double tolV2  = BRep_Tool::Tolerance(aV2);
    double tolMax = std::max(tolEdge, std::max(tolV1, tolV2));
    double resol  = aCurveAdaptor.Resolution(tolMax);
    double delta  = std::abs(aPar1 - aPar2);

    if (delta < resol)
    {
      double dist = BRep_Tool::Pnt(aV1).Distance(BRep_Tool::Pnt(aV2));
      if (dist < tolMax || delta < Precision::PConfusion())
      {

        TopOpeBRepDS_Kind IntType1 = aPave1->InterferenceType();
        bool              Int3d1   = (IntType1 == TopOpeBRepDS_FACE);
        bool              HasSDV1  = myDataStructure->HasSameDomain(aV1);
        bool              HasSDV2  = myDataStructure->HasSameDomain(aV2);
        bool              UsedV1   = theUsedVertexMap.Contains(aV1);
        bool              UsedV2   = theUsedVertexMap.Contains(aV2);

        bool takeFirst = true;
        if (HasSDV1)
          ;
        else if (HasSDV2)
          takeFirst = false;
        else if (UsedV1)
          ;
        else if (UsedV2)
          takeFirst = false;
        else if (Int3d1)
          ;
        else
          takeFirst = false;
        TopoDS_Shape       aVer;
        bool               HasSDV;
        TopAbs_Orientation anOriOpp;
        if (takeFirst)
        {
          aPVSlist.Append(aPave1);
          aVer     = aV1;
          HasSDV   = HasSDV1;
          anOriOpp = aV2.Orientation();
        }
        else
        {
          aPVSlist.Append(aPave2);
          aVer     = aV2;
          HasSDV   = HasSDV2;
          anOriOpp = aV1.Orientation();
        }

        if (aV1.Orientation() != aV2.Orientation())
        {

          NCollection_List<int> thelist;
          if (!aVerOriMap.IsBound(aVer))
            aVerOriMap.Bind(aVer, thelist);
          NCollection_List<int>& anOriList = aVerOriMap(aVer);
          anOriList.Append(takeFirst);
          anOriList.Append(anOriOpp);

          if (HasSDV)
          {
            int iref = myDataStructure->SameDomainReference(aVer);
            aVer     = myDataStructure->Shape(iref);
          }
          theUnkStateVer.Add(aVer);
        }

        PVS.NextLoop();
        continue;
      }
    }
    aPVSlist.Append(aPave1);
  }

  NCollection_List<occ::handle<TopOpeBRepBuild_Pave>>::Iterator aPVSit(aPVSlist);
  while (aPVSit.More())
  {
    occ::handle<TopOpeBRepBuild_Pave> aPave1 = aPVSit.Value();
    TopoDS_Shape                      aV1    = aPave1->Vertex();
    aV1.Orientation(TopAbs_FORWARD);
    aPar1 = aPave1->Parameter();
    anOr1 = (aPave1->Vertex()).Orientation();
    if (aVerOriMap.IsBound(aV1))
    {

      NCollection_List<int>& anOriList = aVerOriMap(aV1);
      if (!anOriList.IsEmpty())
      {
        if (anOriList.First())
        {
          NCollection_List<int>::Iterator it(anOriList);
          it.Next();
          anOr1 = (TopAbs_Orientation)it.Value();
        }
        anOriList.RemoveFirst();
        anOriList.RemoveFirst();
      }
    }

    aPVSit.Next();

    if (!aPVSit.More())
      break;

    occ::handle<TopOpeBRepBuild_Pave> aPave2 = aPVSit.Value();
    TopoDS_Shape                      aV2    = aPave2->Vertex();
    aV2.Orientation(TopAbs_REVERSED);
    aPar2 = aPave2->Parameter();
    anOr2 = (aPave2->Vertex()).Orientation();
    if (aVerOriMap.IsBound(aV2))
    {
      NCollection_List<int>& anOriList = aVerOriMap(aV2);
      if (!anOriList.IsEmpty())
      {
        if (!anOriList.First())
        {
          NCollection_List<int>::Iterator it(anOriList);
          it.Next();
          anOr2 = (TopAbs_Orientation)it.Value();
        }
      }
    }

    if (aPar1 > aPar2)
      continue;

    bool HasSDV1 = myDataStructure->HasSameDomain(aV1);
    bool HasSDV2 = myDataStructure->HasSameDomain(aV2);
    if (HasSDV1)
    {
      int iref = myDataStructure->SameDomainReference(aV1);
      aV1      = myDataStructure->Shape(iref);
      aV1.Orientation(TopAbs_FORWARD);
    }

    if (HasSDV2)
    {
      int iref = myDataStructure->SameDomainReference(aV2);
      aV2      = myDataStructure->Shape(iref);
      aV2.Orientation(TopAbs_REVERSED);
    }

    TopoDS_Edge aNewEdge;
    myBuildTool.CopyEdge(EdgeF, aNewEdge);

    myBuildTool.AddEdgeVertex(aNewEdge, aV1);
    myBuildTool.Parameter(aNewEdge, aV1, aPar1);

    myBuildTool.AddEdgeVertex(aNewEdge, aV2);
    myBuildTool.Parameter(aNewEdge, aV2, aPar2);

    TopAbs_State aState = TopAbs_IN;

    if (anOr1 == TopAbs_FORWARD && anOr2 == TopAbs_REVERSED)
      aState = TopAbs_OUT;
    if (anOr1 == TopAbs_FORWARD && anOr2 == TopAbs_INTERNAL)
      aState = TopAbs_OUT;
    if (anOr1 == TopAbs_INTERNAL && anOr2 == TopAbs_REVERSED)
      aState = TopAbs_OUT;

    if (anOr1 == TopAbs_INTERNAL && anOr2 == TopAbs_INTERNAL)
      aState = TopAbs_OUT;

    aNewEdge.Orientation(anEdge.Orientation());
    aLNew.Append(aNewEdge);
    aDataMapOfShapeState.Bind(aNewEdge, aState);
  }
}

static TopAbs_State ClassifyEdgeToSolidByOnePoint(const TopoDS_Edge&              E,
                                                  TopOpeBRepTool_ShapeClassifier& SC)
{
  double f2 = 0., l2 = 0., par = 0.;

  occ::handle<Geom_Curve> C3D = BRep_Tool::Curve(E, f2, l2);
  gp_Pnt                  aP3d;

  if (C3D.IsNull())
  {

    const TopoDS_Vertex& fv = TopExp::FirstVertex(E);
    if (fv.IsNull())
      return TopAbs_UNKNOWN;
    aP3d = BRep_Tool::Pnt(fv);
  }
  else
  {
    par = f2 * PAR_T + (1 - PAR_T) * l2;
    C3D->D0(par, aP3d);
  }

  SC.StateP3DReference(aP3d);

  return SC.State();
}
