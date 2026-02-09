

#include <Standard_Type.hpp>
#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_Unit.hpp>
#include <StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem.hpp>
#include <StepShape_ValueQualifier.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem,
                           StepRepr_RepresentationItem)

StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem::
  StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem()
{
  myMeasure = new StepBasic_MeasureWithUnit;
}

void StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem::Init(
  const occ::handle<TCollection_HAsciiString>&                      aName,
  const occ::handle<StepBasic_MeasureValueMember>&                  aValueComponent,
  const StepBasic_Unit&                                             aUnitComponent,
  const occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>& qualifiers)
{
  StepRepr_RepresentationItem::Init(aName);
  myMeasure->Init(aValueComponent, aUnitComponent);
  theQualifiers = qualifiers;
}

void StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem::SetMeasure(
  const occ::handle<StepBasic_MeasureWithUnit>& Measure)
{
  myMeasure = Measure;
}

occ::handle<StepBasic_MeasureWithUnit>
  StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem::Measure() const
{
  return myMeasure;
}

occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>
  StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem::Qualifiers() const
{
  return theQualifiers;
}

int StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem::NbQualifiers() const
{
  return theQualifiers->Length();
}

void StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem::SetQualifiers(
  const occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>& qualifiers)
{
  theQualifiers = qualifiers;
}

StepShape_ValueQualifier StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem::
  QualifiersValue(const int num) const
{
  return theQualifiers->Value(num);
}

void StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem::SetQualifiersValue(
  const int                       num,
  const StepShape_ValueQualifier& aqualifier)
{
  theQualifiers->SetValue(num, aqualifier);
}
