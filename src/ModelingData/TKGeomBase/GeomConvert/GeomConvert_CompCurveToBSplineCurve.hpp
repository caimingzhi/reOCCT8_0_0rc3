#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ParameterisationType.hpp>
#include <Standard_Integer.hpp>
class Geom_BSplineCurve;
class Geom_BoundedCurve;

class GeomConvert_CompCurveToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomConvert_CompCurveToBSplineCurve(
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);

  Standard_EXPORT GeomConvert_CompCurveToBSplineCurve(
    const occ::handle<Geom_BoundedCurve>& BasisCurve,
    const Convert_ParameterisationType    Parameterisation = Convert_TgtThetaOver2);

  Standard_EXPORT bool Add(const occ::handle<Geom_BoundedCurve>& NewCurve,
                           const double                          Tolerance,
                           const bool                            After     = false,
                           const bool                            WithRatio = true,
                           const int                             MinM      = 0);

  Standard_EXPORT occ::handle<Geom_BSplineCurve> BSplineCurve() const;

  Standard_EXPORT void Clear();

private:
  Standard_EXPORT void Add(occ::handle<Geom_BSplineCurve>& FirstCurve,
                           occ::handle<Geom_BSplineCurve>& SecondCurve,
                           const bool                      After,
                           const bool                      WithRatio,
                           const int                       MinM);

  occ::handle<Geom_BSplineCurve> myCurve;
  double                         myTol;
  Convert_ParameterisationType   myType;
};
