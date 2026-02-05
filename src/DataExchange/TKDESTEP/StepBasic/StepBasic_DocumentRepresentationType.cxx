#include <StepBasic_Document.hpp>
#include <StepBasic_DocumentRepresentationType.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DocumentRepresentationType, Standard_Transient)

//=================================================================================================

StepBasic_DocumentRepresentationType::StepBasic_DocumentRepresentationType() = default;

//=================================================================================================

void StepBasic_DocumentRepresentationType::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<StepBasic_Document>&       aRepresentedDocument)
{

  theName = aName;

  theRepresentedDocument = aRepresentedDocument;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_DocumentRepresentationType::Name() const
{
  return theName;
}

//=================================================================================================

void StepBasic_DocumentRepresentationType::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<StepBasic_Document> StepBasic_DocumentRepresentationType::RepresentedDocument() const
{
  return theRepresentedDocument;
}

//=================================================================================================

void StepBasic_DocumentRepresentationType::SetRepresentedDocument(
  const occ::handle<StepBasic_Document>& aRepresentedDocument)
{
  theRepresentedDocument = aRepresentedDocument;
}
