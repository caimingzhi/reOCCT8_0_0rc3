#pragma once

#include <BRepMesh_UVParamRangeSplitter.hpp>
#include <IMeshData_Types.hpp>
#include <IMeshTools_Parameters.hpp>

class BRepMesh_NURBSRangeSplitter : public BRepMesh_UVParamRangeSplitter
{
public:
  BRepMesh_NURBSRangeSplitter()
      : mySurfaceType(GeomAbs_OtherSurface)
  {
  }

  ~BRepMesh_NURBSRangeSplitter() override = default;

  Standard_EXPORT void AdjustRange() override;

  Standard_EXPORT Handle(IMeshData::ListOfPnt2d) GenerateSurfaceNodes(
    const IMeshTools_Parameters& theParameters) const override;

protected:
  Standard_EXPORT virtual bool initParameters() const;

  Standard_EXPORT virtual int getUndefinedIntervalNb(
    const occ::handle<Adaptor3d_Surface>& theSurface,
    const bool                            isU,
    const GeomAbs_Shape                   theContinuity) const;

private:
  void getUndefinedInterval(const occ::handle<Adaptor3d_Surface>& theSurface,
                            const bool                            isU,
                            const GeomAbs_Shape                   theContinuity,
                            const std::pair<double, double>&      theRange,
                            NCollection_Array1<double>&           theIntervals) const;

  Handle(IMeshData::SequenceOfReal) computeGrainAndFilterParameters(
    const IMeshData::IMapOfReal&                 theSourceParams,
    const double                                 theTol2d,
    const double                                 theRangeDiff,
    const double                                 theDelta,
    const IMeshTools_Parameters&                 theParameters,
    const occ::handle<NCollection_IncAllocator>& theAllocator) const;

  Handle(IMeshData::SequenceOfReal) filterParameters(
    const IMeshData::IMapOfReal&                 theParams,
    const double                                 theMinDist,
    const double                                 theFilterDist,
    const occ::handle<NCollection_IncAllocator>& theAllocator) const;

  enum EdgeType
  {
    Edge_Internal,
    Edge_Frontier
  };

  enum ParamDimension
  {
    Param_U = 0x1,
    Param_V = 0x2
  };

  bool grabParamsOfEdges(const EdgeType theEdgeType, const int theParamDimensionFlag) const;

private:
  GeomAbs_SurfaceType mySurfaceType;
};
