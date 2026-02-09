#include <BRepMesh_DelaunayBaseMeshAlgo.hpp>
#include <BRepMesh_MeshTool.hpp>
#include <BRepMesh_Delaun.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_DelaunayBaseMeshAlgo, BRepMesh_ConstrainedBaseMeshAlgo)

BRepMesh_DelaunayBaseMeshAlgo::BRepMesh_DelaunayBaseMeshAlgo() = default;

BRepMesh_DelaunayBaseMeshAlgo::~BRepMesh_DelaunayBaseMeshAlgo() = default;

void BRepMesh_DelaunayBaseMeshAlgo::generateMesh(const Message_ProgressRange& theRange)
{
  const occ::handle<BRepMesh_DataStructureOfDelaun>& aStructure = getStructure();
  const occ::handle<VectorOfPnt>&                    aNodesMap  = getNodesMap();

  IMeshData::VectorOfInteger aVerticesOrder(aNodesMap->Size(), getAllocator());
  for (int i = 1; i <= aNodesMap->Size(); ++i)
  {
    aVerticesOrder.Append(i);
  }

  std::pair<int, int> aCellsCount = getCellsCount(aVerticesOrder.Size());
  BRepMesh_Delaun     aMesher(aStructure, aVerticesOrder, aCellsCount.first, aCellsCount.second);
  BRepMesh_MeshTool   aCleaner(aStructure);
  aCleaner.EraseFreeLinks();

  if (!theRange.More())
  {
    return;
  }
  postProcessMesh(aMesher, theRange);
}
