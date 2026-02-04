#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>
class StepGeom_Axis1Placement;
class TCollection_HAsciiString;

class StepShape_RightCircularCylinder : public StepGeom_GeometricRepresentationItem
{

public:
  //! Returns a RightCircularCylinder
  Standard_EXPORT StepShape_RightCircularCylinder();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Axis1Placement>&  aPosition,
                            const double                                 aHeight,
                            const double                                 aRadius);

  Standard_EXPORT void SetPosition(const occ::handle<StepGeom_Axis1Placement>& aPosition);

  Standard_EXPORT occ::handle<StepGeom_Axis1Placement> Position() const;

  Standard_EXPORT void SetHeight(const double aHeight);

  Standard_EXPORT double Height() const;

  Standard_EXPORT void SetRadius(const double aRadius);

  Standard_EXPORT double Radius() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_RightCircularCylinder, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepGeom_Axis1Placement> position;
  double                               height;
  double                               radius;
};

