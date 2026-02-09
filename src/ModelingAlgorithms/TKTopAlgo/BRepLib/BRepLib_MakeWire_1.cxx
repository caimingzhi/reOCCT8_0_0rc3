#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepLib.hpp>
#include <BRepLib_MakeWire.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_UBTreeFiller.hpp>
#include <BRepBndLib.hpp>
#include <BRepLib_MakeVertex.hpp>

void BRepLib_MakeWire::Add(const NCollection_List<TopoDS_Shape>& L)
{
  myError      = BRepLib_WireDone;
  int aLSize   = 0;
  int aRefSize = L.Size();
  if (!L.IsEmpty())
  {

    NCollection_List<NCollection_List<TopoDS_Vertex>> aGrVL;

    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>
      aMapVE;

    CollectCoincidentVertices(L, aGrVL);

    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> anO2NV;

    CreateNewVertices(aGrVL, anO2NV);

    NCollection_List<TopoDS_Shape> aNewEList;

    CreateNewListOfEdges(L, anO2NV, aNewEList);

    TopExp::MapShapesAndAncestors(myShape, TopAbs_VERTEX, TopAbs_EDGE, aMapVE);

    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aProcessedEdges;
    TopExp_Explorer                                        anExp;

    NCollection_List<TopoDS_Shape> anActEdges, aNeighEdges;

    if (myEdge.IsNull())
    {

      const TopoDS_Edge& aFE = TopoDS::Edge(aNewEList.First());
      Add(aFE);
      aProcessedEdges.Add(aFE);
      anActEdges.Append(aFE);
      aLSize++;
    }
    else
    {

      for (anExp.Init(myShape, TopAbs_EDGE); anExp.More(); anExp.Next())
      {
        const TopoDS_Shape& aCSh = anExp.Current();
        aProcessedEdges.Add(aCSh);
        anActEdges.Append(aCSh);
      }
    }

    NCollection_List<TopoDS_Shape>::Iterator anItL1, anItL2;

    for (anItL1.Initialize(aNewEList); anItL1.More(); anItL1.Next())
      TopExp::MapShapesAndAncestors(anItL1.Value(), TopAbs_VERTEX, TopAbs_EDGE, aMapVE);

    while (!anActEdges.IsEmpty())
    {
      anItL2.Initialize(anActEdges);
      for (; anItL2.More(); anItL2.Next())
      {
        const TopoDS_Shape& aCE = anItL2.Value();
        anExp.Init(aCE, TopAbs_VERTEX);
        for (; anExp.More(); anExp.Next())
        {
          const TopoDS_Shape& aCV = anExp.Current();
          for (anItL1.Initialize(aMapVE.FindFromKey(aCV)); anItL1.More(); anItL1.Next())
          {
            const TopoDS_Shape& aNE = anItL1.Value();
            if (!aProcessedEdges.Contains(aNE))
            {
              Add(TopoDS::Edge(aNE), false);
              aNeighEdges.Append(aNE);
              aProcessedEdges.Add(aNE);
              aLSize++;
            }
          }
        }
      }
      anActEdges.Clear();
      anActEdges.Append(aNeighEdges);
    }
  }
  if (aLSize == aRefSize)
    Done();
  else
  {
    NotDone();
    myError = BRepLib_DisconnectedWire;
  }
}

bool BRepLib_MakeWire::BRepLib_BndBoxVertexSelector::Accept(const int& theObj)
{
  if (theObj > myMapOfShape.Extent())
    return false;

  const TopoDS_Vertex& aV = TopoDS::Vertex(myMapOfShape(theObj));

  if (theObj == myVInd)
    return false;

  gp_Pnt aVPnt = BRep_Tool::Pnt(aV);

  double aTolV = BRep_Tool::Tolerance(aV);

  double aL    = myP.SquareDistance(aVPnt);
  double aSTol = aTolV + myTolP;
  aSTol *= aSTol;

  if (aL <= aSTol)
  {
    myResultInd.Append(theObj);
    return true;
  }

  return false;
}

