#include <TopOpeBRepBuild_ShapeListOfShape.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TCollection_AsciiString.hpp>

//=================================================================================================

TopOpeBRepBuild_ShapeListOfShape::TopOpeBRepBuild_ShapeListOfShape() = default;

//=================================================================================================

TopOpeBRepBuild_ShapeListOfShape::TopOpeBRepBuild_ShapeListOfShape(const TopoDS_Shape& S)
{
  myShape = S;
}

//=================================================================================================

TopOpeBRepBuild_ShapeListOfShape::TopOpeBRepBuild_ShapeListOfShape(
  const TopoDS_Shape&                   S,
  const NCollection_List<TopoDS_Shape>& L)
{
  myShape = S;
  myList  = L;
}

//=================================================================================================

const NCollection_List<TopoDS_Shape>& TopOpeBRepBuild_ShapeListOfShape::List() const
{
  return myList;
}

//=================================================================================================

NCollection_List<TopoDS_Shape>& TopOpeBRepBuild_ShapeListOfShape::ChangeList()
{
  return myList;
}

//=================================================================================================

const TopoDS_Shape& TopOpeBRepBuild_ShapeListOfShape::Shape() const
{
  return myShape;
}

//=================================================================================================

TopoDS_Shape& TopOpeBRepBuild_ShapeListOfShape::ChangeShape()
{
  return myShape;
}
