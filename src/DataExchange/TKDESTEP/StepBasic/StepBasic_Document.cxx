#include <StepBasic_Document.hpp>
#include <StepBasic_DocumentType.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_Document, Standard_Transient)

StepBasic_Document::StepBasic_Document()
{
  defDescription = false;
}

void StepBasic_Document::Init(const occ::handle<TCollection_HAsciiString>& aId,
                              const occ::handle<TCollection_HAsciiString>& aName,
                              const bool                                   hasDescription,
                              const occ::handle<TCollection_HAsciiString>& aDescription,
                              const occ::handle<StepBasic_DocumentType>&   aKind)
{

  theId = aId;

  theName = aName;

  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();

  theKind = aKind;
}

occ::handle<TCollection_HAsciiString> StepBasic_Document::Id() const
{
  return theId;
}

void StepBasic_Document::SetId(const occ::handle<TCollection_HAsciiString>& aId)
{
  theId = aId;
}

occ::handle<TCollection_HAsciiString> StepBasic_Document::Name() const
{
  return theName;
}

void StepBasic_Document::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_Document::Description() const
{
  return theDescription;
}

void StepBasic_Document::SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

bool StepBasic_Document::HasDescription() const
{
  return defDescription;
}

occ::handle<StepBasic_DocumentType> StepBasic_Document::Kind() const
{
  return theKind;
}

void StepBasic_Document::SetKind(const occ::handle<StepBasic_DocumentType>& aKind)
{
  theKind = aKind;
}
