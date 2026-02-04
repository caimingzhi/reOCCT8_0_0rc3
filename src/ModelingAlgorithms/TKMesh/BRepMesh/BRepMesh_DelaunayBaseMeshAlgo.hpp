#pragma once


#include <BRepMesh_ConstrainedBaseMeshAlgo.hpp>

//! Class provides base functionality to build face triangulation using Dealunay approach.
//! Performs generation of mesh using raw data from model.
class BRepMesh_DelaunayBaseMeshAlgo : public BRepMesh_ConstrainedBaseMeshAlgo
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_DelaunayBaseMeshAlgo();

  //! Destructor.
  Standard_EXPORT ~BRepMesh_DelaunayBaseMeshAlgo() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_DelaunayBaseMeshAlgo, BRepMesh_ConstrainedBaseMeshAlgo)

protected:
  //! Generates mesh for the contour stored in data structure.
  Standard_EXPORT void generateMesh(const Message_ProgressRange& theRange) override;
};

