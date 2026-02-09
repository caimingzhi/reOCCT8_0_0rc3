#pragma once

#include <BRepBuilderAPI_MakeShape.hpp>
#include <Poly_Triangulation.hpp>

class BRepBuilderAPI_MakeShapeOnMesh : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  BRepBuilderAPI_MakeShapeOnMesh(const occ::handle<Poly_Triangulation>& theMesh)
      : myMesh(theMesh)
  {
  }

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

private:
  occ::handle<Poly_Triangulation> myMesh;
};
