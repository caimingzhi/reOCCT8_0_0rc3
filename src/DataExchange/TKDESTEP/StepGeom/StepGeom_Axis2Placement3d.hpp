#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <StepGeom_Placement.hpp>
class StepGeom_Direction;
class TCollection_HAsciiString;
class StepGeom_CartesianPoint;

class StepGeom_Axis2Placement3d : public StepGeom_Placement
{

public:
  //! Returns a Axis2Placement3d
  Standard_EXPORT StepGeom_Axis2Placement3d();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_CartesianPoint>&  aLocation,
                            const bool                                   hasAaxis,
                            const occ::handle<StepGeom_Direction>&       aAxis,
                            const bool                                   hasArefDirection,
                            const occ::handle<StepGeom_Direction>&       aRefDirection);

  Standard_EXPORT void SetAxis(const occ::handle<StepGeom_Direction>& aAxis);

  Standard_EXPORT void UnSetAxis();

  Standard_EXPORT occ::handle<StepGeom_Direction> Axis() const;

  Standard_EXPORT bool HasAxis() const;

  Standard_EXPORT void SetRefDirection(const occ::handle<StepGeom_Direction>& aRefDirection);

  Standard_EXPORT void UnSetRefDirection();

  Standard_EXPORT occ::handle<StepGeom_Direction> RefDirection() const;

  Standard_EXPORT bool HasRefDirection() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Axis2Placement3d, StepGeom_Placement)

private:
  occ::handle<StepGeom_Direction> axis;
  occ::handle<StepGeom_Direction> refDirection;
  bool                            hasAxis;
  bool                            hasRefDirection;
};

