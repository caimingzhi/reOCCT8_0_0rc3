#pragma once


#include <BRepMesh_DefaultRangeSplitter.hpp>
#include <IMeshTools_Parameters.hpp>

//! Auxiliary class extending default range splitter in
//! order to generate internal nodes for spherical surface.
class BRepMesh_SphereRangeSplitter : public BRepMesh_DefaultRangeSplitter
{
public:
  //! Constructor.
  BRepMesh_SphereRangeSplitter() = default;

  //! Destructor.
  ~BRepMesh_SphereRangeSplitter() override = default;

  //! Returns list of nodes generated using surface data and specified parameters.
  Standard_EXPORT Handle(IMeshData::ListOfPnt2d) GenerateSurfaceNodes(
    const IMeshTools_Parameters& theParameters) const override;

private:
  //! Computes step for the given range.
  void computeStep(const std::pair<double, double>& theRange,
                   const double                     theDefaultStep,
                   std::pair<double, double>&       theStepAndOffset) const
  {
    const double aDiff      = theRange.second - theRange.first;
    theStepAndOffset.first  = aDiff / ((int)(aDiff / theDefaultStep) + 1);
    theStepAndOffset.second = theRange.second - Precision::PConfusion();
  }
};

