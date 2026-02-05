#pragma once

#include <BRepBuilderAPI_MakeShape.hpp>
#include <Poly_Triangulation.hpp>

//! Builds shape on per-facet basis on the input mesh. Resulting shape has shared
//! edges by construction, but no maximization (unify same domain) is applied.
//! No generation history is provided.
class BRepBuilderAPI_MakeShapeOnMesh : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Ctor. Sets mesh to process.
  //! @param[in] theMesh  - Mesh to construct shape for.
  BRepBuilderAPI_MakeShapeOnMesh(const occ::handle<Poly_Triangulation>& theMesh)
      : myMesh(theMesh)
  {
  }

  //! Builds shape on mesh.
  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

private:
  occ::handle<Poly_Triangulation> myMesh;
};
