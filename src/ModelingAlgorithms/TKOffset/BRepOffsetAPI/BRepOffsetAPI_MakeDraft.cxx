

#include <BRepOffsetAPI_MakeDraft.hpp>
#include <Geom_Surface.hpp>
#include <gp_Dir.hpp>
#include <StdFail_NotDone.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>

BRepOffsetAPI_MakeDraft::BRepOffsetAPI_MakeDraft(const TopoDS_Shape& Shape,
                                                 const gp_Dir&       Dir,
                                                 const double        Angle)
    : myDraft(Shape, Dir, Angle)
{
  NotDone();
}

void BRepOffsetAPI_MakeDraft::SetOptions(const BRepBuilderAPI_TransitionMode Style,
                                         const double                        AngleMin,
                                         const double                        AngleMax)
{
  BRepFill_TransitionStyle style = BRepFill_Right;
  if (Style == BRepBuilderAPI_RoundCorner)
    style = BRepFill_Round;
  myDraft.SetOptions(style, AngleMin, AngleMax);
}

void BRepOffsetAPI_MakeDraft::SetDraft(const bool IsInternal)
{
  myDraft.SetDraft(IsInternal);
}

void BRepOffsetAPI_MakeDraft::Perform(const double LengthMax)
{
  myDraft.Perform(LengthMax);
  if (myDraft.IsDone())
  {
    Done();
    myShape = myDraft.Shape();
  }
}

void BRepOffsetAPI_MakeDraft::Perform(const occ::handle<Geom_Surface>& Surface,
                                      const bool                       KeepInsideSurface)
{
  myDraft.Perform(Surface, KeepInsideSurface);
  if (myDraft.IsDone())
  {
    Done();
    myShape = myDraft.Shape();
  }
}

void BRepOffsetAPI_MakeDraft::Perform(const TopoDS_Shape& StopShape, const bool KeepOutSide)
{
  myDraft.Perform(StopShape, KeepOutSide);
  if (myDraft.IsDone())
  {
    Done();
    myShape = myDraft.Shape();
  }
}

TopoDS_Shell BRepOffsetAPI_MakeDraft::Shell() const
{
  return myDraft.Shell();
}

const NCollection_List<TopoDS_Shape>& BRepOffsetAPI_MakeDraft::Generated(const TopoDS_Shape& S)
{
  return myDraft.Generated(S);
}
