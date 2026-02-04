#pragma once


#include <IMeshTools_MeshAlgo.hpp>
#include <NCollection_Shared.hpp>
#include <IMeshTools_Parameters.hpp>
#include <BRepMesh_DegreeOfFreedom.hpp>
#include <Poly_Triangulation.hpp>

class BRepMesh_DataStructureOfDelaun;

//! Class provides base functionality for algorithms building face triangulation.
//! Performs initialization of BRepMesh_DataStructureOfDelaun and nodes map structures.
class BRepMesh_BaseMeshAlgo : public IMeshTools_MeshAlgo
{
public:
  typedef NCollection_Shared<NCollection_Vector<gp_Pnt>> VectorOfPnt;

  //! Constructor.
  Standard_EXPORT BRepMesh_BaseMeshAlgo();

  //! Destructor.
  Standard_EXPORT ~BRepMesh_BaseMeshAlgo() override;

  //! Performs processing of the given face.
  Standard_EXPORT void Perform(
    const IMeshData::IFaceHandle& theDFace,
    const IMeshTools_Parameters&  theParameters,
    const Message_ProgressRange&  theRange = Message_ProgressRange()) override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_BaseMeshAlgo, IMeshTools_MeshAlgo)

protected:
  //! Gets discrete face.
  const IMeshData::IFaceHandle& getDFace() const { return myDFace; }

  //! Gets meshing parameters.
  const IMeshTools_Parameters& getParameters() const { return myParameters; }

  //! Gets common allocator.
  const occ::handle<NCollection_IncAllocator>& getAllocator() const { return myAllocator; }

  //! Gets mesh structure.
  const occ::handle<BRepMesh_DataStructureOfDelaun>& getStructure() const { return myStructure; }

  //! Gets 3d nodes map.
  const occ::handle<VectorOfPnt>& getNodesMap() const { return myNodesMap; }

protected:
  //! Registers the given point in vertex map and adds 2d point to mesh data structure.
  //! Returns index of node in the structure.
  Standard_EXPORT virtual int registerNode(const gp_Pnt&                  thePoint,
                                           const gp_Pnt2d&                thePoint2d,
                                           const BRepMesh_DegreeOfFreedom theMovability,
                                           const bool                     isForceAdd);

  //! Adds the given 2d point to mesh data structure.
  //! Returns index of node in the structure.
  Standard_EXPORT virtual int addNodeToStructure(const gp_Pnt2d&                thePoint,
                                                 const int                      theLocation3d,
                                                 const BRepMesh_DegreeOfFreedom theMovability,
                                                 const bool                     isForceAdd);

  //! Returns 2d point associated to the given vertex.
  Standard_EXPORT virtual gp_Pnt2d getNodePoint2d(const BRepMesh_Vertex& theVertex) const;

  //! Performs initialization of data structure using existing model data.
  Standard_EXPORT virtual bool initDataStructure();

  //! Generates mesh for the contour stored in data structure.
  Standard_EXPORT virtual void generateMesh(const Message_ProgressRange& theRange) = 0;

private:
  //! If the given edge has another pcurve for current face coinciding with specified one,
  //! returns TopAbs_INTERNAL flag. Elsewhere returns orientation of specified pcurve.
  TopAbs_Orientation fixSeamEdgeOrientation(const IMeshData::IEdgeHandle&   theDEdge,
                                            const IMeshData::IPCurveHandle& thePCurve) const;

  //! Adds new link to the mesh data structure.
  //! Movability of the link and order of nodes depend on orientation parameter.
  int addLinkToMesh(const int                theFirstNodeId,
                    const int                theLastNodeId,
                    const TopAbs_Orientation theOrientation);

  //! Commits generated triangulation to TopoDS face.
  void commitSurfaceTriangulation();

  //! Collects triangles to output data.
  occ::handle<Poly_Triangulation> collectTriangles();

  //! Collects nodes to output data.
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

