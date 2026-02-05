#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>
class StepRepr_RepresentationMap;
class TCollection_HAsciiString;

class StepRepr_MappedItem : public StepRepr_RepresentationItem
{

public:
  //! Returns a MappedItem
  Standard_EXPORT StepRepr_MappedItem();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&    aName,
                            const occ::handle<StepRepr_RepresentationMap>&  aMappingSource,
                            const occ::handle<StepRepr_RepresentationItem>& aMappingTarget);

  Standard_EXPORT void SetMappingSource(
    const occ::handle<StepRepr_RepresentationMap>& aMappingSource);

  Standard_EXPORT occ::handle<StepRepr_RepresentationMap> MappingSource() const;

  Standard_EXPORT void SetMappingTarget(
    const occ::handle<StepRepr_RepresentationItem>& aMappingTarget);

  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> MappingTarget() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_MappedItem, StepRepr_RepresentationItem)

private:
  occ::handle<StepRepr_RepresentationMap>  mappingSource;
  occ::handle<StepRepr_RepresentationItem> mappingTarget;
};
