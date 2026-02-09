#pragma once

#include <Poly_Triangulation.hpp>
#include <NCollection_Array1.hpp>

class RWMesh_TriangulationReader;

class RWMesh_TriangulationSource : public Poly_Triangulation
{
  DEFINE_STANDARD_RTTIEXT(RWMesh_TriangulationSource, Poly_Triangulation)
public:
  Standard_EXPORT RWMesh_TriangulationSource();

  Standard_EXPORT ~RWMesh_TriangulationSource() override;

  const occ::handle<RWMesh_TriangulationReader>& Reader() const { return myReader; }

  void SetReader(const occ::handle<RWMesh_TriangulationReader>& theReader) { myReader = theReader; }

  int DegeneratedTriNb() const { return myStatisticOfDegeneratedTriNb; }

  int& ChangeDegeneratedTriNb() { return myStatisticOfDegeneratedTriNb; }

  bool HasGeometry() const override
  {
    return !myNodes.IsEmpty() && (!myTriangles.IsEmpty() || !myEdges.IsEmpty());
  }

  int NbEdges() const { return myEdges.Length(); }

  int Edge(int theIndex) const { return myEdges.Value(theIndex); }

  void SetEdge(int theIndex, int theEdge) { myEdges.SetValue(theIndex, theEdge); }

public:
  int NbDeferredNodes() const override { return myNbDefNodes; }

  void SetNbDeferredNodes(const int theNbNodes) { myNbDefNodes = theNbNodes; }

  int NbDeferredTriangles() const override { return myNbDefTriangles; }

  void SetNbDeferredTriangles(const int theNbTris) { myNbDefTriangles = theNbTris; }

  NCollection_Array1<int>& InternalEdges() { return myEdges; }

  Standard_EXPORT void ResizeEdges(int theNbEdges, bool theToCopyOld);

protected:
  Standard_EXPORT bool loadDeferredData(
    const occ::handle<OSD_FileSystem>&     theFileSystem,
    const occ::handle<Poly_Triangulation>& theDestTriangulation) const override;

protected:
  occ::handle<RWMesh_TriangulationReader> myReader;
  NCollection_Array1<int>                 myEdges;
  int                                     myNbDefNodes;
  int                                     myNbDefTriangles;
  mutable int                             myStatisticOfDegeneratedTriNb;
};
