#pragma once

#include <BRepMesh_UVParamRangeSplitter.hpp>
#include <IMeshTools_Parameters.hpp>

//! Auxiliary class extending UV range splitter in order to generate
//! internal nodes for NURBS surface.
class BRepMesh_TorusRangeSplitter : public BRepMesh_UVParamRangeSplitter
{
public:
  //! Constructor.
  BRepMesh_TorusRangeSplitter() = default;

  //! Destructor.
  ~BRepMesh_TorusRangeSplitter() override = default;

  //! Returns list of nodes generated using surface data and specified parameters.
  Standard_EXPORT Handle(IMeshData::ListOfPnt2d) GenerateSurfaceNodes(
    const IMeshTools_Parameters& theParameters) const override;

  //! Registers border point.
  Standard_EXPORT void AddPoint(const gp_Pnt2d& thePoint) override;

private:
  Handle(IMeshData::SequenceOfReal) fillParams(
    const IMeshData::IMapOfReal&                 theParams,
    const std::pair<double, double>&             theRange,
    const int                                    theStepsNb,
    const double                                 theScale,
    const occ::handle<NCollection_IncAllocator>& theAllocator) const;

  double FUN_CalcAverageDUV(NCollection_Array1<double>& P, const int PLen) const;
};
