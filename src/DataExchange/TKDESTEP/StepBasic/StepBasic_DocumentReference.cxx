

#include <StepBasic_Document.hpp>
#include <StepBasic_DocumentReference.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DocumentReference, Standard_Transient)

void StepBasic_DocumentReference::Init0(const occ::handle<StepBasic_Document>& aAssignedDocument,
                                        const occ::handle<TCollection_HAsciiString>& aSource)
{
  theAssignedDocument = aAssignedDocument;
  theSource           = aSource;
}

occ::handle<StepBasic_Document> StepBasic_DocumentReference::AssignedDocument() const
{
  return theAssignedDocument;
}

void StepBasic_DocumentReference::SetAssignedDocument(
  const occ::handle<StepBasic_Document>& aAssignedDocument)
{
  theAssignedDocument = aAssignedDocument;
}

occ::handle<TCollection_HAsciiString> StepBasic_DocumentReference::Source() const
{
  return theSource;
}

void StepBasic_DocumentReference::SetSource(const occ::handle<TCollection_HAsciiString>& aSource)
{
  theSource = aSource;
}
