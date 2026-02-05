#include <StepBasic_Group.hpp>
#include <StepBasic_GroupRelationship.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_GroupRelationship, Standard_Transient)

//=================================================================================================

StepBasic_GroupRelationship::StepBasic_GroupRelationship()
{
  defDescription = false;
}

//=================================================================================================

void StepBasic_GroupRelationship::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                       const bool                                   hasDescription,
                                       const occ::handle<TCollection_HAsciiString>& aDescription,
                                       const occ::handle<StepBasic_Group>&          aRelatingGroup,
                                       const occ::handle<StepBasic_Group>&          aRelatedGroup)
{

  theName = aName;

  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();

  theRelatingGroup = aRelatingGroup;

  theRelatedGroup = aRelatedGroup;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_GroupRelationship::Name() const
{
  return theName;
}

//=================================================================================================

void StepBasic_GroupRelationship::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_GroupRelationship::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepBasic_GroupRelationship::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

bool StepBasic_GroupRelationship::HasDescription() const
{
  return defDescription;
}

//=================================================================================================

occ::handle<StepBasic_Group> StepBasic_GroupRelationship::RelatingGroup() const
{
  return theRelatingGroup;
}

//=================================================================================================

void StepBasic_GroupRelationship::SetRelatingGroup(
  const occ::handle<StepBasic_Group>& aRelatingGroup)
{
  theRelatingGroup = aRelatingGroup;
}

//=================================================================================================

occ::handle<StepBasic_Group> StepBasic_GroupRelationship::RelatedGroup() const
{
  return theRelatedGroup;
}

//=================================================================================================

void StepBasic_GroupRelationship::SetRelatedGroup(const occ::handle<StepBasic_Group>& aRelatedGroup)
{
  theRelatedGroup = aRelatedGroup;
}
