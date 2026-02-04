#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>
class StepGeom_Direction;
class TCollection_HAsciiString;

class StepGeom_Vector : public StepGeom_GeometricRepresentationItem
{

public:
  //! Returns a Vector
  Standard_EXPORT StepGeom_Vector();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Direction>&       aOrientation,
                            const double                                 aMagnitude);

  Standard_EXPORT void SetOrientation(const occ::handle<StepGeom_Direction>& aOrientation);

  Standard_EXPORT occ::handle<StepGeom_Direction> Orientation() const;

  Standard_EXPORT void SetMagnitude(const double aMagnitude);

  Standard_EXPORT double Magnitude() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Vector, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepGeom_Direction> orientation;
  double                          magnitude;
};

