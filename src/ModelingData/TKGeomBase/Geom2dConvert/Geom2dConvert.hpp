#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
#include <Convert_ParameterisationType.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Geom2d_BSplineCurve;
class Geom2d_Curve;

class Geom2dConvert
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Geom2d_BSplineCurve> SplitBSplineCurve(
    const occ::handle<Geom2d_BSplineCurve>& C,
    const int                               FromK1,
    const int                               ToK2,
    const bool                              SameOrientation = true);

  Standard_EXPORT static occ::handle<Geom2d_BSplineCurve> SplitBSplineCurve(
    const occ::handle<Geom2d_BSplineCurve>& C,
    const double                            FromU1,
    const double                            ToU2,
    const double                            ParametricTolerance,
    const bool                              SameOrientation = true);

  Standard_EXPORT static occ::handle<Geom2d_BSplineCurve> CurveToBSplineCurve(
    const occ::handle<Geom2d_Curve>&   C,
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);

  Standard_EXPORT static void ConcatG1(
    NCollection_Array1<occ::handle<Geom2d_BSplineCurve>>&               ArrayOfCurves,
    const NCollection_Array1<double>&                                   ArrayOfToler,
    occ::handle<NCollection_HArray1<occ::handle<Geom2d_BSplineCurve>>>& ArrayOfConcatenated,
    bool&                                                               ClosedFlag,
    const double                                                        ClosedTolerance);

  Standard_EXPORT static void ConcatC1(
    NCollection_Array1<occ::handle<Geom2d_BSplineCurve>>&               ArrayOfCurves,
    const NCollection_Array1<double>&                                   ArrayOfToler,
    occ::handle<NCollection_HArray1<int>>&                              ArrayOfIndices,
    occ::handle<NCollection_HArray1<occ::handle<Geom2d_BSplineCurve>>>& ArrayOfConcatenated,
    bool&                                                               ClosedFlag,
    const double                                                        ClosedTolerance);

  Standard_EXPORT static void ConcatC1(
    NCollection_Array1<occ::handle<Geom2d_BSplineCurve>>&               ArrayOfCurves,
    const NCollection_Array1<double>&                                   ArrayOfToler,
    occ::handle<NCollection_HArray1<int>>&                              ArrayOfIndices,
    occ::handle<NCollection_HArray1<occ::handle<Geom2d_BSplineCurve>>>& ArrayOfConcatenated,
    bool&                                                               ClosedFlag,
    const double                                                        ClosedTolerance,
    const double                                                        AngularTolerance);

  Standard_EXPORT static void C0BSplineToC1BSplineCurve(occ::handle<Geom2d_BSplineCurve>& BS,
                                                        const double Tolerance);

  Standard_EXPORT static void C0BSplineToArrayOfC1BSplineCurve(
    const occ::handle<Geom2d_BSplineCurve>&                             BS,
    occ::handle<NCollection_HArray1<occ::handle<Geom2d_BSplineCurve>>>& tabBS,
    const double                                                        Tolerance);

  Standard_EXPORT static void C0BSplineToArrayOfC1BSplineCurve(
    const occ::handle<Geom2d_BSplineCurve>&                             BS,
    occ::handle<NCollection_HArray1<occ::handle<Geom2d_BSplineCurve>>>& tabBS,
    const double                                                        AngularTolerance,
    const double                                                        Tolerance);
};
