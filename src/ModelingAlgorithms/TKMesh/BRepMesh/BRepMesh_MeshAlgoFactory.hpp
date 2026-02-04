#pragma once


#include <Standard_Transient.hpp>
#include <IMeshTools_MeshAlgoFactory.hpp>

//! Default implementation of IMeshTools_MeshAlgoFactory providing algorithms
//! of different complexity depending on type of target surface.
class BRepMesh_MeshAlgoFactory : public IMeshTools_MeshAlgoFactory
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_MeshAlgoFactory();

  //! Destructor.
  Standard_EXPORT ~BRepMesh_MeshAlgoFactory() override;

  //! Creates instance of meshing algorithm for the given type of surface.
  Standard_EXPORT occ::handle<IMeshTools_MeshAlgo> GetAlgo(
    const GeomAbs_SurfaceType    theSurfaceType,
    const IMeshTools_Parameters& theParameters) const override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_MeshAlgoFactory, IMeshTools_MeshAlgoFactory)
};

