#include <BRepSweep_Tool.hpp>
#include <TopExp.hpp>
#include <TopoDS_Shape.hpp>

//=================================================================================================

BRepSweep_Tool::BRepSweep_Tool(const TopoDS_Shape& aShape)
{
  TopExp::MapShapes(aShape, myMap);
}

//=================================================================================================

int BRepSweep_Tool::NbShapes() const
{
  return myMap.Extent();
}

//=================================================================================================

int BRepSweep_Tool::Index(const TopoDS_Shape& aShape) const
{
  if (!myMap.Contains(aShape))
    return 0;
  return myMap.FindIndex(aShape);
}

//=================================================================================================

TopoDS_Shape BRepSweep_Tool::Shape(const int anIndex) const
{
  return myMap.FindKey(anIndex);
}

//=================================================================================================

TopAbs_ShapeEnum BRepSweep_Tool::Type(const TopoDS_Shape& aShape) const
{
  return aShape.ShapeType();
}

//=================================================================================================

TopAbs_Orientation BRepSweep_Tool::Orientation(const TopoDS_Shape& aShape) const
{
  return aShape.Orientation();
}

//=================================================================================================

void BRepSweep_Tool::SetOrientation(TopoDS_Shape& aShape, const TopAbs_Orientation Or) const
{
  aShape.Orientation(Or);
}
