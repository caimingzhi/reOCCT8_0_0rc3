#pragma once

class BRepMesh_DataStructureOfDelaun;
class BRepMesh_Delaun;

template <class BaseAlgo>
class BRepMesh_CustomDelaunayBaseMeshAlgo : public BaseAlgo
{
public:
  BRepMesh_CustomDelaunayBaseMeshAlgo() = default;

  ~BRepMesh_CustomDelaunayBaseMeshAlgo() override = default;

protected:
  void postProcessMesh(BRepMesh_Delaun& theMesher, const Message_ProgressRange& theRange) override
  {
    const occ::handle<BRepMesh_DataStructureOfDelaun>& aStructure = this->getStructure();
    std::pair<int, int> aCellsCount = this->getCellsCount(aStructure->NbNodes());
    theMesher.InitCirclesTool(aCellsCount.first, aCellsCount.second);

    BaseAlgo::postProcessMesh(theMesher, theRange);
  }
};
