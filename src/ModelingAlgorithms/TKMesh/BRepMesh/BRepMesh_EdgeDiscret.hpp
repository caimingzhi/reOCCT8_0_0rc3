#pragma once

#include <IMeshTools_ModelAlgo.hpp>
#include <IMeshTools_Parameters.hpp>
#include <IMeshData_Types.hpp>

class IMeshTools_CurveTessellator;

//! Class implements functionality of edge discret tool.
//! Performs check of the edges for existing Poly_PolygonOnTriangulation.
//! In case if it fits specified deflection, restores data structure using
//! it, else clears edges from outdated data.
class BRepMesh_EdgeDiscret : public IMeshTools_ModelAlgo
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_EdgeDiscret();

  //! Destructor.
  Standard_EXPORT ~BRepMesh_EdgeDiscret() override;

  //! Creates instance of free edge tessellator.
  Standard_EXPORT static occ::handle<IMeshTools_CurveTessellator> CreateEdgeTessellator(
    const IMeshData::IEdgeHandle& theDEdge,
    const IMeshTools_Parameters&  theParameters,
    const int                     theMinPointsNb = 2);

  //! Creates instance of edge tessellator.
  Standard_EXPORT static occ::handle<IMeshTools_CurveTessellator> CreateEdgeTessellator(
    const IMeshData::IEdgeHandle& theDEdge,
    const TopAbs_Orientation      theOrientation,
    const IMeshData::IFaceHandle& theDFace,
    const IMeshTools_Parameters&  theParameters,
    const int                     theMinPointsNb = 2);

  //! Creates instance of tessellation extractor.
  Standard_EXPORT static occ::handle<IMeshTools_CurveTessellator> CreateEdgeTessellationExtractor(
    const IMeshData::IEdgeHandle& theDEdge,
    const IMeshData::IFaceHandle& theDFace);

  //! Functor API to discretize the given edge.
  void operator()(const int theEdgeIndex) const { process(theEdgeIndex); }

  //! Updates 3d discrete edge model using the given tessellation tool.
  Standard_EXPORT static void Tessellate3d(
    const IMeshData::IEdgeHandle&                   theDEdge,
    const occ::handle<IMeshTools_CurveTessellator>& theTessellator,
    const bool                                      theUpdateEnds);

  //! Updates 2d discrete edge model using tessellation of 3D curve.
  Standard_EXPORT static void Tessellate2d(const IMeshData::IEdgeHandle& theDEdge,
                                           const bool                    theUpdateEnds);

  DEFINE_STANDARD_RTTIEXT(BRepMesh_EdgeDiscret, IMeshTools_ModelAlgo)

protected:
  //! Performs processing of edges of the given model.
  Standard_EXPORT bool performInternal(const occ::handle<IMeshData_Model>& theModel,
                                       const IMeshTools_Parameters&        theParameters,
                                       const Message_ProgressRange&        theRange) override;

private:
  //! Checks existing discretization of the edge and updates data model.
  void process(const int theEdgeIndex) const;

  //! Checks existing polygon on triangulation does it fit edge deflection or not.
  //! @return deflection of polygon or RealLast () in case if edge has no polygon
  //! or it was dropped.
  double checkExistingPolygonAndUpdateStatus(const IMeshData::IEdgeHandle&   theDEdge,
                                             const IMeshData::IPCurveHandle& thePCurve) const;

private:
  occ::handle<IMeshData_Model> myModel;
  IMeshTools_Parameters        myParameters;
};
