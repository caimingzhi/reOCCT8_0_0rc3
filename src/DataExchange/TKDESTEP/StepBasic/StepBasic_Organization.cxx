

#include <StepBasic_Organization.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_Organization, Standard_Transient)

StepBasic_Organization::StepBasic_Organization() = default;

void StepBasic_Organization::Init(const bool                                   hasAid,
                                  const occ::handle<TCollection_HAsciiString>& aId,
                                  const occ::handle<TCollection_HAsciiString>& aName,
                                  const occ::handle<TCollection_HAsciiString>& aDescription)
{

  hasId       = hasAid;
  id          = aId;
  name        = aName;
  description = aDescription;
}

void StepBasic_Organization::SetId(const occ::handle<TCollection_HAsciiString>& aId)
{
  id    = aId;
  hasId = true;
}

void StepBasic_Organization::UnSetId()
{
  hasId = false;
  id.Nullify();
}

occ::handle<TCollection_HAsciiString> StepBasic_Organization::Id() const
{
  return id;
}

bool StepBasic_Organization::HasId() const
{
  return hasId;
}

void StepBasic_Organization::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_Organization::Name() const
{
  return name;
}

void StepBasic_Organization::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  description = aDescription;
}

occ::handle<TCollection_HAsciiString> StepBasic_Organization::Description() const
{
  return description;
}
