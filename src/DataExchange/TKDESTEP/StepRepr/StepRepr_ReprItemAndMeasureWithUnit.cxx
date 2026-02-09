#include <Standard_Type.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepRepr_MeasureRepresentationItem.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_ReprItemAndMeasureWithUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ReprItemAndMeasureWithUnit, StepRepr_RepresentationItem)

StepRepr_ReprItemAndMeasureWithUnit::StepRepr_ReprItemAndMeasureWithUnit()
{
  myMeasureWithUnit           = new StepBasic_MeasureWithUnit();
  myMeasureRepresentationItem = new StepRepr_MeasureRepresentationItem();
}

void StepRepr_ReprItemAndMeasureWithUnit::Init(const occ::handle<StepBasic_MeasureWithUnit>&   aMWU,
                                               const occ::handle<StepRepr_RepresentationItem>& aRI)
{
  myMeasureWithUnit = aMWU;
  SetName(aRI->Name());
}

occ::handle<StepRepr_MeasureRepresentationItem> StepRepr_ReprItemAndMeasureWithUnit::
  GetMeasureRepresentationItem() const
{
  return myMeasureRepresentationItem;
}

void StepRepr_ReprItemAndMeasureWithUnit::SetMeasureWithUnit(
  const occ::handle<StepBasic_MeasureWithUnit>& aMWU)
{
  myMeasureWithUnit = aMWU;
}

occ::handle<StepBasic_MeasureWithUnit> StepRepr_ReprItemAndMeasureWithUnit::GetMeasureWithUnit()
  const
{
  return myMeasureWithUnit;
}

occ::handle<StepRepr_RepresentationItem> StepRepr_ReprItemAndMeasureWithUnit::
  GetRepresentationItem() const
{
  occ::handle<StepRepr_RepresentationItem> RI = new StepRepr_RepresentationItem();
  RI->Init(Name());
  return RI;
}
