#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_Logical.hpp>
#include <StepGeom_Curve.hpp>
class StepGeom_Direction;
class TCollection_HAsciiString;

class StepGeom_OffsetCurve3d : public StepGeom_Curve
{

public:
  //! Returns a OffsetCurve3d
  Standard_EXPORT StepGeom_OffsetCurve3d();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Curve>&           aBasisCurve,
                            const double                                 aDistance,
                            const StepData_Logical                       aSelfIntersect,
                            const occ::handle<StepGeom_Direction>&       aRefDirection);

  Standard_EXPORT void SetBasisCurve(const occ::handle<StepGeom_Curve>& aBasisCurve);

  Standard_EXPORT occ::handle<StepGeom_Curve> BasisCurve() const;

  Standard_EXPORT void SetDistance(const double aDistance);

  Standard_EXPORT double Distance() const;

  Standard_EXPORT void SetSelfIntersect(const StepData_Logical aSelfIntersect);

  Standard_EXPORT StepData_Logical SelfIntersect() const;

  Standard_EXPORT void SetRefDirection(const occ::handle<StepGeom_Direction>& aRefDirection);

  Standard_EXPORT occ::handle<StepGeom_Direction> RefDirection() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_OffsetCurve3d, StepGeom_Curve)

private:
  occ::handle<StepGeom_Curve>     basisCurve;
  double                          distance;
  StepData_Logical                selfIntersect;
  occ::handle<StepGeom_Direction> refDirection;
};
