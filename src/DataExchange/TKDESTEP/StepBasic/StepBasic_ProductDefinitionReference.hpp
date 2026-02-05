#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_ExternalSource;

//! Representation of STEP entity Product_Definition_Reference
class StepBasic_ProductDefinitionReference : public Standard_Transient
{
public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ProductDefinitionReference();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepBasic_ExternalSource>& theSource,
    const occ::handle<TCollection_HAsciiString>& theProductId,
    const occ::handle<TCollection_HAsciiString>& theProductDefinitionFormationId,
    const occ::handle<TCollection_HAsciiString>& theProductDefinitionId,
    const occ::handle<TCollection_HAsciiString>& theIdOwningOrganizationName);

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepBasic_ExternalSource>& theSource,
    const occ::handle<TCollection_HAsciiString>& theProductId,
    const occ::handle<TCollection_HAsciiString>& theProductDefinitionFormationId,
    const occ::handle<TCollection_HAsciiString>& theProductDefinitionId);

  //! Returns field Source
  inline occ::handle<StepBasic_ExternalSource> Source() const { return mySource; }

  //! Set field Source
  inline void SetSource(const occ::handle<StepBasic_ExternalSource>& theSource)
  {
    mySource = theSource;
  }

  //! Returns field ProductId
  inline occ::handle<TCollection_HAsciiString> ProductId() const { return myProductId; }

  //! Set field ProductId
  inline void SetProductId(const occ::handle<TCollection_HAsciiString>& theProductId)
  {
    myProductId = theProductId;
  }

  //! Returns field ProductDefinitionFormationId
  inline occ::handle<TCollection_HAsciiString> ProductDefinitionFormationId() const
  {
    return myProductDefinitionFormationId;
  }

  //! Set field ProductDefinitionFormationId
  inline void SetProductDefinitionFormationId(
    const occ::handle<TCollection_HAsciiString>& theProductDefinitionFormationId)
  {
    myProductDefinitionFormationId = theProductDefinitionFormationId;
  }

  //! Returns field ProductDefinitionId
  inline occ::handle<TCollection_HAsciiString> ProductDefinitionId() const
  {
    return myProductDefinitionId;
  }

  //! Set field ProductDefinitionId
  inline void SetProductDefinitionId(
    const occ::handle<TCollection_HAsciiString>& theProductDefinitionId)
  {
    myProductDefinitionId = theProductDefinitionId;
  }

  //! Returns field IdOwningOrganizationName
  inline occ::handle<TCollection_HAsciiString> IdOwningOrganizationName() const
  {
    return myIdOwningOrganizationName;
  }

  //! Set field IdOwningOrganizationName
  inline void SetIdOwningOrganizationName(
    const occ::handle<TCollection_HAsciiString>& theIdOwningOrganizationName)
  {
    myIdOwningOrganizationName  = theIdOwningOrganizationName;
    hasIdOwningOrganizationName = (!theIdOwningOrganizationName.IsNull());
  }

  //! Returns true if IdOwningOrganizationName exists
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
