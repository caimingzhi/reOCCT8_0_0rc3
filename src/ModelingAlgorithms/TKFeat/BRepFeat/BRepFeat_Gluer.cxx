#include <BRepFeat_Gluer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

void BRepFeat_Gluer::Build(const Message_ProgressRange&)
{
  myGluer.Perform();
  if (myGluer.IsDone())
  {
    Done();
    myShape = myGluer.ResultingShape();
  }
  else
  {
    NotDone();
  }
}

bool BRepFeat_Gluer::IsDeleted(const TopoDS_Shape& F)
{
  return (myGluer.DescendantFaces(TopoDS::Face(F)).IsEmpty());
}

const NCollection_List<TopoDS_Shape>& BRepFeat_Gluer::Modified(const TopoDS_Shape& F)
{
  if (F.ShapeType() == TopAbs_FACE)
  {
    const NCollection_List<TopoDS_Shape>& LS = myGluer.DescendantFaces(TopoDS::Face(F));
    if (!LS.IsEmpty())
    {
      if (!LS.First().IsSame(F))
        return myGluer.DescendantFaces(TopoDS::Face(F));
    }
  }
  static NCollection_List<TopoDS_Shape> LIM;
  return LIM;
}
