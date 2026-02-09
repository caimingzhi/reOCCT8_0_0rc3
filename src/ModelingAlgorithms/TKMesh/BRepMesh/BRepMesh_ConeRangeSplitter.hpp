#pragma once

#include <BRepMesh_DefaultRangeSplitter.hpp>

class BRepMesh_ConeRangeSplitter : public BRepMesh_DefaultRangeSplitter
{
public:
  BRepMesh_ConeRangeSplitter() = default;

  ~BRepMesh_ConeRangeSplitter() override = default;

  std::pair<double, double> GetSplitSteps(const IMeshTools_Parameters& theParameters,
                                          std::pair<int, int>&         theStepsNb) const;

  Standard_EXPORT Handle(IMeshData::ListOfPnt2d) GenerateSurfaceNodes(
    const IMeshTools_Parameters& theParameters) const override;
};
