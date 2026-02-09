#pragma once

#include <BRepMesh_DefaultRangeSplitter.hpp>

class BRepMesh_CylinderRangeSplitter : public BRepMesh_DefaultRangeSplitter
{
public:
  BRepMesh_CylinderRangeSplitter()
      : myDu(1.)
  {
  }

  ~BRepMesh_CylinderRangeSplitter() override = default;

  Standard_EXPORT void Reset(const IMeshData::IFaceHandle& theDFace,
                             const IMeshTools_Parameters&  theParameters) override;

  Standard_EXPORT Handle(IMeshData::ListOfPnt2d) GenerateSurfaceNodes(
    const IMeshTools_Parameters& theParameters) const override;

protected:
  Standard_EXPORT void computeDelta(const double theLengthU, const double theLengthV) override;

private:
  double myDu;
};
