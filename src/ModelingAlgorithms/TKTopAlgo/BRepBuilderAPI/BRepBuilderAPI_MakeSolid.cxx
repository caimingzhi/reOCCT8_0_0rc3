#include <BRepBuilderAPI_MakeSolid.hpp>
#include <TopoDS.hpp>
#include <TopoDS_CompSolid.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>

BRepBuilderAPI_MakeSolid::BRepBuilderAPI_MakeSolid() = default;

BRepBuilderAPI_MakeSolid::BRepBuilderAPI_MakeSolid(const TopoDS_CompSolid& S)
    : myMakeSolid(S)
{
  if (myMakeSolid.IsDone())
  {
    Done();
    myShape = myMakeSolid.Shape();
  }
}

BRepBuilderAPI_MakeSolid::BRepBuilderAPI_MakeSolid(const TopoDS_Shell& S)
    : myMakeSolid(S)
{
  if (myMakeSolid.IsDone())
  {
    Done();
    myShape = myMakeSolid.Shape();
  }
}

BRepBuilderAPI_MakeSolid::BRepBuilderAPI_MakeSolid(const TopoDS_Shell& S1, const TopoDS_Shell& S2)
    : myMakeSolid(S1, S2)
{
  if (myMakeSolid.IsDone())
  {
    Done();
    myShape = myMakeSolid.Shape();
  }
}

BRepBuilderAPI_MakeSolid::BRepBuilderAPI_MakeSolid(const TopoDS_Shell& S1,
                                                   const TopoDS_Shell& S2,
                                                   const TopoDS_Shell& S3)
    : myMakeSolid(S1, S2, S3)
{
  if (myMakeSolid.IsDone())
  {
    Done();
    myShape = myMakeSolid.Shape();
  }
}

BRepBuilderAPI_MakeSolid::BRepBuilderAPI_MakeSolid(const TopoDS_Solid& So)
    : myMakeSolid(So)
{
  if (myMakeSolid.IsDone())
  {
    Done();
    myShape = myMakeSolid.Shape();
  }
}

BRepBuilderAPI_MakeSolid::BRepBuilderAPI_MakeSolid(const TopoDS_Solid& So, const TopoDS_Shell& S)
    : myMakeSolid(So, S)
{
  if (myMakeSolid.IsDone())
  {
    Done();
    myShape = myMakeSolid.Shape();
  }
}

void BRepBuilderAPI_MakeSolid::Add(const TopoDS_Shell& S)
{
  myMakeSolid.Add(S);
  if (myMakeSolid.IsDone())
  {
    Done();
    myShape = myMakeSolid.Shape();
  }
}

bool BRepBuilderAPI_MakeSolid::IsDone() const
{
  return myMakeSolid.IsDone();
}

const TopoDS_Solid& BRepBuilderAPI_MakeSolid::Solid()
{
  return myMakeSolid.Solid();
}

BRepBuilderAPI_MakeSolid::operator TopoDS_Solid()
{
  return Solid();
}

bool BRepBuilderAPI_MakeSolid::IsDeleted(const TopoDS_Shape& S)

{
  if (S.ShapeType() == TopAbs_FACE)
  {
    BRepLib_ShapeModification aStatus = myMakeSolid.FaceStatus(TopoDS::Face(S));

    if (aStatus == BRepLib_Deleted)
      return true;
  }

  return false;
}
