#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_ToroidalSurface.hpp>
class TCollection_HAsciiString;
class StepGeom_Axis2Placement3d;

class StepGeom_DegenerateToroidalSurface : public StepGeom_ToroidalSurface
{

public:
  Standard_EXPORT StepGeom_DegenerateToroidalSurface();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&  aName,
                            const occ::handle<StepGeom_Axis2Placement3d>& aPosition,
                            const double                                  aMajorRadius,
                            const double                                  aMinorRadius,
                            const bool                                    aSelectOuter);

  Standard_EXPORT void SetSelectOuter(const bool aSelectOuter);

  Standard_EXPORT bool SelectOuter() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_DegenerateToroidalSurface, StepGeom_ToroidalSurface)

private:
  bool selectOuter;
};
