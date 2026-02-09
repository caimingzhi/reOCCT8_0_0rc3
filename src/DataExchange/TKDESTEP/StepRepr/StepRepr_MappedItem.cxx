

#include <StepRepr_MappedItem.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_RepresentationMap.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_MappedItem, StepRepr_RepresentationItem)

StepRepr_MappedItem::StepRepr_MappedItem() = default;

void StepRepr_MappedItem::Init(const occ::handle<TCollection_HAsciiString>&    aName,
                               const occ::handle<StepRepr_RepresentationMap>&  aMappingSource,
                               const occ::handle<StepRepr_RepresentationItem>& aMappingTarget)
{

  mappingSource = aMappingSource;
  mappingTarget = aMappingTarget;

  StepRepr_RepresentationItem::Init(aName);
}

void StepRepr_MappedItem::SetMappingSource(
  const occ::handle<StepRepr_RepresentationMap>& aMappingSource)
{
  mappingSource = aMappingSource;
}

occ::handle<StepRepr_RepresentationMap> StepRepr_MappedItem::MappingSource() const
{
  return mappingSource;
}

void StepRepr_MappedItem::SetMappingTarget(
  const occ::handle<StepRepr_RepresentationItem>& aMappingTarget)
{
  mappingTarget = aMappingTarget;
}

occ::handle<StepRepr_RepresentationItem> StepRepr_MappedItem::MappingTarget() const
{
  return mappingTarget;
}
