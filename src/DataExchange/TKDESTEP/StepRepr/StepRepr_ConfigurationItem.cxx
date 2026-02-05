#include <StepRepr_ConfigurationItem.hpp>
#include <StepRepr_ProductConcept.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ConfigurationItem, Standard_Transient)

//=================================================================================================

StepRepr_ConfigurationItem::StepRepr_ConfigurationItem()
{
  defDescription = false;
  defPurpose     = false;
}

//=================================================================================================

void StepRepr_ConfigurationItem::Init(const occ::handle<TCollection_HAsciiString>& aId,
                                      const occ::handle<TCollection_HAsciiString>& aName,
                                      const bool                                   hasDescription,
                                      const occ::handle<TCollection_HAsciiString>& aDescription,
                                      const occ::handle<StepRepr_ProductConcept>&  aItemConcept,
                                      const bool                                   hasPurpose,
                                      const occ::handle<TCollection_HAsciiString>& aPurpose)
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

  theItemConcept = aItemConcept;

  defPurpose = hasPurpose;
  if (defPurpose)
  {
    thePurpose = aPurpose;
  }
  else
    thePurpose.Nullify();
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepRepr_ConfigurationItem::Id() const
{
  return theId;
}

//=================================================================================================

void StepRepr_ConfigurationItem::SetId(const occ::handle<TCollection_HAsciiString>& aId)
{
  theId = aId;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepRepr_ConfigurationItem::Name() const
{
  return theName;
}

//=================================================================================================

void StepRepr_ConfigurationItem::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepRepr_ConfigurationItem::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepRepr_ConfigurationItem::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

bool StepRepr_ConfigurationItem::HasDescription() const
{
  return defDescription;
}

//=================================================================================================

occ::handle<StepRepr_ProductConcept> StepRepr_ConfigurationItem::ItemConcept() const
{
  return theItemConcept;
}

//=================================================================================================

void StepRepr_ConfigurationItem::SetItemConcept(
  const occ::handle<StepRepr_ProductConcept>& aItemConcept)
{
  theItemConcept = aItemConcept;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepRepr_ConfigurationItem::Purpose() const
{
  return thePurpose;
}

//=================================================================================================

void StepRepr_ConfigurationItem::SetPurpose(const occ::handle<TCollection_HAsciiString>& aPurpose)
{
  thePurpose = aPurpose;
}

//=================================================================================================

bool StepRepr_ConfigurationItem::HasPurpose() const
{
  return defPurpose;
}
