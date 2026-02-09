#include <BRepBuilderAPI_MakeVertex.hpp>
#include <gp_Pnt.hpp>
#include <TopoDS_Vertex.hpp>

BRepBuilderAPI_MakeVertex::BRepBuilderAPI_MakeVertex(const gp_Pnt& P)
    : myMakeVertex(P)
{
  if (myMakeVertex.IsDone())
  {
    Done();
    myShape = myMakeVertex.Shape();
  }
}

const TopoDS_Vertex& BRepBuilderAPI_MakeVertex::Vertex()
{
  return myMakeVertex.Vertex();
}

BRepBuilderAPI_MakeVertex::operator TopoDS_Vertex()
{
  return Vertex();
}
