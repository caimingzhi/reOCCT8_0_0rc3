#pragma once

#include <Standard.hpp>

#include <StepAP242_IdAttributeSelect.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepAP242_IdAttribute : public Standard_Transient
{

public:
  Standard_EXPORT StepAP242_IdAttribute();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theAttributeValue,
                            const StepAP242_IdAttributeSelect&           theIdentifiedItem);

  inline void SetAttributeValue(const occ::handle<TCollection_HAsciiString>& theAttributeValue)
  {
    attributeValue = theAttributeValue;
  }

  inline occ::handle<TCollection_HAsciiString> AttributeValue() const { return attributeValue; }

  inline void SetIdentifiedItem(const StepAP242_IdAttributeSelect& theIdentifiedItem)
  {
    identifiedItem = theIdentifiedItem;
  }

  inline StepAP242_IdAttributeSelect IdentifiedItem() const { return identifiedItem; }

  DEFINE_STANDARD_RTTIEXT(StepAP242_IdAttribute, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> attributeValue;
  StepAP242_IdAttributeSelect           identifiedItem;
};
