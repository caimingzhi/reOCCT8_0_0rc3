#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ParameterisationType.hpp>
#include <Standard_Integer.hpp>
class Geom_BSplineCurve;
class Geom_BoundedCurve;

//! Algorithm converts and concat several curve in an BSplineCurve
class GeomConvert_CompCurveToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  //! Initialize the algorithm
  //! - Parameterisation is used to convert
  Standard_EXPORT GeomConvert_CompCurveToBSplineCurve(
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);

  //! Initialize the algorithm with one curve
  //! - Parameterisation is used to convert
  Standard_EXPORT GeomConvert_CompCurveToBSplineCurve(
    const occ::handle<Geom_BoundedCurve>& BasisCurve,
    const Convert_ParameterisationType    Parameterisation = Convert_TgtThetaOver2);

  //! Append a curve in the BSpline Return False if the
  //! curve is not G0 with the BSplineCurve. Tolerance
  //! is used to check continuity and decrease
  //! Multiplicity at the common Knot until MinM
  //! if MinM = 0, the common Knot can be removed
  //!
  //! WithRatio defines whether the resulting curve should have a uniform
  //! parameterization. Setting WithRatio to false may greatly
  //! decrease the speed of algorithms like CPnts_AbscissaPoint::AdvPerform
  //! when applied to the resulting curve.
  Standard_EXPORT bool Add(const occ::handle<Geom_BoundedCurve>& NewCurve,
                           const double                          Tolerance,
                           const bool                            After     = false,
                           const bool                            WithRatio = true,
                           const int                             MinM      = 0);

  Standard_EXPORT occ::handle<Geom_BSplineCurve> BSplineCurve() const;

  //! Clear a result curve
  Standard_EXPORT void Clear();

private:
  //! Concat two BSplineCurves.
  Standard_EXPORT void Add(occ::handle<Geom_BSplineCurve>& FirstCurve,
                           occ::handle<Geom_BSplineCurve>& SecondCurve,
                           const bool                      After,
                           const bool                      WithRatio,
                           const int                       MinM);

  occ::handle<Geom_BSplineCurve> myCurve;
  double                         myTol;
  Convert_ParameterisationType   myType;
};
