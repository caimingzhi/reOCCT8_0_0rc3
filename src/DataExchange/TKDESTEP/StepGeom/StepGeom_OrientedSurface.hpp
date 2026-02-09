#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <StepGeom_Surface.hpp>
class TCollection_HAsciiString;

class StepGeom_OrientedSurface : public StepGeom_Surface
{

public:
  Standard_EXPORT StepGeom_OrientedSurface();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const bool                                   aOrientation);

  Standard_EXPORT bool Orientation() const;

  Standard_EXPORT void SetOrientation(const bool Orientation);

  DEFINE_STANDARD_RTTIEXT(StepGeom_OrientedSurface, StepGeom_Surface)

private:
  bool theOrientation;
};
