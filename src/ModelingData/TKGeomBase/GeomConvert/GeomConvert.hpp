#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
#include <Convert_ParameterisationType.hpp>
#include <Geom_BSplineCurve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Geom_BSplineCurve;
class Geom_BSplineSurface;
class Geom_Curve;
class Geom_Surface;

class GeomConvert
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Geom_BSplineCurve> SplitBSplineCurve(
    const occ::handle<Geom_BSplineCurve>& C,
    const int                             FromK1,
    const int                             ToK2,
    const bool                            SameOrientation = true);

  Standard_EXPORT static occ::handle<Geom_BSplineCurve> SplitBSplineCurve(
    const occ::handle<Geom_BSplineCurve>& C,
    const double                          FromU1,
    const double                          ToU2,
    const double                          ParametricTolerance,
    const bool                            SameOrientation = true);

  Standard_EXPORT static occ::handle<Geom_BSplineSurface> SplitBSplineSurface(
    const occ::handle<Geom_BSplineSurface>& S,
    const int                               FromUK1,
    const int                               ToUK2,
    const int                               FromVK1,
    const int                               ToVK2,
    const bool                              SameUOrientation = true,
    const bool                              SameVOrientation = true);

  Standard_EXPORT static occ::handle<Geom_BSplineSurface> SplitBSplineSurface(
    const occ::handle<Geom_BSplineSurface>& S,
    const int                               FromK1,
    const int                               ToK2,
    const bool                              USplit,
    const bool                              SameOrientation = true);

  Standard_EXPORT static occ::handle<Geom_BSplineSurface> SplitBSplineSurface(
    const occ::handle<Geom_BSplineSurface>& S,
    const double                            FromU1,
    const double                            ToU2,
    const double                            FromV1,
    const double                            ToV2,
    const double                            ParametricTolerance,
    const bool                              SameUOrientation = true,
    const bool                              SameVOrientation = true);

  Standard_EXPORT static occ::handle<Geom_BSplineSurface> SplitBSplineSurface(
    const occ::handle<Geom_BSplineSurface>& S,
    const double                            FromParam1,
    const double                            ToParam2,
    const bool                              USplit,
    const double                            ParametricTolerance,
    const bool                              SameOrientation = true);

  Standard_EXPORT static occ::handle<Geom_BSplineCurve> CurveToBSplineCurve(
    const occ::handle<Geom_Curve>&     C,
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);

  Standard_EXPORT static occ::handle<Geom_BSplineSurface> SurfaceToBSplineSurface(
    const occ::handle<Geom_Surface>& S);

  Standard_EXPORT static void ConcatG1(
    NCollection_Array1<occ::handle<Geom_BSplineCurve>>&               ArrayOfCurves,
    const NCollection_Array1<double>&                                 ArrayOfToler,
    occ::handle<NCollection_HArray1<occ::handle<Geom_BSplineCurve>>>& ArrayOfConcatenated,
    bool&                                                             ClosedFlag,
    const double                                                      ClosedTolerance);

  Standard_EXPORT static void ConcatC1(
    NCollection_Array1<occ::handle<Geom_BSplineCurve>>&               ArrayOfCurves,
    const NCollection_Array1<double>&                                 ArrayOfToler,
    occ::handle<NCollection_HArray1<int>>&                            ArrayOfIndices,
    occ::handle<NCollection_HArray1<occ::handle<Geom_BSplineCurve>>>& ArrayOfConcatenated,
    bool&                                                             ClosedFlag,
    const double                                                      ClosedTolerance);

  Standard_EXPORT static void ConcatC1(
    NCollection_Array1<occ::handle<Geom_BSplineCurve>>&               ArrayOfCurves,
    const NCollection_Array1<double>&                                 ArrayOfToler,
    occ::handle<NCollection_HArray1<int>>&                            ArrayOfIndices,
    occ::handle<NCollection_HArray1<occ::handle<Geom_BSplineCurve>>>& ArrayOfConcatenated,
    bool&                                                             ClosedFlag,
    const double                                                      ClosedTolerance,
    const double                                                      AngularTolerance);

  Standard_EXPORT static void C0BSplineToC1BSplineCurve(occ::handle<Geom_BSplineCurve>& BS,
                                                        const double                    tolerance,
                                                        const double AngularTolerance = 1.0e-7);

  Standard_EXPORT static void C0BSplineToArrayOfC1BSplineCurve(
    const occ::handle<Geom_BSplineCurve>&                             BS,
    occ::handle<NCollection_HArray1<occ::handle<Geom_BSplineCurve>>>& tabBS,
    const double                                                      tolerance);

  Standard_EXPORT static void C0BSplineToArrayOfC1BSplineCurve(
    const occ::handle<Geom_BSplineCurve>&                             BS,
    occ::handle<NCollection_HArray1<occ::handle<Geom_BSplineCurve>>>& tabBS,
    const double                                                      AngularTolerance,
    const double                                                      tolerance);
};
