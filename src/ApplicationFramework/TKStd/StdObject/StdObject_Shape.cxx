

#include <StdObject_Shape.hpp>

TopoDS_Shape StdObject_Shape::Import() const
{
  TopoDS_Shape aShape;

  if (myTShape)
    aShape.TShape(myTShape->Import());

  aShape.Location(myLocation.Import());
  aShape.Orientation(static_cast<TopAbs_Orientation>(myOrient));

  return aShape;
}

void StdObject_Shape::PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
{
  theChildren.Append(myTShape);
  myLocation.PChildren(theChildren);
}
