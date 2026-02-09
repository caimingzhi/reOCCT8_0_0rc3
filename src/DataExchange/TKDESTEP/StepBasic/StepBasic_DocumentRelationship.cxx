

#include <StepBasic_Document.hpp>
#include <StepBasic_DocumentRelationship.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DocumentRelationship, Standard_Transient)

StepBasic_DocumentRelationship::StepBasic_DocumentRelationship() = default;

void StepBasic_DocumentRelationship::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                          const occ::handle<TCollection_HAsciiString>& aDescription,
                                          const occ::handle<StepBasic_Document>&       aRelating,
                                          const occ::handle<StepBasic_Document>&       aRelated)
{
  theName        = aName;
  theDescription = aDescription;
  theRelating    = aRelating;
  theRelated     = aRelated;
}

occ::handle<TCollection_HAsciiString> StepBasic_DocumentRelationship::Name() const
{
  return theName;
}

void StepBasic_DocumentRelationship::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_DocumentRelationship::Description() const
{
  return theDescription;
}

void StepBasic_DocumentRelationship::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

occ::handle<StepBasic_Document> StepBasic_DocumentRelationship::RelatingDocument() const
{
  return theRelating;
}

void StepBasic_DocumentRelationship::SetRelatingDocument(
  const occ::handle<StepBasic_Document>& aRelating)
{
  theRelating = aRelating;
}

occ::handle<StepBasic_Document> StepBasic_DocumentRelationship::RelatedDocument() const
{
  return theRelated;
}

void StepBasic_DocumentRelationship::SetRelatedDocument(
  const occ::handle<StepBasic_Document>& aRelated)
{
  theRelated = aRelated;
}
