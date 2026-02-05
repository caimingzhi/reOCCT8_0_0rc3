#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_SweptFaceSolid.hpp>
class StepGeom_Axis1Placement;
class TCollection_HAsciiString;
class StepShape_FaceSurface;

class StepShape_RevolvedFaceSolid : public StepShape_SweptFaceSolid
{

public:
  //! Returns a RevolvedFaceSolid
  Standard_EXPORT StepShape_RevolvedFaceSolid();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_FaceSurface>&    aSweptArea);

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_FaceSurface>&    aSweptArea,
                            const occ::handle<StepGeom_Axis1Placement>&  aAxis,
                            const double                                 aAngle);

  Standard_EXPORT void SetAxis(const occ::handle<StepGeom_Axis1Placement>& aAxis);

  Standard_EXPORT occ::handle<StepGeom_Axis1Placement> Axis() const;

  Standard_EXPORT void SetAngle(const double aAngle);

  Standard_EXPORT double Angle() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_RevolvedFaceSolid, StepShape_SweptFaceSolid)

private:
  occ::handle<StepGeom_Axis1Placement> axis;
  double                               angle;
};
