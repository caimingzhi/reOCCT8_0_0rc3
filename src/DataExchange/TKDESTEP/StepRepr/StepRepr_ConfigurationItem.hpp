#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepRepr_ProductConcept;

class StepRepr_ConfigurationItem : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_ConfigurationItem();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aId,
                            const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasDescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepRepr_ProductConcept>&  aItemConcept,
                            const bool                                   hasPurpose,
                            const occ::handle<TCollection_HAsciiString>& aPurpose);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& Id);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT bool HasDescription() const;

  Standard_EXPORT occ::handle<StepRepr_ProductConcept> ItemConcept() const;

  Standard_EXPORT void SetItemConcept(const occ::handle<StepRepr_ProductConcept>& ItemConcept);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Purpose() const;

  Standard_EXPORT void SetPurpose(const occ::handle<TCollection_HAsciiString>& Purpose);

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
