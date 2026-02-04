#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ParameterisationType.hpp>
class Geom2d_BSplineCurve;
class Geom2d_BoundedCurve;

//! This algorithm converts and concat several curve in an BSplineCurve
class Geom2dConvert_CompCurveToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  //! Initialize the algorithm
  //! - Parameterisation is used to convert
  Standard_EXPORT Geom2dConvert_CompCurveToBSplineCurve(
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);

  //! Initialize the algorithm with one curve
  //! - Parameterisation is used to convert
  Standard_EXPORT Geom2dConvert_CompCurveToBSplineCurve(
    const occ::handle<Geom2d_BoundedCurve>& BasisCurve,
    const Convert_ParameterisationType      Parameterisation = Convert_TgtThetaOver2);

  //! Append a curve in the BSpline
  //! Return False if the curve is not G0 with the BSplineCurve.
  //! Tolerance is used to check continuity and decrease
  //! Multiplicity at the common Knot
  //! After is useful if BasisCurve is a closed curve .
  Standard_EXPORT bool Add(const occ::handle<Geom2d_BoundedCurve>& NewCurve,
                           const double                            Tolerance,
                           const bool                              After = false);

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> BSplineCurve() const;

  //! Clear result curve
  Standard_EXPORT void Clear();

private:
  //! Concat two BSplineCurves.
  Standard_EXPORT void Add(occ::handle<Geom2d_BSplineCurve>& FirstCurve,
                           occ::handle<Geom2d_BSplineCurve>& SecondCurve,
                           const bool                        After);

  occ::handle<Geom2d_BSplineCurve> myCurve;
  double                           myTol;
  Convert_ParameterisationType     myType;
};

