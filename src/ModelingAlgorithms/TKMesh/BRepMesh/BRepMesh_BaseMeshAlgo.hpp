#pragma once

#include <IMeshTools_MeshAlgo.hpp>
#include <NCollection_Shared.hpp>
#include <IMeshTools_Parameters.hpp>
#include <BRepMesh_DegreeOfFreedom.hpp>
#include <Poly_Triangulation.hpp>

class BRepMesh_DataStructureOfDelaun;

class BRepMesh_BaseMeshAlgo : public IMeshTools_MeshAlgo
{
public:
  typedef NCollection_Shared<NCollection_Vector<gp_Pnt>> VectorOfPnt;

  Standard_EXPORT BRepMesh_BaseMeshAlgo();

  Standard_EXPORT ~BRepMesh_BaseMeshAlgo() override;

  Standard_EXPORT void Perform(
    const IMeshData::IFaceHandle& theDFace,
    const IMeshTools_Parameters&  theParameters,
    const Message_ProgressRange&  theRange = Message_ProgressRange()) override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_BaseMeshAlgo, IMeshTools_MeshAlgo)

protected:
  const IMeshData::IFaceHandle& getDFace() const { return myDFace; }

  const IMeshTools_Parameters& getParameters() const { return myParameters; }

  const occ::handle<NCollection_IncAllocator>& getAllocator() const { return myAllocator; }

  const occ::handle<BRepMesh_DataStructureOfDelaun>& getStructure() const { return myStructure; }

  const occ::handle<VectorOfPnt>& getNodesMap() const { return myNodesMap; }

protected:
  Standard_EXPORT virtual int registerNode(const gp_Pnt&                  thePoint,
                                           const gp_Pnt2d&                thePoint2d,
                                           const BRepMesh_DegreeOfFreedom theMovability,
                                           const bool                     isForceAdd);

  Standard_EXPORT virtual int addNodeToStructure(const gp_Pnt2d&                thePoint,
                                                 const int                      theLocation3d,
                                                 const BRepMesh_DegreeOfFreedom theMovability,
                                                 const bool                     isForceAdd);

  Standard_EXPORT virtual gp_Pnt2d getNodePoint2d(const BRepMesh_Vertex& theVertex) const;

  Standard_EXPORT virtual bool initDataStructure();

  Standard_EXPORT virtual void generateMesh(const Message_ProgressRange& theRange) = 0;

private:
  TopAbs_Orientation fixSeamEdgeOrientation(const IMeshData::IEdgeHandle&   theDEdge,
                                            const IMeshData::IPCurveHandle& thePCurve) const;

  int addLinkToMesh(const int                theFirstNodeId,
                    const int                theLastNodeId,
                    const TopAbs_Orientation theOrientation);

  void commitSurfaceTriangulation();

  occ::handle<Poly_Triangulation> collectTriangles();

  void collectNodes(const occ::handle<Poly_Triangulation>& theTriangulation);

private:
  typedef NCollection_Shared<NCollection_DataMap<int, int>> DMapOfIntegerInteger;

  IMeshData::IFaceHandle                      myDFace;
  IMeshTools_Parameters                       myParameters;
  occ::handle<NCollection_IncAllocator>       myAllocator;
  occ::handle<BRepMesh_DataStructureOfDelaun> myStructure;
  occ::handle<VectorOfPnt>                    myNodesMap;
  occ::handle<DMapOfIntegerInteger>           myUsedNodes;
};
