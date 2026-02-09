

#include <RWMesh_TriangulationSource.hpp>

#include <RWMesh_TriangulationReader.hpp>

IMPLEMENT_STANDARD_RTTIEXT(RWMesh_TriangulationSource, Poly_Triangulation)

RWMesh_TriangulationSource::RWMesh_TriangulationSource()
    : myNbDefNodes(0),
      myNbDefTriangles(0),
      myStatisticOfDegeneratedTriNb(0)
{
}

RWMesh_TriangulationSource::~RWMesh_TriangulationSource() = default;

bool RWMesh_TriangulationSource::loadDeferredData(
  const occ::handle<OSD_FileSystem>&     theFileSystem,
  const occ::handle<Poly_Triangulation>& theDestTriangulation) const
{
  myStatisticOfDegeneratedTriNb = 0;
  if (myReader.IsNull())
  {
    return false;
  }
  if (myReader->Load(this, theDestTriangulation, theFileSystem))
  {
    return true;
  }
  return false;
}

void RWMesh_TriangulationSource::ResizeEdges(int theNbEdges, bool theToCopyOld)
{
  myEdges.Resize(1, theNbEdges, theToCopyOld);
}
