#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_Point.hpp>
class StepGeom_Curve;
class TCollection_HAsciiString;

class StepGeom_PointOnCurve : public StepGeom_Point
{

public:
  Standard_EXPORT StepGeom_PointOnCurve();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Curve>&           aBasisCurve,
                            const double                                 aPointParameter);

  Standard_EXPORT void SetBasisCurve(const occ::handle<StepGeom_Curve>& aBasisCurve);

  Standard_EXPORT occ::handle<StepGeom_Curve> BasisCurve() const;

  Standard_EXPORT void SetPointParameter(const double aPointParameter);

  Standard_EXPORT double PointParameter() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_PointOnCurve, StepGeom_Point)

private:
  occ::handle<StepGeom_Curve> basisCurve;
  double                      pointParameter;
};
