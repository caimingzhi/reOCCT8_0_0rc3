#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <Standard_Real.hpp>
#include <Extrema_ExtCS.hpp>
#include <GeomAPI_ProjectPointOnSurf.hpp>
#include <IntTools_MarkedRangeSet.hpp>
#include <IntTools_Range.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <IntTools_CurveRangeSample.hpp>
#include <NCollection_List.hpp>
#include <IntTools_SurfaceRangeSample.hpp>
class Geom_Surface;
class IntTools_Context;
class TopoDS_Edge;
class TopoDS_Face;
class IntTools_CurveRangeSample;
class Bnd_Box;
class IntTools_SurfaceRangeSample;
class IntTools_CurveRangeLocalizeData;
class IntTools_SurfaceRangeLocalizeData;

class IntTools_BeanFaceIntersector
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_BeanFaceIntersector();

  Standard_EXPORT IntTools_BeanFaceIntersector(const TopoDS_Edge& theEdge,
                                               const TopoDS_Face& theFace);

  Standard_EXPORT IntTools_BeanFaceIntersector(const BRepAdaptor_Curve&   theCurve,
                                               const BRepAdaptor_Surface& theSurface,
                                               const double               theBeanTolerance,
                                               const double               theFaceTolerance);

  Standard_EXPORT IntTools_BeanFaceIntersector(const BRepAdaptor_Curve&   theCurve,
                                               const BRepAdaptor_Surface& theSurface,
                                               const double               theFirstParOnCurve,
                                               const double               theLastParOnCurve,
                                               const double               theUMinParameter,
                                               const double               theUMaxParameter,
                                               const double               theVMinParameter,
                                               const double               theVMaxParameter,
                                               const double               theBeanTolerance,
                                               const double               theFaceTolerance);

  Standard_EXPORT void Init(const TopoDS_Edge& theEdge, const TopoDS_Face& theFace);

  Standard_EXPORT void Init(const BRepAdaptor_Curve&   theCurve,
                            const BRepAdaptor_Surface& theSurface,
                            const double               theBeanTolerance,
                            const double               theFaceTolerance);

  Standard_EXPORT void Init(const BRepAdaptor_Curve&   theCurve,
                            const BRepAdaptor_Surface& theSurface,
                            const double               theFirstParOnCurve,
                            const double               theLastParOnCurve,
                            const double               theUMinParameter,
                            const double               theUMaxParameter,
                            const double               theVMinParameter,
                            const double               theVMaxParameter,
                            const double               theBeanTolerance,
                            const double               theFaceTolerance);

  Standard_EXPORT void SetContext(const occ::handle<IntTools_Context>& theContext);

  Standard_EXPORT const occ::handle<IntTools_Context>& Context() const;

  Standard_EXPORT void SetBeanParameters(const double theFirstParOnCurve,
                                         const double theLastParOnCurve);

  Standard_EXPORT void SetSurfaceParameters(const double theUMinParameter,
                                            const double theUMaxParameter,
                                            const double theVMinParameter,
                                            const double theVMaxParameter);

  Standard_EXPORT void Perform();

  bool IsDone() const { return myIsDone; }

  Standard_EXPORT const NCollection_Sequence<IntTools_Range>& Result() const;

  Standard_EXPORT void Result(NCollection_Sequence<IntTools_Range>& theResults) const;

  double MinimalSquareDistance() const { return myMinSqDistance; }

private:
  Standard_EXPORT void ComputeAroundExactIntersection();

  Standard_EXPORT void ComputeLinePlane();

  Standard_EXPORT bool FastComputeAnalytic();

  Standard_EXPORT void ComputeUsingExtremum();

  Standard_EXPORT void ComputeNearRangeBoundaries();

  Standard_EXPORT bool ComputeLocalized();

  Standard_EXPORT void ComputeRangeFromStartPoint(const bool   ToIncreaseParameter,
                                                  const double theParameter,
                                                  const double theUParameter,
                                                  const double theVParameter);

  Standard_EXPORT void ComputeRangeFromStartPoint(const bool   ToIncreaseParameter,
                                                  const double theParameter,
                                                  const double theUParameter,
                                                  const double theVParameter,
                                                  const int    theIndex);

  Standard_EXPORT double Distance(const double theArg,
                                  double&      theUParameter,
                                  double&      theVParameter);

  Standard_EXPORT double Distance(const double theArg);

  Standard_EXPORT bool LocalizeSolutions(
    const IntTools_CurveRangeSample&               theCurveRange,
    const Bnd_Box&                                 theBoxCurve,
    const IntTools_SurfaceRangeSample&             theSurfaceRange,
    const Bnd_Box&                                 theBoxSurface,
    IntTools_CurveRangeLocalizeData&               theCurveData,
    IntTools_SurfaceRangeLocalizeData&             theSurfaceData,
    NCollection_List<IntTools_CurveRangeSample>&   theListCurveRange,
    NCollection_List<IntTools_SurfaceRangeSample>& theListSurfaceRange);

  Standard_EXPORT bool TestComputeCoinside();

  BRepAdaptor_Curve                    myCurve;
  BRepAdaptor_Surface                  mySurface;
  occ::handle<Geom_Surface>            myTrsfSurface;
  double                               myFirstParameter;
  double                               myLastParameter;
  double                               myUMinParameter;
  double                               myUMaxParameter;
  double                               myVMinParameter;
  double                               myVMaxParameter;
  double                               myBeanTolerance;
  double                               myFaceTolerance;
  double                               myCurveResolution;
  double                               myCriteria;
  GeomAPI_ProjectPointOnSurf           myProjector;
  IntTools_MarkedRangeSet              myRangeManager;
  occ::handle<IntTools_Context>        myContext;
  NCollection_Sequence<IntTools_Range> myResults;
  bool                                 myIsDone;
  double                               myMinSqDistance;
};
