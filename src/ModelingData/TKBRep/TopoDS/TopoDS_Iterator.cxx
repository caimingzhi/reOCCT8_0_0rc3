#define No_Standard_NoSuchObject

#include <TopoDS_Iterator.hpp>

void TopoDS_Iterator::Initialize(const TopoDS_Shape& S, const bool cumOri, const bool cumLoc)
{
  if (cumLoc)
    myLocation = S.Location();
  else
    myLocation.Identity();
  if (cumOri)
    myOrientation = S.Orientation();
  else
    myOrientation = TopAbs_FORWARD;

  if (S.IsNull())
    myShapes = NCollection_List<TopoDS_Shape>::Iterator();
  else
    myShapes.Initialize(S.TShape()->myShapes);

  if (More())
  {
    myShape = myShapes.Value();
    myShape.Orientation(TopAbs::Compose(myOrientation, myShape.Orientation()));
    if (!myLocation.IsIdentity())
      myShape.Move(myLocation, false);
  }
}

void TopoDS_Iterator::Next()
{
  myShapes.Next();
  if (More())
  {
    myShape = myShapes.Value();
    myShape.Orientation(TopAbs::Compose(myOrientation, myShape.Orientation()));
    if (!myLocation.IsIdentity())
      myShape.Move(myLocation, false);
  }
}
