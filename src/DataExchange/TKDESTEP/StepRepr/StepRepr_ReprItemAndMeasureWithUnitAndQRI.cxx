#include <Standard_Type.hpp>
#include <StepShape_QualifiedRepresentationItem.hpp>
#include <StepRepr_ReprItemAndMeasureWithUnitAndQRI.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ReprItemAndMeasureWithUnitAndQRI,
                           StepRepr_ReprItemAndMeasureWithUnit)

void StepRepr_ReprItemAndMeasureWithUnitAndQRI::Init(
  const occ::handle<StepBasic_MeasureWithUnit>&             aMWU,
  const occ::handle<StepRepr_RepresentationItem>&           aRI,
  const occ::handle<StepShape_QualifiedRepresentationItem>& aQRI)
{
  StepRepr_ReprItemAndMeasureWithUnit::Init(aMWU, aRI);
  myQualifiedRepresentationItem = aQRI;
}

StepRepr_ReprItemAndMeasureWithUnitAndQRI::StepRepr_ReprItemAndMeasureWithUnitAndQRI()

{
  myQualifiedRepresentationItem = new StepShape_QualifiedRepresentationItem();
}

void StepRepr_ReprItemAndMeasureWithUnitAndQRI::SetQualifiedRepresentationItem(
  const occ::handle<StepShape_QualifiedRepresentationItem>& aQRI)
{
  myQualifiedRepresentationItem = aQRI;
}

occ::handle<StepShape_QualifiedRepresentationItem> StepRepr_ReprItemAndMeasureWithUnitAndQRI::
  GetQualifiedRepresentationItem() const
{
  return myQualifiedRepresentationItem;
}
