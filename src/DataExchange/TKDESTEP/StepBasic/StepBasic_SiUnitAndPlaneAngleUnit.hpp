#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_SiUnit.hpp>
#include <StepBasic_SiPrefix.hpp>
#include <StepBasic_SiUnitName.hpp>
class StepBasic_PlaneAngleUnit;

class StepBasic_SiUnitAndPlaneAngleUnit : public StepBasic_SiUnit
{

public:
  //! Returns a SiUnitAndPlaneAngleUnit
  Standard_EXPORT StepBasic_SiUnitAndPlaneAngleUnit();

  Standard_EXPORT void Init(const bool                 hasAprefix,
                            const StepBasic_SiPrefix   aPrefix,
                            const StepBasic_SiUnitName aName);

  Standard_EXPORT void SetPlaneAngleUnit(
    const occ::handle<StepBasic_PlaneAngleUnit>& aPlaneAngleUnit);

  Standard_EXPORT occ::handle<StepBasic_PlaneAngleUnit> PlaneAngleUnit() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SiUnitAndPlaneAngleUnit, StepBasic_SiUnit)

private:
  occ::handle<StepBasic_PlaneAngleUnit> planeAngleUnit;
};

