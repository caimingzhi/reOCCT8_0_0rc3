#include <BRepOffsetAPI_MakeThickSolid.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>

BRepOffsetAPI_MakeThickSolid::BRepOffsetAPI_MakeThickSolid()
{

  mySimpleOffsetShape.SetBuildSolidFlag(true);
}

void BRepOffsetAPI_MakeThickSolid::MakeThickSolidByJoin(
  const TopoDS_Shape&                   S,
  const NCollection_List<TopoDS_Shape>& ClosingFaces,
  const double                          Offset,
  const double                          Tol,
  const BRepOffset_Mode                 Mode,
  const bool                            Intersection,
  const bool                            SelfInter,
  const GeomAbs_JoinType                Join,
  const bool                            RemoveIntEdges,
  const Message_ProgressRange&          theRange)
{
  NotDone();
  myLastUsedAlgo = OffsetAlgo_JOIN;

  myOffsetShape
    .Initialize(S, Offset, Tol, Mode, Intersection, SelfInter, Join, false, RemoveIntEdges);
  NCollection_List<TopoDS_Shape>::Iterator it(ClosingFaces);
  for (; it.More(); it.Next())
    myOffsetShape.AddFace(TopoDS::Face(it.Value()));

  myOffsetShape.MakeThickSolid(theRange);
  if (!myOffsetShape.IsDone())
    return;

  myShape = myOffsetShape.Shape();
  Done();
}

void BRepOffsetAPI_MakeThickSolid::MakeThickSolidBySimple(const TopoDS_Shape& theS,
                                                          const double        theOffsetValue)
{
  NotDone();
  myLastUsedAlgo = OffsetAlgo_SIMPLE;

  mySimpleOffsetShape.Initialize(theS, theOffsetValue);
  mySimpleOffsetShape.Perform();

  if (!mySimpleOffsetShape.IsDone())
    return;

  myShape = mySimpleOffsetShape.GetResultShape();
  Done();
}

void BRepOffsetAPI_MakeThickSolid::Build(const Message_ProgressRange&) {}

const NCollection_List<TopoDS_Shape>& BRepOffsetAPI_MakeThickSolid::Modified(const TopoDS_Shape& F)
{
  myGenerated.Clear();

  if (myLastUsedAlgo == OffsetAlgo_JOIN && myOffsetShape.OffsetFacesFromShapes().HasImage(F))
  {
    if (myOffsetShape.ClosingFaces().Contains(F))
    {
      myOffsetShape.OffsetFacesFromShapes().LastImage(F, myGenerated);

      NCollection_List<TopoDS_Shape>::Iterator it(myGenerated);
      for (; it.More(); it.Next())
        it.ChangeValue().Reverse();
    }
  }
  else if (myLastUsedAlgo == OffsetAlgo_SIMPLE)
  {
    TopoDS_Shape aModShape = mySimpleOffsetShape.Modified(F);
    if (!aModShape.IsNull())
      myGenerated.Append(aModShape);
  }

  return myGenerated;
}
