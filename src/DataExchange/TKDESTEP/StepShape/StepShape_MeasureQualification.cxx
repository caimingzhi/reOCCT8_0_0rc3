

#include <StepBasic_MeasureWithUnit.hpp>
#include <StepShape_MeasureQualification.hpp>
#include <StepShape_ValueQualifier.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_MeasureQualification, Standard_Transient)

StepShape_MeasureQualification::StepShape_MeasureQualification() = default;

void StepShape_MeasureQualification::Init(
  const occ::handle<TCollection_HAsciiString>&                      name,
  const occ::handle<TCollection_HAsciiString>&                      description,
  const occ::handle<Standard_Transient>&                            qualified_measure,
  const occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>& qualifiers)
{
  theName             = name;
  theDescription      = description;
  theQualifiedMeasure = qualified_measure;
  theQualifiers       = qualifiers;
}

occ::handle<TCollection_HAsciiString> StepShape_MeasureQualification::Name() const
{
  return theName;
}

void StepShape_MeasureQualification::SetName(const occ::handle<TCollection_HAsciiString>& name)
{
  theName = name;
}

occ::handle<TCollection_HAsciiString> StepShape_MeasureQualification::Description() const
{
  return theDescription;
}

void StepShape_MeasureQualification::SetDescription(
  const occ::handle<TCollection_HAsciiString>& description)
{
  theDescription = description;
}

occ::handle<Standard_Transient> StepShape_MeasureQualification::QualifiedMeasure() const
{
  return theQualifiedMeasure;
}

void StepShape_MeasureQualification::SetQualifiedMeasure(
  const occ::handle<Standard_Transient>& qualified_measure)
{
  theQualifiedMeasure = qualified_measure;
}

occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> StepShape_MeasureQualification::
  Qualifiers() const
{
  return theQualifiers;
}

int StepShape_MeasureQualification::NbQualifiers() const
{
  return theQualifiers->Length();
}

void StepShape_MeasureQualification::SetQualifiers(
  const occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>& qualifiers)
{
  theQualifiers = qualifiers;
}

StepShape_ValueQualifier StepShape_MeasureQualification::QualifiersValue(const int num) const
{
  return theQualifiers->Value(num);
}

void StepShape_MeasureQualification::SetQualifiersValue(const int                       num,
                                                        const StepShape_ValueQualifier& aqualifier)
{
  theQualifiers->SetValue(num, aqualifier);
}
