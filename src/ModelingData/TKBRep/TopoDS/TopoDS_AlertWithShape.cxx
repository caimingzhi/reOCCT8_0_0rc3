#include <TopoDS_AlertWithShape.hpp>

#include <Message_Msg.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopoDS_AlertWithShape, System::log::Message_Alert)

TopoDS_AlertWithShape::TopoDS_AlertWithShape(const TopoDS_Shape& theShape)
{
  myShape = theShape;
}

bool TopoDS_AlertWithShape::SupportsMerge() const
{
  return false;
}

bool TopoDS_AlertWithShape::Merge(const occ::handle<System::log::Message_Alert>&)
{
  return false;
}
