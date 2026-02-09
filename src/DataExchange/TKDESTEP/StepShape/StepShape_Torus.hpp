#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>
class StepGeom_Axis1Placement;
class TCollection_HAsciiString;

class StepShape_Torus : public StepGeom_GeometricRepresentationItem
{

public:
  Standard_EXPORT StepShape_Torus();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Axis1Placement>&  aPosition,
                            const double                                 aMajorRadius,
                            const double                                 aMinorRadius);

  Standard_EXPORT void SetPosition(const occ::handle<StepGeom_Axis1Placement>& aPosition);

  Standard_EXPORT occ::handle<StepGeom_Axis1Placement> Position() const;

  Standard_EXPORT void SetMajorRadius(const double aMajorRadius);

  Standard_EXPORT double MajorRadius() const;

  Standard_EXPORT void SetMinorRadius(const double aMinorRadius);

  Standard_EXPORT double MinorRadius() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_Torus, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepGeom_Axis1Placement> position;
  double                               majorRadius;
  double                               minorRadius;
};
