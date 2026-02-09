#pragma once

#include <Standard_Transient.hpp>
#include <IMeshTools_MeshAlgoFactory.hpp>

class BRepMesh_MeshAlgoFactory : public IMeshTools_MeshAlgoFactory
{
public:
  Standard_EXPORT BRepMesh_MeshAlgoFactory();

  Standard_EXPORT ~BRepMesh_MeshAlgoFactory() override;

  Standard_EXPORT occ::handle<IMeshTools_MeshAlgo> GetAlgo(
    const GeomAbs_SurfaceType    theSurfaceType,
    const IMeshTools_Parameters& theParameters) const override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_MeshAlgoFactory, IMeshTools_MeshAlgoFactory)
};
