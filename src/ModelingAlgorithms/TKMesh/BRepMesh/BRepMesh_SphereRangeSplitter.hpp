#pragma once

#include <BRepMesh_DefaultRangeSplitter.hpp>
#include <IMeshTools_Parameters.hpp>

class BRepMesh_SphereRangeSplitter : public BRepMesh_DefaultRangeSplitter
{
public:
  BRepMesh_SphereRangeSplitter() = default;

  ~BRepMesh_SphereRangeSplitter() override = default;

  Standard_EXPORT Handle(IMeshData::ListOfPnt2d) GenerateSurfaceNodes(
    const IMeshTools_Parameters& theParameters) const override;

private:
  void computeStep(const std::pair<double, double>& theRange,
                   const double                     theDefaultStep,
                   std::pair<double, double>&       theStepAndOffset) const
  {
    const double aDiff      = theRange.second - theRange.first;
    theStepAndOffset.first  = aDiff / ((int)(aDiff / theDefaultStep) + 1);
    theStepAndOffset.second = theRange.second - Precision::PConfusion();
  }
};
