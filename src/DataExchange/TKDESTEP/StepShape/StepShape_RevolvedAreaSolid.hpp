#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_SweptAreaSolid.hpp>
class StepGeom_Axis1Placement;
class TCollection_HAsciiString;
class StepGeom_CurveBoundedSurface;

class StepShape_RevolvedAreaSolid : public StepShape_SweptAreaSolid
{

public:
  Standard_EXPORT StepShape_RevolvedAreaSolid();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&     aName,
                            const occ::handle<StepGeom_CurveBoundedSurface>& aSweptArea,
                            const occ::handle<StepGeom_Axis1Placement>&      aAxis,
                            const double                                     aAngle);

  Standard_EXPORT void SetAxis(const occ::handle<StepGeom_Axis1Placement>& aAxis);

  Standard_EXPORT occ::handle<StepGeom_Axis1Placement> Axis() const;

  Standard_EXPORT void SetAngle(const double aAngle);

  Standard_EXPORT double Angle() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_RevolvedAreaSolid, StepShape_SweptAreaSolid)

private:
  occ::handle<StepGeom_Axis1Placement> axis;
  double                               angle;
};
