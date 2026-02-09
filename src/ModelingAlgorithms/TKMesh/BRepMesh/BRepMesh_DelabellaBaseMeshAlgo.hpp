#pragma once

#include <BRepMesh_CustomBaseMeshAlgo.hpp>

class BRepMesh_DelabellaBaseMeshAlgo : public BRepMesh_CustomBaseMeshAlgo
{
public:
  Standard_EXPORT BRepMesh_DelabellaBaseMeshAlgo();

  Standard_EXPORT ~BRepMesh_DelabellaBaseMeshAlgo() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_DelabellaBaseMeshAlgo, BRepMesh_CustomBaseMeshAlgo)

protected:
  Standard_EXPORT void buildBaseTriangulation() override;
};
