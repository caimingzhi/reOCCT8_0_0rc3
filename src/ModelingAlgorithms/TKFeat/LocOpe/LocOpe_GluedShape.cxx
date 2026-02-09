#include <LocOpe_GluedShape.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Type.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Map.hpp>

IMPLEMENT_STANDARD_RTTIEXT(LocOpe_GluedShape, LocOpe_GeneratedShape)

LocOpe_GluedShape::LocOpe_GluedShape() = default;

LocOpe_GluedShape::LocOpe_GluedShape(const TopoDS_Shape& S)
    : myShape(S)
{
}

void LocOpe_GluedShape::Init(const TopoDS_Shape& S)
{
  myShape = S;
  myMap.Clear();
  myGShape.Clear();
  myList.Clear();
  myGEdges.Clear();
}

void LocOpe_GluedShape::GlueOnFace(const TopoDS_Face& F)
{

  TopExp_Explorer exp(myShape, TopAbs_FACE);
  for (; exp.More(); exp.Next())
  {
    if (exp.Current().IsSame(F))
    {
      break;
    }
  }
  if (!exp.More())
  {
    throw Standard_ConstructionError();
  }
  myMap.Add(exp.Current());
}

void LocOpe_GluedShape::MapEdgeAndVertices()
{
  if (!myGShape.IsEmpty())
  {
    return;
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    theMapEF;
  TopExp::MapShapesAndAncestors(myShape, TopAbs_EDGE, TopAbs_FACE, theMapEF);

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>           mapdone;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itm(myMap);
  NCollection_List<TopoDS_Shape>::Iterator                         itl;
  TopExp_Explorer                                                  exp, exp2, exp3;

  for (; itm.More(); itm.Next())
  {
    const TopoDS_Face& fac = TopoDS::Face(itm.Key());
    for (exp.Init(fac, TopAbs_EDGE); exp.More(); exp.Next())
    {
      const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
      if (mapdone.Contains(edg))
      {
        continue;
      }

      if (theMapEF.FindFromKey(edg).Extent() != 2)
      {
        throw Standard_ConstructionError();
      }
      for (itl.Initialize(theMapEF.FindFromKey(edg)); itl.More(); itl.Next())
      {
        if (!myMap.Contains(itl.Value()))
        {
          break;
        }
      }

      if (itl.More())
      {

        myGEdges.Append(edg.Reversed());
        myGShape.Bind(edg, itl.Value());
      }

      mapdone.Add(edg);
    }
  }

  for (itl.Initialize(myGEdges); itl.More(); itl.Next())
  {
    const TopoDS_Edge& edg = TopoDS::Edge(itl.Value());
    for (exp.Init(edg, TopAbs_VERTEX); exp.More(); exp.Next())
    {
      const TopoDS_Vertex& vtx = TopoDS::Vertex(exp.Current());
      if (myGShape.IsBound(vtx))
      {
        continue;
      }
      for (exp2.Init(myGShape(edg), TopAbs_EDGE); exp2.More(); exp2.Next())
      {
        if (exp2.Current().IsSame(edg))
        {
          continue;
        }
        for (exp3.Init(exp2.Current(), TopAbs_VERTEX); exp3.More(); exp3.Next())
        {
          if (exp3.Current().IsSame(vtx))
          {
            if (myGShape.IsBound(exp2.Current()))
            {
              myGShape.Bind(vtx, TopoDS_Edge());
            }
            else
            {
              myGShape.Bind(vtx, exp2.Current());
            }
            break;
          }
        }
        if (exp3.More())
        {
          break;
        }
      }
    }
  }

  for (exp.Init(myShape, TopAbs_FACE); exp.More(); exp.Next())
  {
    if (!myMap.Contains(exp.Current()))
    {
      myList.Append(exp.Current());
    }
  }
}

const NCollection_List<TopoDS_Shape>& LocOpe_GluedShape::GeneratingEdges()
{
  if (myGShape.IsEmpty())
  {
    MapEdgeAndVertices();
  }
  return myGEdges;
}

TopoDS_Edge LocOpe_GluedShape::Generated(const TopoDS_Vertex& V)
{
  if (myGShape.IsEmpty())
  {
    MapEdgeAndVertices();
  }
  return TopoDS::Edge(myGShape(V));
}

TopoDS_Face LocOpe_GluedShape::Generated(const TopoDS_Edge& E)
{
  if (myGShape.IsEmpty())
  {
    MapEdgeAndVertices();
  }
  return TopoDS::Face(myGShape(E));
}

const NCollection_List<TopoDS_Shape>& LocOpe_GluedShape::OrientedFaces()
{
  if (myGShape.IsEmpty())
  {
    MapEdgeAndVertices();
  }
  return myList;
}
