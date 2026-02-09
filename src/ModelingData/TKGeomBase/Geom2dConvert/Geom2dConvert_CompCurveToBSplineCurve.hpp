#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ParameterisationType.hpp>
class Geom2d_BSplineCurve;
class Geom2d_BoundedCurve;

class Geom2dConvert_CompCurveToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dConvert_CompCurveToBSplineCurve(
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);

  Standard_EXPORT Geom2dConvert_CompCurveToBSplineCurve(
    const occ::handle<Geom2d_BoundedCurve>& BasisCurve,
    const Convert_ParameterisationType      Parameterisation = Convert_TgtThetaOver2);

  Standard_EXPORT bool Add(const occ::handle<Geom2d_BoundedCurve>& NewCurve,
                           const double                            Tolerance,
                           const bool                              After = false);

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> BSplineCurve() const;

  Standard_EXPORT void Clear();

private:
  Standard_EXPORT void Add(occ::handle<Geom2d_BSplineCurve>& FirstCurve,
                           occ::handle<Geom2d_BSplineCurve>& SecondCurve,
                           const bool                        After);

  occ::handle<Geom2d_BSplineCurve> myCurve;
  double                           myTol;
  Convert_ParameterisationType     myType;
};
