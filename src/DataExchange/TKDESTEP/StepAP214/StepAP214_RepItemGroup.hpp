#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_Group.hpp>
#include <Standard_Boolean.hpp>
class StepRepr_RepresentationItem;
class TCollection_HAsciiString;

class StepAP214_RepItemGroup : public StepBasic_Group
{

public:
  Standard_EXPORT StepAP214_RepItemGroup();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aGroup_Name,
                            const bool                                   hasGroup_Description,
                            const occ::handle<TCollection_HAsciiString>& aGroup_Description,
                            const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name);

  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> RepresentationItem() const;

  Standard_EXPORT void SetRepresentationItem(
    const occ::handle<StepRepr_RepresentationItem>& RepresentationItem);

  DEFINE_STANDARD_RTTIEXT(StepAP214_RepItemGroup, StepBasic_Group)

private:
  occ::handle<StepRepr_RepresentationItem> theRepresentationItem;
};
