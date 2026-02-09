#include <StepBasic_ActionMethod.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ActionMethod, Standard_Transient)

StepBasic_ActionMethod::StepBasic_ActionMethod()
{
  defDescription = false;
}

void StepBasic_ActionMethod::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                  const bool                                   hasDescription,
                                  const occ::handle<TCollection_HAsciiString>& aDescription,
                                  const occ::handle<TCollection_HAsciiString>& aConsequence,
                                  const occ::handle<TCollection_HAsciiString>& aPurpose)
{

  theName = aName;

  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();

  theConsequence = aConsequence;

  thePurpose = aPurpose;
}

occ::handle<TCollection_HAsciiString> StepBasic_ActionMethod::Name() const
{
  return theName;
}

void StepBasic_ActionMethod::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_ActionMethod::Description() const
{
  return theDescription;
}

void StepBasic_ActionMethod::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

bool StepBasic_ActionMethod::HasDescription() const
{
  return defDescription;
}

occ::handle<TCollection_HAsciiString> StepBasic_ActionMethod::Consequence() const
{
  return theConsequence;
}

void StepBasic_ActionMethod::SetConsequence(
  const occ::handle<TCollection_HAsciiString>& aConsequence)
{
  theConsequence = aConsequence;
}

occ::handle<TCollection_HAsciiString> StepBasic_ActionMethod::Purpose() const
{
  return thePurpose;
}

void StepBasic_ActionMethod::SetPurpose(const occ::handle<TCollection_HAsciiString>& aPurpose)
{
  thePurpose = aPurpose;
}
