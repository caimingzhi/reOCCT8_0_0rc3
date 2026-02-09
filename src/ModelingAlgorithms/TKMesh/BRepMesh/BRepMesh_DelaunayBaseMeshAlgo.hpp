#pragma once

#include <BRepMesh_ConstrainedBaseMeshAlgo.hpp>

class BRepMesh_DelaunayBaseMeshAlgo : public BRepMesh_ConstrainedBaseMeshAlgo
{
public:
  Standard_EXPORT BRepMesh_DelaunayBaseMeshAlgo();

  Standard_EXPORT ~BRepMesh_DelaunayBaseMeshAlgo() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_DelaunayBaseMeshAlgo, BRepMesh_ConstrainedBaseMeshAlgo)

protected:
  Standard_EXPORT void generateMesh(const Message_ProgressRange& theRange) override;
};
