

#include <Standard_Type.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_RepresentationMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_RepresentationMap, Standard_Transient)

StepRepr_RepresentationMap::StepRepr_RepresentationMap() = default;

void StepRepr_RepresentationMap::Init(
  const occ::handle<StepRepr_RepresentationItem>& aMappingOrigin,
  const occ::handle<StepRepr_Representation>&     aMappedRepresentation)
{

  mappingOrigin        = aMappingOrigin;
  mappedRepresentation = aMappedRepresentation;
}

void StepRepr_RepresentationMap::SetMappingOrigin(
  const occ::handle<StepRepr_RepresentationItem>& aMappingOrigin)
{
  mappingOrigin = aMappingOrigin;
}

occ::handle<StepRepr_RepresentationItem> StepRepr_RepresentationMap::MappingOrigin() const
{
  return mappingOrigin;
}

void StepRepr_RepresentationMap::SetMappedRepresentation(
  const occ::handle<StepRepr_Representation>& aMappedRepresentation)
{
  mappedRepresentation = aMappedRepresentation;
}

occ::handle<StepRepr_Representation> StepRepr_RepresentationMap::MappedRepresentation() const
{
  return mappedRepresentation;
}
