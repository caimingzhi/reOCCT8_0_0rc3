#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_SweptAreaSolid.hpp>
class StepGeom_Direction;
class TCollection_HAsciiString;
class StepGeom_CurveBoundedSurface;

class StepShape_ExtrudedAreaSolid : public StepShape_SweptAreaSolid
{

public:
  //! Returns a ExtrudedAreaSolid
  Standard_EXPORT StepShape_ExtrudedAreaSolid();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&     aName,
                            const occ::handle<StepGeom_CurveBoundedSurface>& aSweptArea,
                            const occ::handle<StepGeom_Direction>&           aExtrudedDirection,
                            const double                                     aDepth);

  Standard_EXPORT void SetExtrudedDirection(
    const occ::handle<StepGeom_Direction>& aExtrudedDirection);

  Standard_EXPORT occ::handle<StepGeom_Direction> ExtrudedDirection() const;

  Standard_EXPORT void SetDepth(const double aDepth);

  Standard_EXPORT double Depth() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_ExtrudedAreaSolid, StepShape_SweptAreaSolid)

private:
  occ::handle<StepGeom_Direction> extrudedDirection;
  double                          depth;
};