void BRepLib_MakeWire::BRepLib_BndBoxVertexSelector::SetCurrentVertex(const gp_Pnt& theP,
                                                                      double        theTol,
                                                                      int           theVInd)
{
  myP = theP;
  myVBox.Add(myP);
  myVBox.Enlarge(theTol);
  myTolP = theTol;
  myVInd = theVInd;
}

void BRepLib_MakeWire::CollectCoincidentVertices(
  const NCollection_List<TopoDS_Shape>&              theL,
  NCollection_List<NCollection_List<TopoDS_Vertex>>& theGrVL)
{
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> anAllV;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aMV2EL;

  TopExp::MapShapes(myShape, TopAbs_VERTEX, anAllV);

  NCollection_List<TopoDS_Shape>::Iterator anItL(theL);
  for (; anItL.More(); anItL.Next())
    TopExp::MapShapes(anItL.Value(), TopAbs_VERTEX, anAllV);

  NCollection_DataMap<TopoDS_Vertex, NCollection_Map<TopoDS_Vertex>> aV2CV;
  NCollection_UBTree<int, Bnd_Box>                                   aTree;
  NCollection_UBTreeFiller<int, Bnd_Box>                             aTreeFiller(aTree);
  NCollection_Map<TopoDS_Vertex>                                     aNonGroupedV;

  for (int i = 1; i <= anAllV.Extent(); i++)
  {
    const TopoDS_Shape& aSh = anAllV(i);
    Bnd_Box             aBB;
    BRepBndLib::Add(aSh, aBB);
    aTreeFiller.Add(i, aBB);
  }

  aTreeFiller.Fill();
  BRepLib_BndBoxVertexSelector aSelector(anAllV);

  int                             aNbColl = 0;
  NCollection_List<int>::Iterator itI;
  for (int i = 1; i <= anAllV.Extent(); i++)
  {
    const TopoDS_Vertex& aV = TopoDS::Vertex(anAllV(i));
    if (myVertices.Contains(aV))
      continue;
    aSelector.SetCurrentVertex(BRep_Tool::Pnt(aV), BRep_Tool::Tolerance(aV), i);
    aNbColl = aTree.Select(aSelector);
    if (aNbColl > 0)
    {
      const NCollection_List<int>&    aResInds = aSelector.GetResultInds();
      NCollection_Map<TopoDS_Vertex>* aVM      = aV2CV.Bound(aV, NCollection_Map<TopoDS_Vertex>());
      for (itI.Initialize(aResInds); itI.More(); itI.Next())
      {
        const TopoDS_Vertex& aCV = TopoDS::Vertex(anAllV(itI.Value()));
        aVM->Add(aCV);
        if (myVertices.Contains(aCV))
        {
          if (aV2CV.IsBound(aCV))
            aV2CV(aCV).Add(aV);
          else
          {
            aV2CV.Bound(aCV, NCollection_Map<TopoDS_Vertex>())->Add(aV);
            aNonGroupedV.Add(aCV);
          }
        }
      }
      if (!aVM->IsEmpty())
        aNonGroupedV.Add(aV);
    }
    aSelector.ClearResInds();
  }

  NCollection_Map<TopoDS_Vertex>::Iterator  itMV;
  NCollection_List<TopoDS_Vertex>           aStartV, aCurrentV, anOneGrV;
  NCollection_List<TopoDS_Vertex>::Iterator itLV;
  bool                                      IsStartNewGroup = true;
  while (!aNonGroupedV.IsEmpty() || !IsStartNewGroup)

  {
    if (IsStartNewGroup)
    {

      itMV.Initialize(aNonGroupedV);
      const TopoDS_Vertex& aCurV = itMV.Value();
      aStartV.Append(aCurV);
      aNonGroupedV.Remove(aCurV);
    }
    itLV.Init(aStartV);
    for (; itLV.More(); itLV.Next())
    {
      const TopoDS_Vertex& aSV = itLV.Value();
      anOneGrV.Append(aSV);
      itMV.Initialize(aV2CV(aSV));
      for (; itMV.More(); itMV.Next())
      {
        const TopoDS_Vertex& aCV = itMV.Value();
        if (aNonGroupedV.Contains(aCV))
        {
          aCurrentV.Append(aCV);
          aNonGroupedV.Remove(aCV);
        }
      }
    }
    aStartV.Clear();
    aStartV.Append(aCurrentV);
    IsStartNewGroup = aStartV.IsEmpty();
    if (IsStartNewGroup && !anOneGrV.IsEmpty())
    {
      theGrVL.Append(anOneGrV);
      anOneGrV.Clear();
    }
  }
}

