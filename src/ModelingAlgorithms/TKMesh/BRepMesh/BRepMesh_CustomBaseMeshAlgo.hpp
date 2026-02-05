#pragma once

#include <BRepMesh_ConstrainedBaseMeshAlgo.hpp>
#include <NCollection_Shared.hpp>

#include <BRepMesh_Delaun.hpp>
#include <BRepMesh_MeshTool.hpp>

//! Class provides base functionality to build face triangulation using custom triangulation
//! algorithm. Performs generation of mesh using raw data from model.
class BRepMesh_CustomBaseMeshAlgo : public BRepMesh_ConstrainedBaseMeshAlgo
{
public:
  //! Constructor.
  BRepMesh_CustomBaseMeshAlgo() = default;

  //! Destructor.
  ~BRepMesh_CustomBaseMeshAlgo() override = default;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_CustomBaseMeshAlgo, BRepMesh_ConstrainedBaseMeshAlgo)

protected:
  //! Generates mesh for the contour stored in data structure.
  void generateMesh(const Message_ProgressRange& theRange) override
  {
    const occ::handle<BRepMesh_DataStructureOfDelaun>& aStructure = this->getStructure();
    const int                                          aNodesNb   = aStructure->NbNodes();

    buildBaseTriangulation();

    std::pair<int, int> aCellsCount = this->getCellsCount(aStructure->NbNodes());
    BRepMesh_Delaun     aMesher(aStructure, aCellsCount.first, aCellsCount.second, false);

    const int  aNewNodesNb = aStructure->NbNodes();
    const bool isRemoveAux = aNewNodesNb > aNodesNb;
    if (isRemoveAux)
    {
      IMeshData::VectorOfInteger aAuxVertices(aNewNodesNb - aNodesNb);
      for (int aExtNodesIt = aNodesNb + 1; aExtNodesIt <= aNewNodesNb; ++aExtNodesIt)
      {
        aAuxVertices.Append(aExtNodesIt);
      }

      // Set aux vertices if there are some to clean up mesh correctly.
      aMesher.SetAuxVertices(aAuxVertices);
    }

    aMesher.ProcessConstraints();

    // Destruction of triangles containing aux vertices added (possibly) during base mesh
    // computation.
    if (isRemoveAux)
    {
      aMesher.RemoveAuxElements();
    }

    BRepMesh_MeshTool aCleaner(aStructure);
    aCleaner.EraseFreeLinks();

    postProcessMesh(aMesher, theRange);
  }

protected:
  //! Builds base triangulation using custom triangulation algorithm.
  Standard_EXPORT virtual void buildBaseTriangulation() = 0;
};
