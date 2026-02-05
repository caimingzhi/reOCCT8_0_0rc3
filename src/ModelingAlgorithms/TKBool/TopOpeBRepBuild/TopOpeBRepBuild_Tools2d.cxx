#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Wire.hpp>
#include <TopOpeBRepBuild_Tools2d.hpp>
#include <TopOpeBRepBuild_VertexInfo.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

#include <cstdio>
static void BuildPath(
  const TopoDS_Vertex& myVertex0,
  const TopoDS_Edge&   myEdge,
  const TopoDS_Vertex& myVertex,
  const int            aNbEdges,
  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepBuild_VertexInfo, TopTools_ShapeMapHasher>& M,
  int                             anEdgesCount,
  int&                            aBreakFlag,
  NCollection_List<TopoDS_Shape>& myResList);

//=================================================================================================

void TopOpeBRepBuild_Tools2d::Path(const TopoDS_Wire&              aWire,
                                   NCollection_List<TopoDS_Shape>& aResList)
{
  int                            anEdgesCount = 0, aNbEdges = 0, aBreakFlag = 0;
  NCollection_List<TopoDS_Shape> myResList;
  TopoDS_Vertex                  myVertex, myVertex0;
  TopoDS_Edge                    myEdge, aNullEdge;

  TopExp_Explorer ex(aWire, TopAbs_EDGE);
  for (; ex.More(); ex.Next())
    aNbEdges++;

  myResList.Clear();

  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepBuild_VertexInfo, TopTools_ShapeMapHasher> M;
  TopOpeBRepBuild_Tools2d::MakeMapOfShapeVertexInfo(aWire, M);

  myEdge    = aNullEdge;
  myVertex0 = TopoDS::Vertex(M.FindKey(1));
  myVertex  = myVertex0;

  BuildPath(myVertex0, myEdge, myVertex, aNbEdges, M, anEdgesCount, aBreakFlag, myResList);
  //
  aResList.Clear();
  aResList = myResList;
}

//=================================================================================================

void BuildPath(
  const TopoDS_Vertex& myVertex0,
  const TopoDS_Edge&   myInputEdge,
  const TopoDS_Vertex& myInputVertex,
  const int            aNbEdges,
  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepBuild_VertexInfo, TopTools_ShapeMapHasher>& M,
  int                             anEdgesCount,
  int&                            aBreakFlag,
  NCollection_List<TopoDS_Shape>& myResList)
{
  int           j = 1, aFoundOut, aNbCases, stopFlag = 0;
  TopoDS_Edge   myEdge;
  TopoDS_Vertex myVertex;

  if (aBreakFlag == 1)
    return;

  TopOpeBRepBuild_VertexInfo& aVInfo = M.ChangeFromKey(myInputVertex);
  //
  aVInfo.SetCurrentIn(myInputEdge);
  aVInfo.Prepare(myResList);
  aNbCases = aVInfo.NbCases();
  if (!aNbCases)
    aBreakFlag = 2;

  for (j = 1; j <= aNbCases; j++)
  {

    myEdge = aVInfo.CurrentOut();

    aFoundOut = aVInfo.FoundOut();
    if (!aFoundOut)
    { // FondOut=0 TUPICK
      aBreakFlag = 2;
      return;
    }

    else
    {
      if (stopFlag)
      { // if previous path was wrong
        aVInfo.RemovePassed();
        myResList.RemoveFirst();
        stopFlag = 0;
        anEdgesCount--;
      }

      aVInfo.AppendPassed(myEdge);
      myResList.Prepend(myEdge);
      anEdgesCount++;
      myVertex = (myEdge.Orientation() == TopAbs_FORWARD) ? TopExp::LastVertex(myEdge)
                                                          : TopExp::FirstVertex(myEdge);

      if (myVertex.IsSame(myVertex0) && anEdgesCount == aNbEdges)
      {
        aBreakFlag = 1;
        return;
      }

      BuildPath(myVertex0, myEdge, myVertex, aNbEdges, M, anEdgesCount, aBreakFlag, myResList);
      ////
      if (aBreakFlag == 1)
      {
        return;
      }

      if (aBreakFlag == 2)
      { // Come back
        if (j == aNbCases)
        {
          aVInfo.RemovePassed();
          myResList.RemoveFirst();
          anEdgesCount--;
          ////
          return;
        }
        else
        {
          stopFlag   = 1;
          aBreakFlag = 0; // Next j if possible
        }
      } // end of if (aBreakFlag==2)
    } // end of else .i.e. aFoundOut#0
  } // end of for (j=1; j<=aNbCases; j++)
}

//=================================================================================================

void TopOpeBRepBuild_Tools2d::MakeMapOfShapeVertexInfo(
  const TopoDS_Wire& aWire,
  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepBuild_VertexInfo, TopTools_ShapeMapHasher>& M)
{
  TopOpeBRepBuild_VertexInfo empty;
  TopExp_Explorer            exa(aWire, TopAbs_EDGE);
  for (; exa.More(); exa.Next())
  {
    const TopoDS_Edge& anEdge = TopoDS::Edge(exa.Current());
    TopExp_Explorer    exs(anEdge, TopAbs_VERTEX);
    for (; exs.More(); exs.Next())
    {
      const TopoDS_Vertex& aVertex = TopoDS::Vertex(exs.Current());
      int                  index   = M.FindIndex(aVertex);
      if (!index)
        index = M.Add(aVertex, empty);

      TopOpeBRepBuild_VertexInfo& aVInfo = M(index);
      aVInfo.SetVertex(aVertex);
      TopAbs_Orientation anOr = aVertex.Orientation();
      if (anOr == TopAbs_FORWARD)
        aVInfo.AddOut(anEdge);
      else if (anOr == TopAbs_REVERSED)
        aVInfo.AddIn(anEdge);
    }
  }

  int i, aNb;
  aNb = M.Extent();
  for (i = 1; i <= aNb; i++)
  {
    TopOpeBRepBuild_VertexInfo&                 aVInfo   = M(i);
    const NCollection_IndexedMap<TopoDS_Shape>& EdgesIn  = aVInfo.EdgesIn();
    const NCollection_IndexedMap<TopoDS_Shape>& EdgesOut = aVInfo.EdgesOut();
    int                                         aNbEdgesIn, aNbEdgesOut;
    aNbEdgesIn  = EdgesIn.Extent();
    aNbEdgesOut = EdgesOut.Extent();
    if (aNbEdgesIn != 1 && aNbEdgesOut != 1)
    {
      aVInfo.SetSmart(true);
    }
  }
}

//=================================================================================================

void TopOpeBRepBuild_Tools2d::DumpMapOfShapeVertexInfo(
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   TopOpeBRepBuild_VertexInfo,
                                   TopTools_ShapeMapHasher>& M)
{
  int i, aNb;
  aNb = M.Extent();
  for (i = 1; i <= aNb; i++)
  {
    const TopOpeBRepBuild_VertexInfo& aVInfo = M(i);

    printf(" Vert.#%d, ", i);
    const NCollection_List<TopoDS_Shape>& aList = aVInfo.ListPassed();

    if (aList.Extent())
    {
      NCollection_List<TopoDS_Shape>::Iterator anIt(aList);
      for (; anIt.More(); anIt.Next())
      {
        printf("pass,");
      }
    }

    else
    {
      printf("none");
    }
    printf("\n");
  }
}
