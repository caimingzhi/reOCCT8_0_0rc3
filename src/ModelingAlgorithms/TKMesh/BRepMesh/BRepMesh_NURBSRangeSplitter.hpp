#pragma once

#include <BRepMesh_UVParamRangeSplitter.hpp>
#include <IMeshData_Types.hpp>
#include <IMeshTools_Parameters.hpp>

//! Auxiliary class extending UV range splitter in order to generate
//! internal nodes for NURBS surface.
class BRepMesh_NURBSRangeSplitter : public BRepMesh_UVParamRangeSplitter
{
public:
  //! Constructor.
  BRepMesh_NURBSRangeSplitter()
      : mySurfaceType(GeomAbs_OtherSurface)
  {
  }

  //! Destructor.
  ~BRepMesh_NURBSRangeSplitter() override = default;

  //! Updates discrete range of surface according to its geometric range.
  Standard_EXPORT void AdjustRange() override;

  //! Returns list of nodes generated using surface data and specified parameters.
  Standard_EXPORT Handle(IMeshData::ListOfPnt2d) GenerateSurfaceNodes(
    const IMeshTools_Parameters& theParameters) const override;

protected:
  //! Initializes U and V parameters lists using CN continuity intervals.
  Standard_EXPORT virtual bool initParameters() const;

  //! Returns number of intervals computed using available geometrical parameters.
  Standard_EXPORT virtual int getUndefinedIntervalNb(
    const occ::handle<Adaptor3d_Surface>& theSurface,
    const bool                            isU,
    const GeomAbs_Shape                   theContinuity) const;

private:
  //! Tries to compute intervals even for cases with no intervals
  //! at all using available geometrical parameters.
  void getUndefinedInterval(const occ::handle<Adaptor3d_Surface>& theSurface,
                            const bool                            isU,
                            const GeomAbs_Shape                   theContinuity,
                            const std::pair<double, double>&      theRange,
                            NCollection_Array1<double>&           theIntervals) const;

  //! Computes parameters of filter and applies it to the source parameters.
  Handle(IMeshData::SequenceOfReal) computeGrainAndFilterParameters(
    const IMeshData::IMapOfReal&                 theSourceParams,
    const double                                 theTol2d,
    const double                                 theRangeDiff,
    const double                                 theDelta,
    const IMeshTools_Parameters&                 theParameters,
    const occ::handle<NCollection_IncAllocator>& theAllocator) const;

  //! Filters parameters in order to avoid too dence distribution.
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

  //! Finds edges of discrete face and uses its points
  //! as auxiliary control parameters for generation of nodes.
  bool grabParamsOfEdges(const EdgeType theEdgeType, const int theParamDimensionFlag) const;

private:
  GeomAbs_SurfaceType mySurfaceType;
};
