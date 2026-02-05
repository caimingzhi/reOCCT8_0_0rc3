#include <ChFi2d.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

//=================================================================================================

bool ChFi2d::CommonVertex(const TopoDS_Edge& E1, const TopoDS_Edge& E2, TopoDS_Vertex& V)
{
  TopoDS_Vertex firstVertex1, lastVertex1, firstVertex2, lastVertex2;
  TopExp::Vertices(E1, firstVertex1, lastVertex1);
  TopExp::Vertices(E2, firstVertex2, lastVertex2);

  if (firstVertex1.IsSame(firstVertex2) || firstVertex1.IsSame(lastVertex2))
  {
    V = firstVertex1;
    return true;
  }
  if (lastVertex1.IsSame(firstVertex2) || lastVertex1.IsSame(lastVertex2))
  {
    V = lastVertex1;
    return true;
  }
  return false;
} // CommonVertex

//=================================================================================================

ChFi2d_ConstructionError ChFi2d::FindConnectedEdges(const TopoDS_Face&   F,
                                                    const TopoDS_Vertex& V,
                                                    TopoDS_Edge&         E1,
                                                    TopoDS_Edge&         E2)
{
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    vertexMap;
  TopExp::MapShapesAndAncestors(F, TopAbs_VERTEX, TopAbs_EDGE, vertexMap);

  if (vertexMap.Contains(V))
  {
    NCollection_List<TopoDS_Shape>::Iterator iterator(vertexMap.FindFromKey(V));
    if (iterator.More())
    {
      E1 = TopoDS::Edge(iterator.Value());
      iterator.Next();
    } // if ...
    else
      return ChFi2d_ConnexionError;
    if (iterator.More())
    {
      E2 = TopoDS::Edge(iterator.Value());
      iterator.Next();
    } // if ...
    else
      return ChFi2d_ConnexionError;

    if (iterator.More())
      return ChFi2d_ConnexionError;
  } // if (isFind)
  else
    return ChFi2d_ConnexionError;
  return ChFi2d_IsDone;
} // FindConnectedEdges
