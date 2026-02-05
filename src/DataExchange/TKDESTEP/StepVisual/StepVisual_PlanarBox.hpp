#pragma once

#include <Standard.hpp>

#include <StepGeom_Axis2Placement.hpp>
#include <StepVisual_PlanarExtent.hpp>
#include <Standard_Real.hpp>
class TCollection_HAsciiString;

class StepVisual_PlanarBox : public StepVisual_PlanarExtent
{

public:
  //! Returns a PlanarBox
  Standard_EXPORT StepVisual_PlanarBox();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const double                                 aSizeInX,
                            const double                                 aSizeInY,
                            const StepGeom_Axis2Placement&               aPlacement);

  Standard_EXPORT void SetPlacement(const StepGeom_Axis2Placement& aPlacement);

  Standard_EXPORT StepGeom_Axis2Placement Placement() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_PlanarBox, StepVisual_PlanarExtent)

private:
  StepGeom_Axis2Placement placement;
};
