#include <BRep_Builder.hpp>
#include <BRepLib.hpp>
#include <BRepLib_MakeVertex.hpp>
#include <gp_Pnt.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Vertex.hpp>

BRepLib_MakeVertex::BRepLib_MakeVertex(const gp_Pnt& P)
{
  BRep_Builder B;
  B.MakeVertex(TopoDS::Vertex(myShape), P, BRepLib::Precision());
  Done();
}

const TopoDS_Vertex& BRepLib_MakeVertex::Vertex()
{
  return TopoDS::Vertex(Shape());
}

BRepLib_MakeVertex::operator TopoDS_Vertex()
{
  return Vertex();
}
