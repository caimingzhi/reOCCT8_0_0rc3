#pragma once

#include <IMeshTools_ModelAlgo.hpp>
#include <IMeshTools_Parameters.hpp>
#include <IMeshData_Types.hpp>

class IMeshTools_CurveTessellator;

class BRepMesh_EdgeDiscret : public IMeshTools_ModelAlgo
{
public:
  Standard_EXPORT BRepMesh_EdgeDiscret();

  Standard_EXPORT ~BRepMesh_EdgeDiscret() override;

  Standard_EXPORT static occ::handle<IMeshTools_CurveTessellator> CreateEdgeTessellator(
    const IMeshData::IEdgeHandle& theDEdge,
    const IMeshTools_Parameters&  theParameters,
    const int                     theMinPointsNb = 2);

  Standard_EXPORT static occ::handle<IMeshTools_CurveTessellator> CreateEdgeTessellator(
    const IMeshData::IEdgeHandle& theDEdge,
    const TopAbs_Orientation      theOrientation,
    const IMeshData::IFaceHandle& theDFace,
    const IMeshTools_Parameters&  theParameters,
    const int                     theMinPointsNb = 2);

  Standard_EXPORT static occ::handle<IMeshTools_CurveTessellator> CreateEdgeTessellationExtractor(
    const IMeshData::IEdgeHandle& theDEdge,
    const IMeshData::IFaceHandle& theDFace);

  void operator()(const int theEdgeIndex) const { process(theEdgeIndex); }

  Standard_EXPORT static void Tessellate3d(
    const IMeshData::IEdgeHandle&                   theDEdge,
    const occ::handle<IMeshTools_CurveTessellator>& theTessellator,
    const bool                                      theUpdateEnds);

  Standard_EXPORT static void Tessellate2d(const IMeshData::IEdgeHandle& theDEdge,
                                           const bool                    theUpdateEnds);

  DEFINE_STANDARD_RTTIEXT(BRepMesh_EdgeDiscret, IMeshTools_ModelAlgo)

protected:
  Standard_EXPORT bool performInternal(const occ::handle<IMeshData_Model>& theModel,
                                       const IMeshTools_Parameters&        theParameters,
                                       const Message_ProgressRange&        theRange) override;

private:
  void process(const int theEdgeIndex) const;

  double checkExistingPolygonAndUpdateStatus(const IMeshData::IEdgeHandle&   theDEdge,
                                             const IMeshData::IPCurveHandle& thePCurve) const;

private:
  occ::handle<IMeshData_Model> myModel;
  IMeshTools_Parameters        myParameters;
};
