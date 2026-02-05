#include <StepBasic_ExternallyDefinedItem.hpp>
#include <StepBasic_ExternalSource.hpp>
#include <StepBasic_SourceItem.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ExternallyDefinedItem, Standard_Transient)

//=================================================================================================

StepBasic_ExternallyDefinedItem::StepBasic_ExternallyDefinedItem() = default;

//=================================================================================================

void StepBasic_ExternallyDefinedItem::Init(const StepBasic_SourceItem&                  aItemId,
                                           const occ::handle<StepBasic_ExternalSource>& aSource)
{

  theItemId = aItemId;

  theSource = aSource;
}

//=================================================================================================

StepBasic_SourceItem StepBasic_ExternallyDefinedItem::ItemId() const
{
  return theItemId;
}

//=================================================================================================

void StepBasic_ExternallyDefinedItem::SetItemId(const StepBasic_SourceItem& aItemId)
{
  theItemId = aItemId;
}

//=================================================================================================

occ::handle<StepBasic_ExternalSource> StepBasic_ExternallyDefinedItem::Source() const
{
  return theSource;
}

//=================================================================================================

void StepBasic_ExternallyDefinedItem::SetSource(
  const occ::handle<StepBasic_ExternalSource>& aSource)
{
  theSource = aSource;
}
