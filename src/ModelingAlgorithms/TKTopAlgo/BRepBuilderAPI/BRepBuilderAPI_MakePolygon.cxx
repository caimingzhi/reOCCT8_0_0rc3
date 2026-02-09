#include <BRepBuilderAPI_MakePolygon.hpp>
#include <gp_Pnt.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

BRepBuilderAPI_MakePolygon::BRepBuilderAPI_MakePolygon() = default;

BRepBuilderAPI_MakePolygon::BRepBuilderAPI_MakePolygon(const gp_Pnt& P1, const gp_Pnt& P2)
    : myMakePolygon(P1, P2)
{
  if (myMakePolygon.IsDone())
  {
    Done();
    myShape = myMakePolygon.Shape();
  }
}

BRepBuilderAPI_MakePolygon::BRepBuilderAPI_MakePolygon(const gp_Pnt& P1,
                                                       const gp_Pnt& P2,
                                                       const gp_Pnt& P3,
                                                       const bool    Cl)
    : myMakePolygon(P1, P2, P3, Cl)
{
  if (myMakePolygon.IsDone())
  {
    Done();
    myShape = myMakePolygon.Shape();
  }
}

BRepBuilderAPI_MakePolygon::BRepBuilderAPI_MakePolygon(const gp_Pnt& P1,
                                                       const gp_Pnt& P2,
                                                       const gp_Pnt& P3,
                                                       const gp_Pnt& P4,
                                                       const bool    Cl)
    : myMakePolygon(P1, P2, P3, P4, Cl)
{
  if (myMakePolygon.IsDone())
  {
    Done();
    myShape = myMakePolygon.Shape();
  }
}

BRepBuilderAPI_MakePolygon::BRepBuilderAPI_MakePolygon(const TopoDS_Vertex& V1,
                                                       const TopoDS_Vertex& V2)
    : myMakePolygon(V1, V2)
{
  if (myMakePolygon.IsDone())
  {
    Done();
    myShape = myMakePolygon.Shape();
  }
}

BRepBuilderAPI_MakePolygon::BRepBuilderAPI_MakePolygon(const TopoDS_Vertex& V1,
                                                       const TopoDS_Vertex& V2,
                                                       const TopoDS_Vertex& V3,
                                                       const bool           Cl)
    : myMakePolygon(V1, V2, V3, Cl)
{
  if (myMakePolygon.IsDone())
  {
    Done();
    myShape = myMakePolygon.Shape();
  }
}

BRepBuilderAPI_MakePolygon::BRepBuilderAPI_MakePolygon(const TopoDS_Vertex& V1,
                                                       const TopoDS_Vertex& V2,
                                                       const TopoDS_Vertex& V3,
                                                       const TopoDS_Vertex& V4,
                                                       const bool           Cl)
    : myMakePolygon(V1, V2, V3, V4, Cl)
{
  if (myMakePolygon.IsDone())
  {
    Done();
    myShape = myMakePolygon.Shape();
  }
}

void BRepBuilderAPI_MakePolygon::Add(const gp_Pnt& P)
{
  myMakePolygon.Add(P);
  if (myMakePolygon.IsDone())
  {
    Done();
    if (!LastVertex().IsNull())
      myShape = myMakePolygon.Shape();
  }
}

void BRepBuilderAPI_MakePolygon::Add(const TopoDS_Vertex& V)
{
  myMakePolygon.Add(V);
  if (myMakePolygon.IsDone())
  {
    Done();
    myShape = myMakePolygon.Shape();
  }
}

bool BRepBuilderAPI_MakePolygon::Added() const
{
  return myMakePolygon.Added();
}

void BRepBuilderAPI_MakePolygon::Close()
{
  myMakePolygon.Close();
  myShape = myMakePolygon.Shape();
}

const TopoDS_Vertex& BRepBuilderAPI_MakePolygon::FirstVertex() const
{
  return myMakePolygon.FirstVertex();
}

const TopoDS_Vertex& BRepBuilderAPI_MakePolygon::LastVertex() const
{
  return myMakePolygon.LastVertex();
}

bool BRepBuilderAPI_MakePolygon::IsDone() const
{
  return myMakePolygon.IsDone();
}

const TopoDS_Edge& BRepBuilderAPI_MakePolygon::Edge() const
{
  return myMakePolygon.Edge();
}

const TopoDS_Wire& BRepBuilderAPI_MakePolygon::Wire()
{
  return myMakePolygon.Wire();
}

BRepBuilderAPI_MakePolygon::operator TopoDS_Edge() const
{
  return Edge();
}

BRepBuilderAPI_MakePolygon::operator TopoDS_Wire()
{
  return Wire();
}
