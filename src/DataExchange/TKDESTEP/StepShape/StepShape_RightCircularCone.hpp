#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>
class StepGeom_Axis1Placement;
class TCollection_HAsciiString;

class StepShape_RightCircularCone : public StepGeom_GeometricRepresentationItem
{

public:
  //! Returns a RightCircularCone
  Standard_EXPORT StepShape_RightCircularCone();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Axis1Placement>&  aPosition,
                            const double                                 aHeight,
                            const double                                 aRadius,
                            const double                                 aSemiAngle);

  Standard_EXPORT void SetPosition(const occ::handle<StepGeom_Axis1Placement>& aPosition);

  Standard_EXPORT occ::handle<StepGeom_Axis1Placement> Position() const;

  Standard_EXPORT void SetHeight(const double aHeight);

  Standard_EXPORT double Height() const;

  Standard_EXPORT void SetRadius(const double aRadius);

  Standard_EXPORT double Radius() const;

  Standard_EXPORT void SetSemiAngle(const double aSemiAngle);

  Standard_EXPORT double SemiAngle() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_RightCircularCone, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepGeom_Axis1Placement> position;
  double                               height;
  double                               radius;
  double                               semiAngle;
};

