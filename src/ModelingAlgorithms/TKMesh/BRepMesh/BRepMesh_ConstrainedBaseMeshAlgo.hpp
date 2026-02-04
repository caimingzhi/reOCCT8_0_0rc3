#pragma once


#include <BRepMesh_BaseMeshAlgo.hpp>

class BRepMesh_Delaun;

//! Class provides base functionality to build face triangulation using Dealunay approach.
//! Performs generation of mesh using raw data from model.
class BRepMesh_ConstrainedBaseMeshAlgo : public BRepMesh_BaseMeshAlgo
{
public:
  //! Constructor.
  BRepMesh_ConstrainedBaseMeshAlgo() = default;

  //! Destructor.
  ~BRepMesh_ConstrainedBaseMeshAlgo() override = default;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_ConstrainedBaseMeshAlgo, BRepMesh_BaseMeshAlgo)

protected:
  //! Returns size of cell to be used by acceleration circles grid structure.
  virtual std::pair<int, int> getCellsCount(const int /*theVerticesNb*/)
  {
    return std::pair<int, int>(-1, -1);
  }

  //! Performs processing of generated mesh.
  //! By default does nothing.
  //! Expected to be called from method generateMesh() in successor classes.
  virtual void postProcessMesh(BRepMesh_Delaun& /*theMesher*/,
                               const Message_ProgressRange& /*theRange*/)
  {
  }
};

