#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_ExternalSource;

class StepBasic_ProductDefinitionReference : public Standard_Transient
{
public:
  Standard_EXPORT StepBasic_ProductDefinitionReference();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_ExternalSource>& theSource,
    const occ::handle<TCollection_HAsciiString>& theProductId,
    const occ::handle<TCollection_HAsciiString>& theProductDefinitionFormationId,
    const occ::handle<TCollection_HAsciiString>& theProductDefinitionId,
    const occ::handle<TCollection_HAsciiString>& theIdOwningOrganizationName);

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_ExternalSource>& theSource,
    const occ::handle<TCollection_HAsciiString>& theProductId,
    const occ::handle<TCollection_HAsciiString>& theProductDefinitionFormationId,
    const occ::handle<TCollection_HAsciiString>& theProductDefinitionId);

  inline occ::handle<StepBasic_ExternalSource> Source() const { return mySource; }

  inline void SetSource(const occ::handle<StepBasic_ExternalSource>& theSource)
  {
    mySource = theSource;
  }

  inline occ::handle<TCollection_HAsciiString> ProductId() const { return myProductId; }

  inline void SetProductId(const occ::handle<TCollection_HAsciiString>& theProductId)
  {
    myProductId = theProductId;
  }

  inline occ::handle<TCollection_HAsciiString> ProductDefinitionFormationId() const
  {
    return myProductDefinitionFormationId;
  }

  inline void SetProductDefinitionFormationId(
    const occ::handle<TCollection_HAsciiString>& theProductDefinitionFormationId)
  {
    myProductDefinitionFormationId = theProductDefinitionFormationId;
  }

  inline occ::handle<TCollection_HAsciiString> ProductDefinitionId() const
  {
    return myProductDefinitionId;
  }

  inline void SetProductDefinitionId(
    const occ::handle<TCollection_HAsciiString>& theProductDefinitionId)
  {
    myProductDefinitionId = theProductDefinitionId;
  }

  inline occ::handle<TCollection_HAsciiString> IdOwningOrganizationName() const
  {
    return myIdOwningOrganizationName;
  }

  inline void SetIdOwningOrganizationName(
    const occ::handle<TCollection_HAsciiString>& theIdOwningOrganizationName)
  {
    myIdOwningOrganizationName  = theIdOwningOrganizationName;
    hasIdOwningOrganizationName = (!theIdOwningOrganizationName.IsNull());
  }

  inline bool HasIdOwningOrganizationName() const { return hasIdOwningOrganizationName; }

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductDefinitionReference, Standard_Transient)

private:
  occ::handle<StepBasic_ExternalSource> mySource;
  occ::handle<TCollection_HAsciiString> myProductId;
  occ::handle<TCollection_HAsciiString> myProductDefinitionFormationId;
  occ::handle<TCollection_HAsciiString> myProductDefinitionId;
  occ::handle<TCollection_HAsciiString> myIdOwningOrganizationName;
  bool                                  hasIdOwningOrganizationName;
};