void BRepLib_MakeWire::CreateNewVertices(
  const NCollection_List<NCollection_List<TopoDS_Vertex>>&                  theGrVL,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theO2NV)
{

  NCollection_List<NCollection_List<TopoDS_Vertex>>::Iterator itLLV;
  NCollection_List<TopoDS_Vertex>::Iterator                   itLV;
  BRep_Builder                                                aBB;
  itLLV.Init(theGrVL);
  for (; itLLV.More(); itLLV.Next())
  {
    TopoDS_Vertex                          aNewV;
    NCollection_List<TopoDS_Shape>         aValList;
    const NCollection_List<TopoDS_Vertex>& aVal = itLLV.Value();
    itLV.Initialize(aVal);
    double aNewTol = 0;
    gp_Pnt aNewC;
    for (; itLV.More(); itLV.Next())
    {
      const TopoDS_Vertex& aVV = itLV.Value();
      aValList.Append(aVV);
      if (myVertices.Contains(aVV))
        aNewV = aVV;
    }
    BRepLib::BoundingVertex(aValList, aNewC, aNewTol);

    if (aNewV.IsNull())
    {

      aNewV = BRepLib_MakeVertex(aNewC);
      aBB.UpdateVertex(aNewV, aNewTol);
    }
    else

      aBB.UpdateVertex(aNewV, gp_Pnt(aNewC), aNewTol);

    itLV.Initialize(aVal);
    for (; itLV.More(); itLV.Next())
    {
      const TopoDS_Vertex& aVV = itLV.Value();
      theO2NV.Bind(aVV, aNewV);
    }
  }
}

void BRepLib_MakeWire::CreateNewListOfEdges(
  const NCollection_List<TopoDS_Shape>&                                           theL,
  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theO2NV,
  NCollection_List<TopoDS_Shape>&                                                 theNewEList)
{

  bool                                     IsNewEdge;
  NCollection_List<TopoDS_Vertex>          aVList;
  TopExp_Explorer                          exp;
  BRep_Builder                             aBB;
  NCollection_List<TopoDS_Shape>::Iterator anItL;
  for (anItL.Initialize(theL); anItL.More(); anItL.Next())
  {
    IsNewEdge = false;
    aVList.Clear();
    const TopoDS_Edge& aCE = TopoDS::Edge(anItL.Value());
    exp.Init(aCE, TopAbs_VERTEX);
    for (; exp.More(); exp.Next())
    {
      const TopoDS_Vertex& aVal = TopoDS::Vertex(exp.Current());
      if (theO2NV.IsBound(aVal))
      {
        IsNewEdge = true;

        aVList.Append(TopoDS::Vertex(theO2NV(aVal).Oriented(aVal.Orientation())));
      }
      else
        aVList.Append(aVal);
    }
    if (IsNewEdge)
    {
      TopoDS_Shape                              NewE = aCE.EmptyCopied();
      NCollection_List<TopoDS_Vertex>::Iterator it(aVList);
      for (; it.More(); it.Next())
        aBB.Add(NewE, it.Value());
      theNewEList.Append(TopoDS::Edge(NewE));
    }
    else
      theNewEList.Append(aCE);
  }
}
