#pragma once


class BRepMesh_DataStructureOfDelaun;
class BRepMesh_Delaun;

//! Class provides base functionality to build face triangulation using custom
//! triangulation algorithm with possibility to modify final mesh.
//! Performs generation of mesh using raw data from model.
template <class BaseAlgo>
class BRepMesh_CustomDelaunayBaseMeshAlgo : public BaseAlgo
{
public:
  //! Constructor.
  BRepMesh_CustomDelaunayBaseMeshAlgo() = default;

  //! Destructor.
  ~BRepMesh_CustomDelaunayBaseMeshAlgo() override = default;

protected:
  //! Performs processing of generated mesh.
  void postProcessMesh(BRepMesh_Delaun& theMesher, const Message_ProgressRange& theRange) override
  {
    const occ::handle<BRepMesh_DataStructureOfDelaun>& aStructure = this->getStructure();
    std::pair<int, int> aCellsCount = this->getCellsCount(aStructure->NbNodes());
    theMesher.InitCirclesTool(aCellsCount.first, aCellsCount.second);

    BaseAlgo::postProcessMesh(theMesher, theRange);
  }
};

