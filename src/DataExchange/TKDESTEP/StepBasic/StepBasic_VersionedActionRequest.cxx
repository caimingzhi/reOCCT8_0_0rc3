#include <StepBasic_VersionedActionRequest.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_VersionedActionRequest, Standard_Transient)

StepBasic_VersionedActionRequest::StepBasic_VersionedActionRequest()
{
  defDescription = false;
}

void StepBasic_VersionedActionRequest::Init(
  const occ::handle<TCollection_HAsciiString>& aId,
  const occ::handle<TCollection_HAsciiString>& aVersion,
  const occ::handle<TCollection_HAsciiString>& aPurpose,
  const bool                                   hasDescription,
  const occ::handle<TCollection_HAsciiString>& aDescription)
{

  theId = aId;

  theVersion = aVersion;

  thePurpose = aPurpose;

  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();
}

occ::handle<TCollection_HAsciiString> StepBasic_VersionedActionRequest::Id() const
{
  return theId;
}

void StepBasic_VersionedActionRequest::SetId(const occ::handle<TCollection_HAsciiString>& aId)
{
  theId = aId;
}

occ::handle<TCollection_HAsciiString> StepBasic_VersionedActionRequest::Version() const
{
  return theVersion;
}

void StepBasic_VersionedActionRequest::SetVersion(
  const occ::handle<TCollection_HAsciiString>& aVersion)
{
  theVersion = aVersion;
}

occ::handle<TCollection_HAsciiString> StepBasic_VersionedActionRequest::Purpose() const
{
  return thePurpose;
}

void StepBasic_VersionedActionRequest::SetPurpose(
  const occ::handle<TCollection_HAsciiString>& aPurpose)
{
  thePurpose = aPurpose;
}

occ::handle<TCollection_HAsciiString> StepBasic_VersionedActionRequest::Description() const
{
  return theDescription;
}

void StepBasic_VersionedActionRequest::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

bool StepBasic_VersionedActionRequest::HasDescription() const
{
  return defDescription;
}
