#pragma once

#include <IMeshTools_Context.hpp>

class BRepMesh_Context : public IMeshTools_Context
{
public:
  Standard_EXPORT BRepMesh_Context(
    IMeshTools_MeshAlgoType theMeshType = IMeshTools_MeshAlgoType_DEFAULT);

  Standard_EXPORT ~BRepMesh_Context() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_Context, IMeshTools_Context)
};
