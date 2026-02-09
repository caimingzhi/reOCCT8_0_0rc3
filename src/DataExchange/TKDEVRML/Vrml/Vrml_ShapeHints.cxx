

#include <Vrml_ShapeHints.hpp>

Vrml_ShapeHints::Vrml_ShapeHints(const Vrml_VertexOrdering aVertexOrdering,
                                 const Vrml_ShapeType      aShapeType,
                                 const Vrml_FaceType       aFaceType,
                                 const double              aAngle)
{
  myVertexOrdering = aVertexOrdering;
  myShapeType      = aShapeType;
  myFaceType       = aFaceType;
  myAngle          = aAngle;
}

void Vrml_ShapeHints::SetVertexOrdering(const Vrml_VertexOrdering aVertexOrdering)
{
  myVertexOrdering = aVertexOrdering;
}

Vrml_VertexOrdering Vrml_ShapeHints::VertexOrdering() const
{
  return myVertexOrdering;
}

void Vrml_ShapeHints::SetShapeType(const Vrml_ShapeType aShapeType)
{
  myShapeType = aShapeType;
}

Vrml_ShapeType Vrml_ShapeHints::ShapeType() const
{
  return myShapeType;
}

void Vrml_ShapeHints::SetFaceType(const Vrml_FaceType aFaceType)
{
  myFaceType = aFaceType;
}

Vrml_FaceType Vrml_ShapeHints::FaceType() const
{
  return myFaceType;
}

void Vrml_ShapeHints::SetAngle(const double aAngle)
{
  myAngle = aAngle;
}

double Vrml_ShapeHints::Angle() const
{
  return myAngle;
}

Standard_OStream& Vrml_ShapeHints::Print(Standard_OStream& anOStream) const
{
  anOStream << "ShapeHints {\n";

  switch (myVertexOrdering)
  {
    case Vrml_UNKNOWN_ORDERING:
      break;
    case Vrml_CLOCKWISE:
      anOStream << "    vertexOrdering\tCLOCKWISE\n";
      break;
    case Vrml_COUNTERCLOCKWISE:
      anOStream << "    vertexOrdering\tCOUNTERCLOCKWISE\n";
      break;
  }

  switch (myShapeType)
  {
    case Vrml_UNKNOWN_SHAPE_TYPE:
      break;
    case Vrml_SOLID:
      anOStream << "    shapeType\t\tSOLID\n";
      break;
  }

  switch (myFaceType)
  {
    case Vrml_UNKNOWN_FACE_TYPE:
      anOStream << "    faceType\t\tUNKNOWN_FACE_TYPE\n";
      break;
    case Vrml_CONVEX:
      break;
  }

  if (std::abs(myAngle - 0.5) > 0.0001)
  {
    anOStream << "    creaseAngle\t\t" << myAngle << "\n";
  }
  anOStream << "}\n";
  return anOStream;
}
