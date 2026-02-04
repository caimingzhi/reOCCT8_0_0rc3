#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepRepr_ProductConcept;

//! Representation of STEP entity ConfigurationItem
class StepRepr_ConfigurationItem : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_ConfigurationItem();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aId,
                            const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasDescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepRepr_ProductConcept>&  aItemConcept,
                            const bool                                   hasPurpose,
                            const occ::handle<TCollection_HAsciiString>& aPurpose);

  //! Returns field Id
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  //! Set field Id
  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& Id);

  //! Returns field Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Set field Name
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  //! Returns True if optional field Description is defined
  Standard_EXPORT bool HasDescription() const;

  //! Returns field ItemConcept
  Standard_EXPORT occ::handle<StepRepr_ProductConcept> ItemConcept() const;

  //! Set field ItemConcept
  Standard_EXPORT void SetItemConcept(const occ::handle<StepRepr_ProductConcept>& ItemConcept);

  //! Returns field Purpose
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Purpose() const;

  //! Set field Purpose
  Standard_EXPORT void SetPurpose(const occ::handle<TCollection_HAsciiString>& Purpose);

  //! Returns True if optional field Purpose is defined
  Standard_EXPORT bool HasPurpose() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_ConfigurationItem, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theId;
  occ::handle<TCollection_HAsciiString> theName;
  occ::handle<TCollection_HAsciiString> theDescription;
  occ::handle<StepRepr_ProductConcept>  theItemConcept;
  occ::handle<TCollection_HAsciiString> thePurpose;
  bool                                  defDescription;
  bool                                  defPurpose;
};

