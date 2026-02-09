

#include <StepShape_QualifiedRepresentationItem.hpp>
#include <StepShape_ValueQualifier.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_QualifiedRepresentationItem, StepRepr_RepresentationItem)

StepShape_QualifiedRepresentationItem::StepShape_QualifiedRepresentationItem() = default;

void StepShape_QualifiedRepresentationItem::Init(
  const occ::handle<TCollection_HAsciiString>&                      aName,
  const occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>& qualifiers)
{
  StepRepr_RepresentationItem::Init(aName);
  theQualifiers = qualifiers;
}

occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> StepShape_QualifiedRepresentationItem::
  Qualifiers() const
{
  return theQualifiers;
}

int StepShape_QualifiedRepresentationItem::NbQualifiers() const
{
  return theQualifiers->Length();
}

void StepShape_QualifiedRepresentationItem::SetQualifiers(
  const occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>& qualifiers)
{
  theQualifiers = qualifiers;
}

StepShape_ValueQualifier StepShape_QualifiedRepresentationItem::QualifiersValue(const int num) const
{
  return theQualifiers->Value(num);
}

void StepShape_QualifiedRepresentationItem::SetQualifiersValue(
  const int                       num,
  const StepShape_ValueQualifier& aqualifier)
{
  theQualifiers->SetValue(num, aqualifier);
}
