#pragma once


#include <BRepMesh_CustomBaseMeshAlgo.hpp>

//! Class provides base functionality to build face triangulation using Delabella project.
//! Performs generation of mesh using raw data from model.
class BRepMesh_DelabellaBaseMeshAlgo : public BRepMesh_CustomBaseMeshAlgo
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_DelabellaBaseMeshAlgo();

  //! Destructor.
  Standard_EXPORT ~BRepMesh_DelabellaBaseMeshAlgo() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_DelabellaBaseMeshAlgo, BRepMesh_CustomBaseMeshAlgo)

protected:
  //! Builds base triangulation using Delabella project.
  Standard_EXPORT void buildBaseTriangulation() override;
};

