#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_SweptFaceSolid.hpp>
class StepGeom_Direction;
class TCollection_HAsciiString;
class StepShape_FaceSurface;

class StepShape_ExtrudedFaceSolid : public StepShape_SweptFaceSolid
{

public:
  Standard_EXPORT StepShape_ExtrudedFaceSolid();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_FaceSurface>&    aSweptArea,
                            const occ::handle<StepGeom_Direction>&       aExtrudedDirection,
                            const double                                 aDepth);

  Standard_EXPORT void SetExtrudedDirection(
    const occ::handle<StepGeom_Direction>& aExtrudedDirection);

  Standard_EXPORT occ::handle<StepGeom_Direction> ExtrudedDirection() const;

  Standard_EXPORT void SetDepth(const double aDepth);

  Standard_EXPORT double Depth() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_ExtrudedFaceSolid, StepShape_SweptFaceSolid)

private:
  occ::handle<StepGeom_Direction> extrudedDirection;
  double                          depth;
};
