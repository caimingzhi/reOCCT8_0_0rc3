#pragma once

#include <BRepMesh_DefaultRangeSplitter.hpp>

//! Auxiliary class extending default range splitter in
//! order to generate internal nodes for conical surface.
class BRepMesh_ConeRangeSplitter : public BRepMesh_DefaultRangeSplitter
{
public:
  //! Constructor.
  BRepMesh_ConeRangeSplitter() = default;

  //! Destructor.
  ~BRepMesh_ConeRangeSplitter() override = default;

  //! Returns split intervals along U and V direction.
  //! @param theParameters meshing parameters.
  //! @param[out] theStepsNb number of steps along corresponding direction.
  std::pair<double, double> GetSplitSteps(const IMeshTools_Parameters& theParameters,
                                          std::pair<int, int>&         theStepsNb) const;

  //! Returns list of nodes generated using surface data and specified parameters.
  Standard_EXPORT Handle(IMeshData::ListOfPnt2d) GenerateSurfaceNodes(
    const IMeshTools_Parameters& theParameters) const override;
};
