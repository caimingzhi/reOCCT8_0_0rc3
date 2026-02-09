#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationContext.hpp>
#include <Standard_Integer.hpp>
class StepGeom_GeometricRepresentationContext;
class StepRepr_ParametricRepresentationContext;
class TCollection_HAsciiString;

class StepGeom_GeometricRepresentationContextAndParametricRepresentationContext
    : public StepRepr_RepresentationContext
{

public:
  Standard_EXPORT StepGeom_GeometricRepresentationContextAndParametricRepresentationContext();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                 aContextIdentifier,
    const occ::handle<TCollection_HAsciiString>&                 aContextType,
    const occ::handle<StepGeom_GeometricRepresentationContext>&  aGeometricRepresentationContext,
    const occ::handle<StepRepr_ParametricRepresentationContext>& aParametricRepresentationContext);

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aContextIdentifier,
                            const occ::handle<TCollection_HAsciiString>& aContextType,
                            const int                                    aCoordinateSpaceDimension);

  Standard_EXPORT void SetGeometricRepresentationContext(
    const occ::handle<StepGeom_GeometricRepresentationContext>& aGeometricRepresentationContext);

  Standard_EXPORT occ::handle<StepGeom_GeometricRepresentationContext>
                  GeometricRepresentationContext() const;

  Standard_EXPORT void SetParametricRepresentationContext(
    const occ::handle<StepRepr_ParametricRepresentationContext>& aParametricRepresentationContext);

  Standard_EXPORT occ::handle<StepRepr_ParametricRepresentationContext>
                  ParametricRepresentationContext() const;

  Standard_EXPORT void SetCoordinateSpaceDimension(const int aCoordinateSpaceDimension);

  Standard_EXPORT int CoordinateSpaceDimension() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_GeometricRepresentationContextAndParametricRepresentationContext,
                          StepRepr_RepresentationContext)

private:
  occ::handle<StepGeom_GeometricRepresentationContext>  geometricRepresentationContext;
  occ::handle<StepRepr_ParametricRepresentationContext> parametricRepresentationContext;
};
