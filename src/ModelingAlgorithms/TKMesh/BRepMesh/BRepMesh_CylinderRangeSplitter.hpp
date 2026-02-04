#pragma once


#include <BRepMesh_DefaultRangeSplitter.hpp>

//! Auxiliary class extending default range splitter in
//! order to generate internal nodes for cylindrical surface.
class BRepMesh_CylinderRangeSplitter : public BRepMesh_DefaultRangeSplitter
{
public:
  //! Constructor.
  BRepMesh_CylinderRangeSplitter()
      : myDu(1.)
  {
  }

  //! Destructor.
  ~BRepMesh_CylinderRangeSplitter() override = default;

  //! Resets this splitter. Must be called before first use.
  Standard_EXPORT void Reset(const IMeshData::IFaceHandle& theDFace,
                             const IMeshTools_Parameters&  theParameters) override;

  //! Returns list of nodes generated using surface data and specified parameters.
  Standard_EXPORT Handle(IMeshData::ListOfPnt2d) GenerateSurfaceNodes(
    const IMeshTools_Parameters& theParameters) const override;

protected:
  //! Computes parametric delta taking length along U and V into account.
  Standard_EXPORT void computeDelta(const double theLengthU, const double theLengthV) override;

private:
  double myDu;
};

