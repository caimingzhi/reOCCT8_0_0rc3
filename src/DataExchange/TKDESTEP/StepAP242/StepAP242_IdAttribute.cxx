#include <StepAP242_IdAttribute.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP242_IdAttribute, Standard_Transient)

//=================================================================================================

StepAP242_IdAttribute::StepAP242_IdAttribute() = default;

//=================================================================================================

void StepAP242_IdAttribute::Init(const occ::handle<TCollection_HAsciiString>& theAttributeValue,
                                 const StepAP242_IdAttributeSelect&           theIdentifiedItem)
{
  // --- classe own fields ---
  attributeValue = theAttributeValue;
  identifiedItem = theIdentifiedItem;
}
