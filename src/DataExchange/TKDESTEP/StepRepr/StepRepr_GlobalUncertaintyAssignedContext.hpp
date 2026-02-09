#pragma once

#include <Standard.hpp>

#include <StepBasic_UncertaintyMeasureWithUnit.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepBasic_UncertaintyMeasureWithUnit;

class StepRepr_GlobalUncertaintyAssignedContext : public StepRepr_RepresentationContext
{

public:
  Standard_EXPORT StepRepr_GlobalUncertaintyAssignedContext();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aContextIdentifier,
    const occ::handle<TCollection_HAsciiString>& aContextType,
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>>&
      aUncertainty);

  Standard_EXPORT void SetUncertainty(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>>&
      aUncertainty);

  Standard_EXPORT occ::handle<
    NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>>
    Uncertainty() const;

  Standard_EXPORT occ::handle<StepBasic_UncertaintyMeasureWithUnit> UncertaintyValue(
    const int num) const;

  Standard_EXPORT int NbUncertainty() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_GlobalUncertaintyAssignedContext, StepRepr_RepresentationContext)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_UncertaintyMeasureWithUnit>>> uncertainty;
};
