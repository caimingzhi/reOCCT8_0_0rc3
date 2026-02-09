#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

enum Vrml_VertexOrdering
{
  Vrml_UNKNOWN_ORDERING,
  Vrml_CLOCKWISE,
  Vrml_COUNTERCLOCKWISE
};

enum Vrml_ShapeType
{
  Vrml_UNKNOWN_SHAPE_TYPE,
  Vrml_SOLID
};

enum Vrml_FaceType
{
  Vrml_UNKNOWN_FACE_TYPE,
  Vrml_CONVEX
};

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>

class Vrml_ShapeHints
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_ShapeHints(const Vrml_VertexOrdering aVertexOrdering = Vrml_UNKNOWN_ORDERING,
                                  const Vrml_ShapeType      aShapeType = Vrml_UNKNOWN_SHAPE_TYPE,
                                  const Vrml_FaceType       aFaceType  = Vrml_CONVEX,
                                  const double              aAngle     = 0.5);

  Standard_EXPORT void SetVertexOrdering(const Vrml_VertexOrdering aVertexOrdering);

  Standard_EXPORT Vrml_VertexOrdering VertexOrdering() const;

  Standard_EXPORT void SetShapeType(const Vrml_ShapeType aShapeType);

  Standard_EXPORT Vrml_ShapeType ShapeType() const;

  Standard_EXPORT void SetFaceType(const Vrml_FaceType aFaceType);

  Standard_EXPORT Vrml_FaceType FaceType() const;

  Standard_EXPORT void SetAngle(const double aAngle);

  Standard_EXPORT double Angle() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  Vrml_VertexOrdering myVertexOrdering;
  Vrml_ShapeType      myShapeType;
  Vrml_FaceType       myFaceType;
  double              myAngle;
};
