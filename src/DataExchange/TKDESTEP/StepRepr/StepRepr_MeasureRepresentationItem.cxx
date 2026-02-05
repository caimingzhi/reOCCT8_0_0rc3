#include <Standard_Type.hpp>
#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_Unit.hpp>
#include <StepRepr_MeasureRepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_MeasureRepresentationItem, StepRepr_RepresentationItem)

//=================================================================================================

StepRepr_MeasureRepresentationItem::StepRepr_MeasureRepresentationItem()
{
  myMeasure = new StepBasic_MeasureWithUnit;
}

//=================================================================================================

void StepRepr_MeasureRepresentationItem::Init(
  const occ::handle<TCollection_HAsciiString>&     aName,
  const occ::handle<StepBasic_MeasureValueMember>& aValueComponent,
  const StepBasic_Unit&                            aUnitComponent)
{
  StepRepr_RepresentationItem::Init(aName);
  myMeasure->Init(aValueComponent, aUnitComponent);
}

//=================================================================================================

void StepRepr_MeasureRepresentationItem::SetMeasure(
  const occ::handle<StepBasic_MeasureWithUnit>& Measure)
{
  myMeasure = Measure;
}

//=================================================================================================

occ::handle<StepBasic_MeasureWithUnit> StepRepr_MeasureRepresentationItem::Measure() const
{
  return myMeasure;
}
