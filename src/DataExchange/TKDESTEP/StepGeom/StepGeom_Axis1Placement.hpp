#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <StepGeom_Placement.hpp>
class StepGeom_Direction;
class TCollection_HAsciiString;
class StepGeom_CartesianPoint;

class StepGeom_Axis1Placement : public StepGeom_Placement
{

public:
  Standard_EXPORT StepGeom_Axis1Placement();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_CartesianPoint>&  aLocation,
                            const bool                                   hasAaxis,
                            const occ::handle<StepGeom_Direction>&       aAxis);

  Standard_EXPORT void SetAxis(const occ::handle<StepGeom_Direction>& aAxis);

  Standard_EXPORT void UnSetAxis();

  Standard_EXPORT occ::handle<StepGeom_Direction> Axis() const;

  Standard_EXPORT bool HasAxis() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Axis1Placement, StepGeom_Placement)

private:
  occ::handle<StepGeom_Direction> axis;
  bool                            hasAxis;
};
