#include <BRepFill_OffsetAncestors.hpp>
#include <BRepFill_OffsetWire.hpp>
#include <StdFail_NotDone.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>

BRepFill_OffsetAncestors::BRepFill_OffsetAncestors()
    : myIsPerform(false)
{
}

BRepFill_OffsetAncestors::BRepFill_OffsetAncestors(BRepFill_OffsetWire& Paral)
{
  Perform(Paral);
}

void BRepFill_OffsetAncestors::Perform(BRepFill_OffsetWire& Paral)
{
  TopoDS_Face Spine = Paral.Spine();

  TopExp_Explorer                          Exp;
  NCollection_List<TopoDS_Shape>::Iterator it;

  for (Exp.Init(Spine, TopAbs_EDGE); Exp.More(); Exp.Next())
  {
    for (it.Initialize(Paral.GeneratedShapes(Exp.Current())); it.More(); it.Next())
    {
      myMap.Bind(it.Value(), Exp.Current());
    }
  }

  for (Exp.Init(Spine, TopAbs_VERTEX); Exp.More(); Exp.Next())
  {
    for (it.Initialize(Paral.GeneratedShapes(Exp.Current())); it.More(); it.Next())
    {
      myMap.Bind(it.Value(), Exp.Current());
    }
  }

  myIsPerform = true;
}

bool BRepFill_OffsetAncestors::IsDone() const
{
  return myIsPerform;
}

bool BRepFill_OffsetAncestors::HasAncestor(const TopoDS_Edge& S1) const
{
  return myMap.IsBound(S1);
}

const TopoDS_Shape& BRepFill_OffsetAncestors::Ancestor(const TopoDS_Edge& S1) const
{
  StdFail_NotDone_Raise_if(
    !myIsPerform,
    "BRepFill_OffsetAncestors::Ancestor() - Perform() should be called before accessing results");
  return myMap(S1);
}
