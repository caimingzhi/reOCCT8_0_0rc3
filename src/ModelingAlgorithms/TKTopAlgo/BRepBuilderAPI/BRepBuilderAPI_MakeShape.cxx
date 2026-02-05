#include <BRepBuilderAPI_MakeShape.hpp>
#include <TopoDS_Shape.hpp>

//=================================================================================================

BRepBuilderAPI_MakeShape::BRepBuilderAPI_MakeShape() = default;

//=================================================================================================

void BRepBuilderAPI_MakeShape::Build(const Message_ProgressRange& /*theRange*/) {}

//=================================================================================================

const TopoDS_Shape& BRepBuilderAPI_MakeShape::Shape()
{
  if (!IsDone())
  {
    // the following is const cast away
    ((BRepBuilderAPI_MakeShape*)(void*)this)->Build();
    Check();
  }
  return myShape;
}

//=================================================================================================

BRepBuilderAPI_MakeShape::operator TopoDS_Shape()
{
  return Shape();
}

//=================================================================================================

const NCollection_List<TopoDS_Shape>& BRepBuilderAPI_MakeShape::Generated(const TopoDS_Shape&)

{
  myGenerated.Clear();
  return myGenerated;
}

//=================================================================================================

const NCollection_List<TopoDS_Shape>& BRepBuilderAPI_MakeShape::Modified(const TopoDS_Shape&)

{
  myGenerated.Clear();
  return myGenerated;
}

//=================================================================================================

bool BRepBuilderAPI_MakeShape::IsDeleted(const TopoDS_Shape&)

{
  return false;
}
