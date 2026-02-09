#pragma once

#include <BRepMesh_UVParamRangeSplitter.hpp>
#include <IMeshTools_Parameters.hpp>

class BRepMesh_TorusRangeSplitter : public BRepMesh_UVParamRangeSplitter
{
public:
  BRepMesh_TorusRangeSplitter() = default;

  ~BRepMesh_TorusRangeSplitter() override = default;

  Standard_EXPORT Handle(IMeshData::ListOfPnt2d) GenerateSurfaceNodes(
    const IMeshTools_Parameters& theParameters) const override;

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
