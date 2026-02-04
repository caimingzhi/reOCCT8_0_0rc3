#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationContext.hpp>
#include <Standard_Integer.hpp>
#include <StepBasic_NamedUnit.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_UncertaintyMeasureWithUnit.hpp>
class StepGeom_GeometricRepresentationContext;
class StepRepr_GlobalUnitAssignedContext;
class StepRepr_GlobalUncertaintyAssignedContext;
class TCollection_HAsciiString;
class StepBasic_NamedUnit;
class StepBasic_UncertaintyMeasureWithUnit;

class StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx
    : public StepRepr_RepresentationContext
{

public:
  Standard_EXPORT StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                  aContextIdentifier,
    const occ::handle<TCollection_HAsciiString>&                  aContextType,
    const occ::handle<StepGeom_GeometricRepresentationContext>&   aGeometricRepresentationCtx,
    const occ::handle<StepRepr_GlobalUnitAssignedContext>&        aGlobalUnitAssignedCtx,
    const occ::handle<StepRepr_GlobalUncertaintyAssignedContext>& aGlobalUncertaintyAssignedCtx);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aContextIdentifier,
    const occ::handle<TCollection_HAsciiString>& aContextType,
    const int                                    aCoordinateSpaceDimension,
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>& aUnits,
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>>&
      anUncertainty);

  Standard_EXPORT void SetGeometricRepresentationContext(
    const occ::handle<StepGeom_GeometricRepresentationContext>& aGeometricRepresentationContext);

  Standard_EXPORT occ::handle<StepGeom_GeometricRepresentationContext>
                  GeometricRepresentationContext() const;

  Standard_EXPORT void SetGlobalUnitAssignedContext(
    const occ::handle<StepRepr_GlobalUnitAssignedContext>& aGlobalUnitAssignedContext);

  Standard_EXPORT occ::handle<StepRepr_GlobalUnitAssignedContext> GlobalUnitAssignedContext() const;

  Standard_EXPORT void SetGlobalUncertaintyAssignedContext(
    const occ::handle<StepRepr_GlobalUncertaintyAssignedContext>& aGlobalUncertaintyAssignedCtx);

  Standard_EXPORT occ::handle<StepRepr_GlobalUncertaintyAssignedContext>
                  GlobalUncertaintyAssignedContext() const;

  Standard_EXPORT void SetCoordinateSpaceDimension(const int aCoordinateSpaceDimension);

  Standard_EXPORT int CoordinateSpaceDimension() const;

  Standard_EXPORT void SetUnits(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>& aUnits);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>> Units() const;

  Standard_EXPORT occ::handle<StepBasic_NamedUnit> UnitsValue(const int num) const;

  Standard_EXPORT int NbUnits() const;

  Standard_EXPORT void SetUncertainty(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>>&
      aUncertainty);

  Standard_EXPORT occ::handle<
    NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>>
    Uncertainty() const;

  Standard_EXPORT occ::handle<StepBasic_UncertaintyMeasureWithUnit> UncertaintyValue(
    const int num) const;

  Standard_EXPORT int NbUncertainty() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx,
                          StepRepr_RepresentationContext)

private:
  occ::handle<StepGeom_GeometricRepresentationContext>   geometricRepresentationContext;
  occ::handle<StepRepr_GlobalUnitAssignedContext>        globalUnitAssignedContext;
  occ::handle<StepRepr_GlobalUncertaintyAssignedContext> globalUncertaintyAssignedContext;
};

