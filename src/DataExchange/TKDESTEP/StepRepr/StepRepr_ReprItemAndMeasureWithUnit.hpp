#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>
class StepRepr_MeasureRepresentationItem;
class StepBasic_MeasureWithUnit;

class StepRepr_ReprItemAndMeasureWithUnit : public StepRepr_RepresentationItem
{

public:
  Standard_EXPORT StepRepr_ReprItemAndMeasureWithUnit();

  Standard_EXPORT void Init(const occ::handle<StepBasic_MeasureWithUnit>&   aMWU,
                            const occ::handle<StepRepr_RepresentationItem>& aRI);

  Standard_EXPORT occ::handle<StepRepr_MeasureRepresentationItem> GetMeasureRepresentationItem()
    const;

  Standard_EXPORT void SetMeasureWithUnit(const occ::handle<StepBasic_MeasureWithUnit>& aMWU);

  Standard_EXPORT occ::handle<StepBasic_MeasureWithUnit> GetMeasureWithUnit() const;

  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> GetRepresentationItem() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_ReprItemAndMeasureWithUnit, StepRepr_RepresentationItem)

private:
  occ::handle<StepRepr_MeasureRepresentationItem> myMeasureRepresentationItem;
  occ::handle<StepBasic_MeasureWithUnit>          myMeasureWithUnit;
};
