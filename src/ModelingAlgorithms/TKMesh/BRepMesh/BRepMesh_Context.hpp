#pragma once


#include <IMeshTools_Context.hpp>

//! Class implementing default context of BRepMesh algorithm.
//! Initializes context by default algorithms.
class BRepMesh_Context : public IMeshTools_Context
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_Context(
    IMeshTools_MeshAlgoType theMeshType = IMeshTools_MeshAlgoType_DEFAULT);

  //! Destructor.
  Standard_EXPORT ~BRepMesh_Context() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_Context, IMeshTools_Context)
};

