#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>
class StepGeom_CartesianPoint;
class TCollection_HAsciiString;

class StepGeom_Placement : public StepGeom_GeometricRepresentationItem
{

public:
  //! Returns a Placement
  Standard_EXPORT StepGeom_Placement();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_CartesianPoint>&  aLocation);

  Standard_EXPORT void SetLocation(const occ::handle<StepGeom_CartesianPoint>& aLocation);

  Standard_EXPORT occ::handle<StepGeom_CartesianPoint> Location() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Placement, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepGeom_CartesianPoint> location;
};
