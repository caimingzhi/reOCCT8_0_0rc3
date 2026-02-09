#include <BRep_Builder.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <BRepLib_MakePolygon.hpp>
#include <BRepTools.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <StdFail_NotDone.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

BRepLib_MakePolygon::BRepLib_MakePolygon() = default;

BRepLib_MakePolygon::BRepLib_MakePolygon(const gp_Pnt& P1, const gp_Pnt& P2)
{
  Add(P1);
  Add(P2);
}

BRepLib_MakePolygon::BRepLib_MakePolygon(const gp_Pnt& P1,
                                         const gp_Pnt& P2,
                                         const gp_Pnt& P3,
                                         const bool    Cl)
{
  Add(P1);
  Add(P2);
  Add(P3);
  if (Cl)
    Close();
}

BRepLib_MakePolygon::BRepLib_MakePolygon(const gp_Pnt& P1,
                                         const gp_Pnt& P2,
                                         const gp_Pnt& P3,
                                         const gp_Pnt& P4,
                                         const bool    Cl)
{
  Add(P1);
  Add(P2);
  Add(P3);
  Add(P4);
  if (Cl)
    Close();
}

BRepLib_MakePolygon::BRepLib_MakePolygon(const TopoDS_Vertex& V1, const TopoDS_Vertex& V2)
{
  Add(V1);
  Add(V2);
}

BRepLib_MakePolygon::BRepLib_MakePolygon(const TopoDS_Vertex& V1,
                                         const TopoDS_Vertex& V2,
                                         const TopoDS_Vertex& V3,
                                         const bool           Cl)
{
  Add(V1);
  Add(V2);
  Add(V3);
  if (Cl)
    Close();
}

BRepLib_MakePolygon::BRepLib_MakePolygon(const TopoDS_Vertex& V1,
                                         const TopoDS_Vertex& V2,
                                         const TopoDS_Vertex& V3,
                                         const TopoDS_Vertex& V4,
                                         const bool           Cl)
{
  Add(V1);
  Add(V2);
  Add(V3);
  Add(V4);
  if (Cl)
    Close();
}

void BRepLib_MakePolygon::Add(const gp_Pnt& P)
{
  BRep_Builder  B;
  TopoDS_Vertex V;
  B.MakeVertex(V, P, Precision::Confusion());
  Add(V);
}

void BRepLib_MakePolygon::Add(const TopoDS_Vertex& V)
{
  if (myFirstVertex.IsNull())
  {
    myFirstVertex = V;
  }
  else
  {
    myEdge.Nullify();
    BRep_Builder  B;
    TopoDS_Vertex last;

    bool second = myLastVertex.IsNull();
    if (second)
    {
      last         = myFirstVertex;
      myLastVertex = V;
      B.MakeWire(TopoDS::Wire(myShape));
      myShape.Closed(false);
      myShape.Orientable(true);
    }
    else
    {
      last = myLastVertex;
      if (BRepTools::Compare(V, myFirstVertex))
      {
        myLastVertex = myFirstVertex;
        myShape.Closed(true);
      }
      else
        myLastVertex = V;
    }

    BRepLib_MakeEdge ME(last, myLastVertex);
    if (ME.IsDone())
    {
      myEdge = ME;
      B.Add(myShape, myEdge);
      Done();
    }
    else
    {

      if (second)
        myLastVertex.Nullify();
      else
        myLastVertex = last;
    }
  }
}

bool BRepLib_MakePolygon::Added() const
{
  return !myEdge.IsNull();
}

void BRepLib_MakePolygon::Close()
{
  if (myFirstVertex.IsNull() || myLastVertex.IsNull())
    return;

  if (myShape.Closed())
    return;

  BRep_Builder B;
  myEdge.Nullify();
  BRepLib_MakeEdge ME(myLastVertex, myFirstVertex);
  if (ME.IsDone())
  {
    myEdge = ME;
    B.Add(myShape, myEdge);
    myShape.Closed(true);
  }
}

const TopoDS_Vertex& BRepLib_MakePolygon::FirstVertex() const
{
  return myFirstVertex;
}

const TopoDS_Vertex& BRepLib_MakePolygon::LastVertex() const
{
  return myLastVertex;
}

const TopoDS_Edge& BRepLib_MakePolygon::Edge() const
{
  return myEdge;
}

const TopoDS_Wire& BRepLib_MakePolygon::Wire()
{
  return TopoDS::Wire(Shape());
}

BRepLib_MakePolygon::operator TopoDS_Edge() const
{
  return Edge();
}

BRepLib_MakePolygon::operator TopoDS_Wire()
{
  return Wire();
}
