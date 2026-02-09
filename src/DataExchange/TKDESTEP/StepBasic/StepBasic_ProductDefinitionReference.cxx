#include <StepBasic_ExternalSource.hpp>
#include <StepBasic_ProductDefinitionReference.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductDefinitionReference, Standard_Transient)

StepBasic_ProductDefinitionReference::StepBasic_ProductDefinitionReference() = default;

void StepBasic_ProductDefinitionReference::Init(
  const occ::handle<StepBasic_ExternalSource>& theSource,
  const occ::handle<TCollection_HAsciiString>& theProductId,
  const occ::handle<TCollection_HAsciiString>& theProductDefinitionFormationId,
  const occ::handle<TCollection_HAsciiString>& theProductDefinitionId,
  const occ::handle<TCollection_HAsciiString>& theIdOwningOrganizationName)
{
  mySource                       = theSource;
  myProductId                    = theProductId;
  myProductDefinitionFormationId = theProductDefinitionFormationId;
  myProductDefinitionId          = theProductDefinitionId;
  myIdOwningOrganizationName     = theIdOwningOrganizationName;
  hasIdOwningOrganizationName    = (!theIdOwningOrganizationName.IsNull());
}

void StepBasic_ProductDefinitionReference::Init(
  const occ::handle<StepBasic_ExternalSource>& theSource,
  const occ::handle<TCollection_HAsciiString>& theProductId,
  const occ::handle<TCollection_HAsciiString>& theProductDefinitionFormationId,
  const occ::handle<TCollection_HAsciiString>& theProductDefinitionId)
{
  mySource                       = theSource;
  myProductId                    = theProductId;
  myProductDefinitionFormationId = theProductDefinitionFormationId;
  myProductDefinitionId          = theProductDefinitionId;
  hasIdOwningOrganizationName    = false;
}
