#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_HBuilder.hpp>
#include <TopOpeBRepBuild_PaveSet.hpp>
#include <TopOpeBRepBuild_WireEdgeSet.hpp>
#include <TopOpeBRepDS_CurveExplorer.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_List.hpp>

int TopOpeBRepBuild_Builder1::CorrectResult2d(TopoDS_Shape& aResult)

{
  int aNb = myMapOfCorrect2dEdges.Extent();
  if (!aNb)
    return 0;

  if (aResult.ShapeType() != TopAbs_SOLID)
    return 0;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aSourceShapeMap;
  TopExp::MapShapes(myShape1, TopAbs_EDGE, aSourceShapeMap);
  TopExp::MapShapes(myShape2, TopAbs_EDGE, aSourceShapeMap);

  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> EdMap;
  BRep_Builder                                                                    BB;
  TopoDS_Shape aLocalShape = aResult.EmptyCopied();
  TopoDS_Solid aSolid      = TopoDS::Solid(aLocalShape);

  TopExp_Explorer anExpShells(aResult, TopAbs_SHELL);
  for (; anExpShells.More(); anExpShells.Next())
  {
    const TopoDS_Shell& S = TopoDS::Shell(anExpShells.Current());
    aLocalShape           = S.EmptyCopied();
    TopoDS_Shell aShell   = TopoDS::Shell(aLocalShape);

    TopExp_Explorer anExpFaces(S, TopAbs_FACE);
    for (; anExpFaces.More(); anExpFaces.Next())
    {
      TopoDS_Face F = TopoDS::Face(anExpFaces.Current());

      TopAbs_Orientation Fori = F.Orientation();

      aLocalShape       = F.EmptyCopied();
      TopoDS_Face aFace = TopoDS::Face(aLocalShape);

      TopExp_Explorer anExpWires(F, TopAbs_WIRE);
      for (; anExpWires.More(); anExpWires.Next())
      {
        TopoDS_Wire W = TopoDS::Wire(anExpWires.Current());

        TopAbs_Orientation Wori = W.Orientation();

        aLocalShape       = W.EmptyCopied();
        TopoDS_Wire aWire = TopoDS::Wire(aLocalShape);

        TopExp_Explorer anExpEdges(W, TopAbs_EDGE);
        for (; anExpEdges.More(); anExpEdges.Next())
        {
          TopoDS_Edge E = TopoDS::Edge(anExpEdges.Current());

          if (EdMap.Contains(E))
          {
            TopoDS_Shape anEdge = EdMap.ChangeFromKey(E);

            anEdge.Orientation(E.Orientation());
            BB.Add(aWire, anEdge);
            continue;
          }

          if (myMapOfCorrect2dEdges.Contains(E))
          {
            TopoDS_Shape anEdge = myMapOfCorrect2dEdges.ChangeFromKey(E);

            anEdge.Orientation(E.Orientation());
            BB.Add(aWire, anEdge);
            EdMap.Add(E, anEdge);
            continue;
          }

          TopoDS_Edge anEdge;

          if (aSourceShapeMap.Contains(E))
          {
            TopoDS_Shape aLocalShape1 = E.EmptyCopied();
            anEdge                    = TopoDS::Edge(aLocalShape1);

            EdMap.Add(E, anEdge);

            TopExp_Explorer anExpVertices(E, TopAbs_VERTEX);
            bool            free = anEdge.Free();
            anEdge.Free(true);
            for (; anExpVertices.More(); anExpVertices.Next())
              BB.Add(anEdge, anExpVertices.Current());

            anEdge.Free(free);
          }
          else
            anEdge = E;

          anEdge.Orientation(E.Orientation());
          BB.Add(aWire, anEdge);
        }

        aWire.Orientation(Wori);
        aWire.Closed(BRep_Tool::IsClosed(aWire));
        BB.Add(aFace, aWire);
      }

      aFace.Orientation(Fori);
      BB.Add(aShell, aFace);
    }

    aShell.Orientation(S.Orientation());
    aShell.Closed(BRep_Tool::IsClosed(aShell));
    BB.Add(aSolid, aShell);
  }
  aResult = aSolid;

  TopOpeBRepDS_CurveExplorer cex(myDataStructure->DS());
  for (; cex.More(); cex.Next())
  {
    int                                      ic  = cex.Index();
    NCollection_List<TopoDS_Shape>&          LSE = ChangeNewEdges(ic);
    NCollection_List<TopoDS_Shape>           corrLSE;
    NCollection_List<TopoDS_Shape>::Iterator it(LSE);
    for (; it.More(); it.Next())
    {
      const TopoDS_Shape& E = it.Value();
      if (EdMap.Contains(E))
      {
        const TopoDS_Shape& newE = EdMap.FindFromKey(E);
        corrLSE.Append(newE);
      }
      else
        corrLSE.Append(E);
    }
    LSE.Clear();
    LSE.Append(corrLSE);
  }

  const TopOpeBRepDS_DataStructure& BDS = myDataStructure->DS();
  int                               i, nes = BDS.NbSectionEdges();

  for (i = 1; i <= nes; i++)
  {
    const TopoDS_Shape& es = BDS.SectionEdge(i);
    if (es.IsNull())
      continue;

    for (int j = 0; j <= 2; j++)
    {
      TopAbs_State                             staspl = TopAbs_State(j);
      NCollection_List<TopoDS_Shape>&          LSE    = ChangeSplit(es, staspl);
      NCollection_List<TopoDS_Shape>           corrLSE;
      NCollection_List<TopoDS_Shape>::Iterator it(LSE);
      for (; it.More(); it.Next())
      {
        const TopoDS_Shape& E = it.Value();
        if (EdMap.Contains(E))
        {
          const TopoDS_Shape& newE = EdMap.FindFromKey(E);
          corrLSE.Append(newE);
        }
        else
          corrLSE.Append(E);
      }
      LSE.Clear();
      LSE.Append(corrLSE);
    }
  }
  return 1;
}
