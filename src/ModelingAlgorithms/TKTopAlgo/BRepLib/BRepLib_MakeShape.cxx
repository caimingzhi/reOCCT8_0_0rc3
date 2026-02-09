#include <BRepLib_MakeShape.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>

BRepLib_MakeShape::BRepLib_MakeShape() = default;

void BRepLib_MakeShape::Build() {}

const TopoDS_Shape& BRepLib_MakeShape::Shape()
{
  if (!IsDone())
  {

    ((BRepLib_MakeShape*)(void*)this)->Build();
    Check();
  }
  return myShape;
}

BRepLib_MakeShape::operator TopoDS_Shape()
{
  return Shape();
}

bool BRepLib_MakeShape::HasDescendants(const TopoDS_Face&) const
{
  return (true);
}

BRepLib_ShapeModification BRepLib_MakeShape::FaceStatus(const TopoDS_Face&) const
{
  BRepLib_ShapeModification myStatus = BRepLib_Trimmed;
  return myStatus;
}

const NCollection_List<TopoDS_Shape>& BRepLib_MakeShape::DescendantFaces(const TopoDS_Face&)
{
  return myGenFaces;
}

int BRepLib_MakeShape::NbSurfaces() const
{
  return (0);
}

const NCollection_List<TopoDS_Shape>& BRepLib_MakeShape::NewFaces(const int)
{
  return myNewFaces;
}

const NCollection_List<TopoDS_Shape>& BRepLib_MakeShape::FacesFromEdges(const TopoDS_Edge&)
{
  return myEdgFaces;
}
