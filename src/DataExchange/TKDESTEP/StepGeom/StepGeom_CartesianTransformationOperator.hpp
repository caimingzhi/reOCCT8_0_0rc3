#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>
class StepGeom_Direction;
class StepGeom_CartesianPoint;
class TCollection_HAsciiString;

class StepGeom_CartesianTransformationOperator : public StepGeom_GeometricRepresentationItem
{

public:
  Standard_EXPORT StepGeom_CartesianTransformationOperator();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasAaxis1,
                            const occ::handle<StepGeom_Direction>&       aAxis1,
                            const bool                                   hasAaxis2,
                            const occ::handle<StepGeom_Direction>&       aAxis2,
                            const occ::handle<StepGeom_CartesianPoint>&  aLocalOrigin,
                            const bool                                   hasAscale,
                            const double                                 aScale);

  Standard_EXPORT void SetAxis1(const occ::handle<StepGeom_Direction>& aAxis1);

  Standard_EXPORT void UnSetAxis1();

  Standard_EXPORT occ::handle<StepGeom_Direction> Axis1() const;

  Standard_EXPORT bool HasAxis1() const;

  Standard_EXPORT void SetAxis2(const occ::handle<StepGeom_Direction>& aAxis2);

  Standard_EXPORT void UnSetAxis2();

  Standard_EXPORT occ::handle<StepGeom_Direction> Axis2() const;

  Standard_EXPORT bool HasAxis2() const;

  Standard_EXPORT void SetLocalOrigin(const occ::handle<StepGeom_CartesianPoint>& aLocalOrigin);

  Standard_EXPORT occ::handle<StepGeom_CartesianPoint> LocalOrigin() const;

  Standard_EXPORT void SetScale(const double aScale);

  Standard_EXPORT void UnSetScale();

  Standard_EXPORT double Scale() const;

  Standard_EXPORT bool HasScale() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_CartesianTransformationOperator,
                          StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepGeom_Direction>      axis1;
  occ::handle<StepGeom_Direction>      axis2;
  occ::handle<StepGeom_CartesianPoint> localOrigin;
  double                               scale;
  bool                                 hasAxis1;
  bool                                 hasAxis2;
  bool                                 hasScale;
};
