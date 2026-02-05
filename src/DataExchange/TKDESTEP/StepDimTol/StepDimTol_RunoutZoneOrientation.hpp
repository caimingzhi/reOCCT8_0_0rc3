#pragma once

#include <Standard_Transient.hpp>
#include <Standard.hpp>
#include <StepBasic_PlaneAngleMeasureWithUnit.hpp>

//! Added for Dimensional Tolerances
class StepDimTol_RunoutZoneOrientation : public Standard_Transient
{

public:
  Standard_EXPORT StepDimTol_RunoutZoneOrientation();

  //! Init all field own and inherited
  Standard_EXPORT void Init(const occ::handle<StepBasic_PlaneAngleMeasureWithUnit>& theAngle);

  //! Returns field Angle
  inline occ::handle<StepBasic_PlaneAngleMeasureWithUnit> Angle() { return myAngle; }

  //! Set field Angle
  inline void SetAngle(const occ::handle<StepBasic_PlaneAngleMeasureWithUnit>& theAngle)
  {
    myAngle = theAngle;
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_RunoutZoneOrientation, Standard_Transient)

private:
  occ::handle<StepBasic_PlaneAngleMeasureWithUnit> myAngle;
};
