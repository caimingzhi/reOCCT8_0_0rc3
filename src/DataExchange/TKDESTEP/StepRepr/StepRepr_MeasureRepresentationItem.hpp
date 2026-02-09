#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>
class StepBasic_MeasureWithUnit;
class TCollection_HAsciiString;
class StepBasic_MeasureValueMember;
class StepBasic_Unit;

class StepRepr_MeasureRepresentationItem : public StepRepr_RepresentationItem
{

public:
  Standard_EXPORT StepRepr_MeasureRepresentationItem();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&     aName,
                            const occ::handle<StepBasic_MeasureValueMember>& aValueComponent,
                            const StepBasic_Unit&                            aUnitComponent);

  Standard_EXPORT void SetMeasure(const occ::handle<StepBasic_MeasureWithUnit>& Measure);

  Standard_EXPORT occ::handle<StepBasic_MeasureWithUnit> Measure() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_MeasureRepresentationItem, StepRepr_RepresentationItem)

private:
  occ::handle<StepBasic_MeasureWithUnit> myMeasure;
};
