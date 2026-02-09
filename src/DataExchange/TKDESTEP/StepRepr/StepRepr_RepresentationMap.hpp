#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepRepr_RepresentationItem;
class StepRepr_Representation;

class StepRepr_RepresentationMap : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_RepresentationMap();

  Standard_EXPORT void Init(const occ::handle<StepRepr_RepresentationItem>& aMappingOrigin,
                            const occ::handle<StepRepr_Representation>&     aMappedRepresentation);

  Standard_EXPORT void SetMappingOrigin(
    const occ::handle<StepRepr_RepresentationItem>& aMappingOrigin);

  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> MappingOrigin() const;

  Standard_EXPORT void SetMappedRepresentation(
    const occ::handle<StepRepr_Representation>& aMappedRepresentation);

  Standard_EXPORT occ::handle<StepRepr_Representation> MappedRepresentation() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_RepresentationMap, Standard_Transient)

private:
  occ::handle<StepRepr_RepresentationItem> mappingOrigin;
  occ::handle<StepRepr_Representation>     mappedRepresentation;
};
