#include <BRepBuilderAPI_MakeWire.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

//=================================================================================================

BRepBuilderAPI_MakeWire::BRepBuilderAPI_MakeWire() = default;

//=================================================================================================

BRepBuilderAPI_MakeWire::BRepBuilderAPI_MakeWire(const TopoDS_Edge& E)
    : myMakeWire(E)
{
  if (myMakeWire.IsDone())
  {
    Done();
    myShape = myMakeWire.Wire();
  }
}

//=================================================================================================

BRepBuilderAPI_MakeWire::BRepBuilderAPI_MakeWire(const TopoDS_Edge& E1, const TopoDS_Edge& E2)
    : myMakeWire(E1, E2)
{
  if (myMakeWire.IsDone())
  {
    Done();
    myShape = myMakeWire.Wire();
  }
}

//=================================================================================================

BRepBuilderAPI_MakeWire::BRepBuilderAPI_MakeWire(const TopoDS_Edge& E1,
                                                 const TopoDS_Edge& E2,
                                                 const TopoDS_Edge& E3)
    : myMakeWire(E1, E2, E3)
{
  if (myMakeWire.IsDone())
  {
    Done();
    myShape = myMakeWire.Wire();
  }
}

//=================================================================================================

BRepBuilderAPI_MakeWire::BRepBuilderAPI_MakeWire(const TopoDS_Edge& E1,
                                                 const TopoDS_Edge& E2,
                                                 const TopoDS_Edge& E3,
                                                 const TopoDS_Edge& E4)
    : myMakeWire(E1, E2, E3, E4)
{
  if (myMakeWire.IsDone())
  {
    Done();
    myShape = myMakeWire.Wire();
  }
}

//=================================================================================================

BRepBuilderAPI_MakeWire::BRepBuilderAPI_MakeWire(const TopoDS_Wire& W)
    : myMakeWire(W)
{
  if (myMakeWire.IsDone())
  {
    Done();
    myShape = myMakeWire.Wire();
  }
}

//=================================================================================================

BRepBuilderAPI_MakeWire::BRepBuilderAPI_MakeWire(const TopoDS_Wire& W, const TopoDS_Edge& E)
    : myMakeWire(W, E)
{
  if (myMakeWire.IsDone())
  {
    Done();
    myShape = myMakeWire.Wire();
  }
}

//=================================================================================================

void BRepBuilderAPI_MakeWire::Add(const TopoDS_Wire& W)
{
  myMakeWire.Add(W);
  if (myMakeWire.IsDone())
  {
    Done();
    myShape = myMakeWire.Wire();
  }
}

//=================================================================================================

void BRepBuilderAPI_MakeWire::Add(const TopoDS_Edge& E)
{
  myMakeWire.Add(E);
  if (myMakeWire.IsDone())
  {
    Done();
    myShape = myMakeWire.Wire();
  }
}

//=================================================================================================

void BRepBuilderAPI_MakeWire::Add(const NCollection_List<TopoDS_Shape>& L)
{
  myMakeWire.Add(L);
  if (myMakeWire.IsDone())
  {
    Done();
    myShape = myMakeWire.Wire();
  }
}

//=================================================================================================

const TopoDS_Wire& BRepBuilderAPI_MakeWire::Wire()
{
  return myMakeWire.Wire();
}

//=================================================================================================

const TopoDS_Edge& BRepBuilderAPI_MakeWire::Edge() const
{
  return myMakeWire.Edge();
}

//=================================================================================================

const TopoDS_Vertex& BRepBuilderAPI_MakeWire::Vertex() const
{
  return myMakeWire.Vertex();
}

//=================================================================================================

BRepBuilderAPI_MakeWire::operator TopoDS_Wire()
{
  return Wire();
}

//=================================================================================================

bool BRepBuilderAPI_MakeWire::IsDone() const
{
  return myMakeWire.IsDone();
}

//=================================================================================================

BRepBuilderAPI_WireError BRepBuilderAPI_MakeWire::Error() const
{
  switch (myMakeWire.Error())
  {

    case BRepLib_WireDone:
      return BRepBuilderAPI_WireDone;

    case BRepLib_EmptyWire:
      return BRepBuilderAPI_EmptyWire;

    case BRepLib_DisconnectedWire:
      return BRepBuilderAPI_DisconnectedWire;

    case BRepLib_NonManifoldWire:
      return BRepBuilderAPI_NonManifoldWire;
  }

  // portage WNT
  return BRepBuilderAPI_WireDone;
}
