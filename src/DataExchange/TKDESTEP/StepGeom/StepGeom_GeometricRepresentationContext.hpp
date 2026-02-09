#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <StepRepr_RepresentationContext.hpp>
class TCollection_HAsciiString;

class StepGeom_GeometricRepresentationContext : public StepRepr_RepresentationContext
{

public:
  Standard_EXPORT StepGeom_GeometricRepresentationContext();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aContextIdentifier,
                            const occ::handle<TCollection_HAsciiString>& aContextType,
                            const int                                    aCoordinateSpaceDimension);

  Standard_EXPORT void SetCoordinateSpaceDimension(const int aCoordinateSpaceDimension);

  Standard_EXPORT int CoordinateSpaceDimension() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_GeometricRepresentationContext, StepRepr_RepresentationContext)

private:
  int coordinateSpaceDimension;
};
