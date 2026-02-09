#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationContext.hpp>
#include <Standard_Integer.hpp>
#include <StepBasic_NamedUnit.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class StepGeom_GeometricRepresentationContext;
class StepRepr_GlobalUnitAssignedContext;
class TCollection_HAsciiString;
class StepBasic_NamedUnit;

class StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext
    : public StepRepr_RepresentationContext
{

public:
  Standard_EXPORT StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                aContextIdentifier,
    const occ::handle<TCollection_HAsciiString>&                aContextType,
    const occ::handle<StepGeom_GeometricRepresentationContext>& aGeometricRepresentationContext,
    const occ::handle<StepRepr_GlobalUnitAssignedContext>&      aGlobalUnitAssignedContext);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aContextIdentifier,
    const occ::handle<TCollection_HAsciiString>& aContextType,
    const int                                    aCoordinateSpaceDimension,
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>& aUnits);

  Standard_EXPORT void SetGeometricRepresentationContext(
    const occ::handle<StepGeom_GeometricRepresentationContext>& aGeometricRepresentationContext);

  Standard_EXPORT occ::handle<StepGeom_GeometricRepresentationContext>
                  GeometricRepresentationContext() const;

  Standard_EXPORT void SetGlobalUnitAssignedContext(
    const occ::handle<StepRepr_GlobalUnitAssignedContext>& aGlobalUnitAssignedContext);

  Standard_EXPORT occ::handle<StepRepr_GlobalUnitAssignedContext> GlobalUnitAssignedContext() const;

  Standard_EXPORT void SetCoordinateSpaceDimension(const int aCoordinateSpaceDimension);

  Standard_EXPORT int CoordinateSpaceDimension() const;

  Standard_EXPORT void SetUnits(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>& aUnits);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>> Units() const;

  Standard_EXPORT occ::handle<StepBasic_NamedUnit> UnitsValue(const int num) const;

  Standard_EXPORT int NbUnits() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext,
                          StepRepr_RepresentationContext)

private:
  occ::handle<StepGeom_GeometricRepresentationContext> geometricRepresentationContext;
  occ::handle<StepRepr_GlobalUnitAssignedContext>      globalUnitAssignedContext;
};
